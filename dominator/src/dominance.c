#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "hard-reg-set.h"
#include "obstack.h"
#include "basic-block.h"
#include "toplev.h"
#include "et-forest.h"
#include "timevar.h"
#include "vecprim.h"
#include "pointer-set.h"
#include "graphds.h"

static void init_dom_info (struct dom_info *, enum cdi_direction);
static void free_dom_info (struct dom_info *);
static void calc_dfs_tree_nonrec (struct dom_info *, basic_block, bool);
static void calc_dfs_tree (struct dom_info *, bool);
static void compress (struct dom_info *, TBB);
static TBB eval (struct dom_info *, TBB);
static void link_roots (struct dom_info *, TBB, TBB);
static void calc_idoms (struct dom_info *, bool);
void debug_dominance_info (enum cdi_direction);
void debug_dominance_tree (enum cdi_direction, basic_block);

/* Map dominance calculation type to array index used for various
   dominance information arrays.  This version is simple -- it will need
   to be modified, obviously, if additional values are added to
   cdi_direction.  */

static unsigned int
dom_convert_dir_to_idx (enum cdi_direction dir)
{
  gcc_assert (dir == CDI_DOMINATORS || dir == CDI_POST_DOMINATORS);
  return dir - 1;
}

/* Free all allocated memory in DI, but not DI itself.  */

static void
free_dom_info (struct dom_info *di)
{
  free (di->dfs_parent);
  free (di->path_min);
  free (di->key);
  free (di->dom);
  free (di->bucket);
  free (di->next_bucket);
  free (di->set_chain);
  free (di->set_size);
  free (di->set_child);
  free (di->dfs_order);
  free (di->dfs_to_bb);
  BITMAP_FREE (di->fake_exit_edge);
}

/* Compress the path from V to the root of its set and update path_min at the
   same time.  After compress(di, V) set_chain[V] is the root of the set V is
   in and path_min[V] is the node with the smallest key[] value on the path
   from V to that root.  */

static void
compress (struct dom_info *di, TBB v)
{
  /* Btw. It's not worth to unrecurse compress() as the depth is usually not
     greater than 5 even for huge graphs (I've not seen call depth > 4).
     Also performance wise compress() ranges _far_ behind eval().  */
  TBB parent = di->set_chain[v];
  if (di->set_chain[parent])
    {
      compress (di, parent);
      if (di->key[di->path_min[parent]] < di->key[di->path_min[v]])
	di->path_min[v] = di->path_min[parent];
      di->set_chain[v] = di->set_chain[parent];
    }
}

/* Compress the path from V to the set root of V if needed (when the root has
   changed since the last call).  Returns the node with the smallest key[]
   value on the path from V to the root.  */

static inline TBB
eval (struct dom_info *di, TBB v)
{
  /* The representative of the set V is in, also called root (as the set
     representation is a tree).  */
  TBB rep = di->set_chain[v];

  /* V itself is the root.  */
  if (!rep)
    return di->path_min[v];

  /* Compress only if necessary.  */
  if (di->set_chain[rep])
    {
      compress (di, v);
      rep = di->set_chain[v];
    }

  if (di->key[di->path_min[rep]] >= di->key[di->path_min[v]])
    return di->path_min[v];
  else
    return di->path_min[rep];
}

/* This essentially merges the two sets of V and W, giving a single set with
   the new root V.  The internal representation of these disjoint sets is a
   balanced tree.  Currently link(V,W) is only used with V being the parent
   of W.  */

static void
link_roots (struct dom_info *di, TBB v, TBB w)
{
  TBB s = w;

  /* Rebalance the tree.  */
  while (di->key[di->path_min[w]] < di->key[di->path_min[di->set_child[s]]])
    {
      if (di->set_size[s] + di->set_size[di->set_child[di->set_child[s]]]
	  >= 2 * di->set_size[di->set_child[s]])
	{
	  di->set_chain[di->set_child[s]] = s;
	  di->set_child[s] = di->set_child[di->set_child[s]];
	}
      else
	{
	  di->set_size[di->set_child[s]] = di->set_size[s];
	  s = di->set_chain[s] = di->set_child[s];
	}
    }

  di->path_min[s] = di->path_min[w];
  di->set_size[v] += di->set_size[w];
  if (di->set_size[v] < 2 * di->set_size[w])
    {
      TBB tmp = s;
      s = di->set_child[v];
      di->set_child[v] = tmp;
    }

  /* Merge all subtrees.  */
  while (s)
    {
      di->set_chain[s] = v;
      s = di->set_child[s];
    }
}

/* This calculates the immediate dominators (or post-dominators if REVERSE is
   true).  DI is our working structure and should hold the DFS forest.
   On return the immediate dominator to node V is in di->dom[V].  */

static void
calc_idoms (struct dom_info *di, bool reverse)
{
  TBB v, w, k, par;
  basic_block en_block;
  edge_iterator ei, einext;

  if (reverse)
    en_block = EXIT_BLOCK_PTR;
  else
    en_block = ENTRY_BLOCK_PTR;

  /* Go backwards in DFS order, to first look at the leafs.  */
  v = di->nodes;
  while (v > 1)
    {
      basic_block bb = di->dfs_to_bb[v];
      edge e;

      par = di->dfs_parent[v];
      k = v;

      ei = (reverse) ? ei_start (bb->succs) : ei_start (bb->preds);

      if (reverse)
	{
	  /* If this block has a fake edge to exit, process that first.  */
	  if (bitmap_bit_p (di->fake_exit_edge, bb->index))
	    {
	      einext = ei;
	      einext.index = 0;
	      goto do_fake_exit_edge;
	    }
	}

      /* Search all direct predecessors for the smallest node with a path
         to them.  That way we have the smallest node with also a path to
         us only over nodes behind us.  In effect we search for our
         semidominator.  */
      while (!ei_end_p (ei))
	{
	  TBB k1;
	  basic_block b;

	  e = ei_edge (ei);
	  b = (reverse) ? e->dest : e->src;
	  einext = ei;
	  ei_next (&einext);

	  if (b == en_block)
	    {
	    do_fake_exit_edge:
	      k1 = di->dfs_order[last_basic_block];
	    }
	  else
	    k1 = di->dfs_order[b->index];

	  /* Call eval() only if really needed.  If k1 is above V in DFS tree,
	     then we know, that eval(k1) == k1 and key[k1] == k1.  */
	  if (k1 > v)
	    k1 = di->key[eval (di, k1)];
	  if (k1 < k)
	    k = k1;

	  ei = einext;
	}

      di->key[v] = k;
      link_roots (di, par, v);
      di->next_bucket[v] = di->bucket[k];
      di->bucket[k] = v;

      /* Transform semidominators into dominators.  */
      for (w = di->bucket[par]; w; w = di->next_bucket[w])
	{
	  k = eval (di, w);
	  if (di->key[k] < di->key[w])
	    di->dom[w] = k;
	  else
	    di->dom[w] = par;
	}
      /* We don't need to cleanup next_bucket[].  */
      di->bucket[par] = 0;
      v--;
    }

  /* Explicitly define the dominators.  */
  di->dom[1] = 0;
  for (v = 2; v <= di->nodes; v++)
    if (di->dom[v] != di->key[v])
      di->dom[v] = di->dom[di->dom[v]];
}

/* Assign dfs numbers starting from NUM to NODE and its sons.  */

static void
assign_dfs_numbers (struct et_node *node, int *num)
{
  struct et_node *son;

  node->dfs_num_in = (*num)++;

  if (node->son)
    {
      assign_dfs_numbers (node->son, num);
      for (son = node->son->right; son != node->son; son = son->right)
	assign_dfs_numbers (son, num);
    }

  node->dfs_num_out = (*num)++;
}

/* Compute the data necessary for fast resolving of dominator queries in a
   static dominator tree.  */

static void
compute_dom_fast_query (enum cdi_direction dir)
{
  int num = 0;
  basic_block bb;
  unsigned int dir_index = dom_convert_dir_to_idx (dir);

  gcc_assert (dom_info_available_p (dir));

  if (dom_computed[dir_index] == DOM_OK)
    return;

  FOR_ALL_BB (bb)
    {
      if (!bb->dom[dir_index]->father)
	assign_dfs_numbers (bb->dom[dir_index], &num);
    }

  dom_computed[dir_index] = DOM_OK;
}

/* The main entry point into this module.  DIR is set depending on whether
   we want to compute dominators or postdominators.  */

void
calculate_dominance_info (enum cdi_direction dir)
{
  struct dom_info di;
  basic_block b;
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  bool reverse = (dir == CDI_POST_DOMINATORS) ? true : false;

  if (dom_computed[dir_index] == DOM_OK)
    return;

  timevar_push (TV_DOMINANCE);
  if (!dom_info_available_p (dir))
    {
      gcc_assert (!n_bbs_in_dom_tree[dir_index]);

      FOR_ALL_BB (b)
	{
	  b->dom[dir_index] = et_new_tree (b);
	}
      n_bbs_in_dom_tree[dir_index] = n_basic_blocks;

      init_dom_info (&di, dir);
      calc_dfs_tree (&di, reverse);
      calc_idoms (&di, reverse);

      FOR_EACH_BB (b)
	{
	  TBB d = di.dom[di.dfs_order[b->index]];

	  if (di.dfs_to_bb[d])
	    et_set_father (b->dom[dir_index], di.dfs_to_bb[d]->dom[dir_index]);
	}

      free_dom_info (&di);
      dom_computed[dir_index] = DOM_NO_FAST_QUERY;
    }

  compute_dom_fast_query (dir);

  timevar_pop (TV_DOMINANCE);
}

/* Free dominance information for direction DIR.  */
void
free_dominance_info (enum cdi_direction dir)
{
  basic_block bb;
  unsigned int dir_index = dom_convert_dir_to_idx (dir);

  if (!dom_info_available_p (dir))
    return;

  FOR_ALL_BB (bb)
    {
      et_free_tree_force (bb->dom[dir_index]);
      bb->dom[dir_index] = NULL;
    }
  et_free_pools ();

  n_bbs_in_dom_tree[dir_index] = 0;

  dom_computed[dir_index] = DOM_NONE;
}

/* Return the immediate dominator of basic block BB.  */
basic_block
get_immediate_dominator (enum cdi_direction dir, basic_block bb)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  struct et_node *node = bb->dom[dir_index];

  gcc_assert (dom_computed[dir_index]);

  if (!node->father)
    return NULL;

  return (basic_block) node->father->data;
}

/* Set the immediate dominator of the block possibly removing
   existing edge.  NULL can be used to remove any edge.  */
inline void
set_immediate_dominator (enum cdi_direction dir, basic_block bb,
			 basic_block dominated_by)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  struct et_node *node = bb->dom[dir_index];
 
  gcc_assert (dom_computed[dir_index]);

  if (node->father)
    {
      if (node->father->data == dominated_by)
	return;
      et_split (node);
    }

  if (dominated_by)
    et_set_father (node, dominated_by->dom[dir_index]);

  if (dom_computed[dir_index] == DOM_OK)
    dom_computed[dir_index] = DOM_NO_FAST_QUERY;
}

/* Returns the list of basic blocks immediately dominated by BB, in the
   direction DIR.  */
VEC (basic_block, heap) *
get_dominated_by (enum cdi_direction dir, basic_block bb)
{
  int n;
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  struct et_node *node = bb->dom[dir_index], *son = node->son, *ason;
  VEC (basic_block, heap) *bbs = NULL;

  gcc_assert (dom_computed[dir_index]);

  if (!son)
    return NULL;

  VEC_safe_push (basic_block, heap, bbs, (basic_block) son->data);
  for (ason = son->right, n = 1; ason != son; ason = ason->right)
    VEC_safe_push (basic_block, heap, bbs, (basic_block) ason->data);

  return bbs;
}

/* Returns the list of basic blocks that are immediately dominated (in
   direction DIR) by some block between N_REGION ones stored in REGION,
   except for blocks in the REGION itself.  */
  
VEC (basic_block, heap) *
get_dominated_by_region (enum cdi_direction dir, basic_block *region,
			 unsigned n_region)
{
  unsigned i;
  basic_block dom;
  VEC (basic_block, heap) *doms = NULL;

  for (i = 0; i < n_region; i++)
    region[i]->flags |= BB_DUPLICATED;
  for (i = 0; i < n_region; i++)
    for (dom = first_dom_son (dir, region[i]);
	 dom;
	 dom = next_dom_son (dir, dom))
      if (!(dom->flags & BB_DUPLICATED))
	VEC_safe_push (basic_block, heap, doms, dom);
  for (i = 0; i < n_region; i++)
    region[i]->flags &= ~BB_DUPLICATED;

  return doms;
}

/* Redirect all edges pointing to BB to TO.  */
void
redirect_immediate_dominators (enum cdi_direction dir, basic_block bb,
			       basic_block to)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  struct et_node *bb_node, *to_node, *son;
 
  bb_node = bb->dom[dir_index];
  to_node = to->dom[dir_index];

  gcc_assert (dom_computed[dir_index]);

  if (!bb_node->son)
    return;

  while (bb_node->son)
    {
      son = bb_node->son;

      et_split (son);
      et_set_father (son, to_node);
    }

  if (dom_computed[dir_index] == DOM_OK)
    dom_computed[dir_index] = DOM_NO_FAST_QUERY;
}

/* Find first basic block in the tree dominating both BB1 and BB2.  */
basic_block
nearest_common_dominator (enum cdi_direction dir, basic_block bb1, basic_block bb2)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);

  gcc_assert (dom_computed[dir_index]);

  if (!bb1)
    return bb2;
  if (!bb2)
    return bb1;

  return (basic_block) et_nca (bb1->dom[dir_index], bb2->dom[dir_index])->data;
}


/* Find the nearest common dominator for the basic blocks in BLOCKS,
   using dominance direction DIR.  */

basic_block
nearest_common_dominator_for_set (enum cdi_direction dir, bitmap blocks)
{
  unsigned i, first;
  bitmap_iterator bi;
  basic_block dom;
  
  first = bitmap_first_set_bit (blocks);
  dom = BASIC_BLOCK (first);
  EXECUTE_IF_SET_IN_BITMAP (blocks, 0, i, bi)
    if (dom != BASIC_BLOCK (i))
      dom = nearest_common_dominator (dir, dom, BASIC_BLOCK (i));

  return dom;
}

/*  Given a dominator tree, we can determine whether one thing
    dominates another in constant time by using two DFS numbers:

    1. The number for when we visit a node on the way down the tree
    2. The number for when we visit a node on the way back up the tree

    You can view these as bounds for the range of dfs numbers the
    nodes in the subtree of the dominator tree rooted at that node
    will contain.
    
    The dominator tree is always a simple acyclic tree, so there are
    only three possible relations two nodes in the dominator tree have
    to each other:
    
    1. Node A is above Node B (and thus, Node A dominates node B)

     A
     |
     C
    / \
   B   D


   In the above case, DFS_Number_In of A will be <= DFS_Number_In of
   B, and DFS_Number_Out of A will be >= DFS_Number_Out of B.  This is
   because we must hit A in the dominator tree *before* B on the walk
   down, and we will hit A *after* B on the walk back up
   
   2. Node A is below node B (and thus, node B dominates node A)
   
   
     B
     |
     A
    / \
   C   D

   In the above case, DFS_Number_In of A will be >= DFS_Number_In of
   B, and DFS_Number_Out of A will be <= DFS_Number_Out of B.
   
   This is because we must hit A in the dominator tree *after* B on
   the walk down, and we will hit A *before* B on the walk back up
   
   3. Node A and B are siblings (and thus, neither dominates the other)

     C
     |
     D
    / \
   A   B

   In the above case, DFS_Number_In of A will *always* be <=
   DFS_Number_In of B, and DFS_Number_Out of A will *always* be <=
   DFS_Number_Out of B.  This is because we will always finish the dfs
   walk of one of the subtrees before the other, and thus, the dfs
   numbers for one subtree can't intersect with the range of dfs
   numbers for the other subtree.  If you swap A and B's position in
   the dominator tree, the comparison changes direction, but the point
   is that both comparisons will always go the same way if there is no
   dominance relationship.

   Thus, it is sufficient to write

   A_Dominates_B (node A, node B)
   {
     return DFS_Number_In(A) <= DFS_Number_In(B) 
            && DFS_Number_Out (A) >= DFS_Number_Out(B);
   }

   A_Dominated_by_B (node A, node B)
   {
     return DFS_Number_In(A) >= DFS_Number_In(A)
            && DFS_Number_Out (A) <= DFS_Number_Out(B);
   }  */

/* Return TRUE in case BB1 is dominated by BB2.  */
bool
dominated_by_p (enum cdi_direction dir, const_basic_block bb1, const_basic_block bb2)
{ 
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  struct et_node *n1 = bb1->dom[dir_index], *n2 = bb2->dom[dir_index];
 
  gcc_assert (dom_computed[dir_index]);

  if (dom_computed[dir_index] == DOM_OK)
    return (n1->dfs_num_in >= n2->dfs_num_in
  	    && n1->dfs_num_out <= n2->dfs_num_out);

  return et_below (n1, n2);
}

/* Returns the entry dfs number for basic block BB, in the direction DIR.  */

unsigned
bb_dom_dfs_in (enum cdi_direction dir, basic_block bb)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  struct et_node *n = bb->dom[dir_index];

  gcc_assert (dom_computed[dir_index] == DOM_OK);
  return n->dfs_num_in;
}

/* Returns the exit dfs number for basic block BB, in the direction DIR.  */

unsigned
bb_dom_dfs_out (enum cdi_direction dir, basic_block bb)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  struct et_node *n = bb->dom[dir_index];

  gcc_assert (dom_computed[dir_index] == DOM_OK);
  return n->dfs_num_out;
}

/* Verify invariants of dominator structure.  */
void
verify_dominators (enum cdi_direction dir)
{
  int err = 0;
  basic_block bb, imm_bb, imm_bb_correct;
  struct dom_info di;
  bool reverse = (dir == CDI_POST_DOMINATORS) ? true : false;

  gcc_assert (dom_info_available_p (dir));

  init_dom_info (&di, dir);
  calc_dfs_tree (&di, reverse);
  calc_idoms (&di, reverse);

  FOR_EACH_BB (bb)
    {
      imm_bb = get_immediate_dominator (dir, bb);
      if (!imm_bb)
	{
	  error ("dominator of %d status unknown", bb->index);
	  err = 1;
	}

      imm_bb_correct = di.dfs_to_bb[di.dom[di.dfs_order[bb->index]]];
      if (imm_bb != imm_bb_correct)
	{
	  error ("dominator of %d should be %d, not %d",
		 bb->index, imm_bb_correct->index, imm_bb->index);
	  err = 1;
	}
    }

  free_dom_info (&di);
  gcc_assert (!err);
}

/* Determine immediate dominator (or postdominator, according to DIR) of BB,
   assuming that dominators of other blocks are correct.  We also use it to
   recompute the dominators in a restricted area, by iterating it until it
   reaches a fixed point.  */

basic_block
recompute_dominator (enum cdi_direction dir, basic_block bb)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  basic_block dom_bb = NULL;
  edge e;
  edge_iterator ei;

  gcc_assert (dom_computed[dir_index]);

  if (dir == CDI_DOMINATORS)
    {
      FOR_EACH_EDGE (e, ei, bb->preds)
	{
	  if (!dominated_by_p (dir, e->src, bb))
	    dom_bb = nearest_common_dominator (dir, dom_bb, e->src);
	}
    }
  else
    {
      FOR_EACH_EDGE (e, ei, bb->succs)
	{
	  if (!dominated_by_p (dir, e->dest, bb))
	    dom_bb = nearest_common_dominator (dir, dom_bb, e->dest);
	}
    }

  return dom_bb;
}

/* Use simple heuristics (see iterate_fix_dominators) to determine dominators
   of BBS.  We assume that all the immediate dominators except for those of the
   blocks in BBS are correct.  If CONSERVATIVE is true, we also assume that the
   currently recorded immediate dominators of blocks in BBS really dominate the
   blocks.  The basic blocks for that we determine the dominator are removed
   from BBS.  */

static void
prune_bbs_to_update_dominators (VEC (basic_block, heap) *bbs,
				bool conservative)
{
  unsigned i;
  bool single;
  basic_block bb, dom = NULL;
  edge_iterator ei;
  edge e;

  for (i = 0; VEC_iterate (basic_block, bbs, i, bb);)
    {
      if (bb == ENTRY_BLOCK_PTR)
	goto succeed;

      if (single_pred_p (bb))
	{
	  set_immediate_dominator (CDI_DOMINATORS, bb, single_pred (bb));
	  goto succeed;
	}

      if (!conservative)
	goto fail;

      single = true;
      dom = NULL;
      FOR_EACH_EDGE (e, ei, bb->preds)
	{
	  if (dominated_by_p (CDI_DOMINATORS, e->src, bb))
	    continue;

	  if (!dom)
	    dom = e->src;
	  else
	    {
	      single = false;
	      dom = nearest_common_dominator (CDI_DOMINATORS, dom, e->src);
	    }
	}

      gcc_assert (dom != NULL);
      if (single
	  || find_edge (dom, bb))
	{
	  set_immediate_dominator (CDI_DOMINATORS, bb, dom);
	  goto succeed;
	}

fail:
      i++;
      continue;

succeed:
      VEC_unordered_remove (basic_block, bbs, i);
    }
}

/* Returns root of the dominance tree in the direction DIR that contains
   BB.  */

static basic_block
root_of_dom_tree (enum cdi_direction dir, basic_block bb)
{
  return (basic_block) et_root (bb->dom[dom_convert_dir_to_idx (dir)])->data;
}

/* See the comment in iterate_fix_dominators.  Finds the immediate dominators
   for the sons of Y, found using the SON and BROTHER arrays representing
   the dominance tree of graph G.  BBS maps the vertices of G to the basic
   blocks.  */

static void
determine_dominators_for_sons (struct graph *g, VEC (basic_block, heap) *bbs,
			       int y, int *son, int *brother)
{
  bitmap gprime;
  int i, a, nc;
  VEC (int, heap) **sccs;
  basic_block bb, dom, ybb;
  unsigned si;
  edge e;
  edge_iterator ei;

  if (son[y] == -1)
    return;
  if (y == (int) VEC_length (basic_block, bbs))
    ybb = ENTRY_BLOCK_PTR;
  else
    ybb = VEC_index (basic_block, bbs, y);

  if (brother[son[y]] == -1)
    {
      /* Handle the common case Y has just one son specially.  */
      bb = VEC_index (basic_block, bbs, son[y]);
      set_immediate_dominator (CDI_DOMINATORS, bb,
			       recompute_dominator (CDI_DOMINATORS, bb));
      identify_vertices (g, y, son[y]);
      return;
    }

  gprime = BITMAP_ALLOC (NULL);
  for (a = son[y]; a != -1; a = brother[a])
    bitmap_set_bit (gprime, a);

  nc = graphds_scc (g, gprime);
  BITMAP_FREE (gprime);

  sccs = XCNEWVEC (VEC (int, heap) *, nc);
  for (a = son[y]; a != -1; a = brother[a])
    VEC_safe_push (int, heap, sccs[g->vertices[a].component], a);

  for (i = nc - 1; i >= 0; i--)
    {
      dom = NULL;
      for (si = 0; VEC_iterate (int, sccs[i], si, a); si++)
	{
	  bb = VEC_index (basic_block, bbs, a);
	  FOR_EACH_EDGE (e, ei, bb->preds)
	    {
	      if (root_of_dom_tree (CDI_DOMINATORS, e->src) != ybb)
		continue;

	      dom = nearest_common_dominator (CDI_DOMINATORS, dom, e->src);
	    }
	}

      gcc_assert (dom != NULL);
      for (si = 0; VEC_iterate (int, sccs[i], si, a); si++)
	{
	  bb = VEC_index (basic_block, bbs, a);
	  set_immediate_dominator (CDI_DOMINATORS, bb, dom);
	}
    }

  for (i = 0; i < nc; i++)
    VEC_free (int, heap, sccs[i]);
  free (sccs);

  for (a = son[y]; a != -1; a = brother[a])
    identify_vertices (g, y, a);
}

/* Recompute dominance information for basic blocks in the set BBS.  The
   function assumes that the immediate dominators of all the other blocks
   in CFG are correct, and that there are no unreachable blocks.

   If CONSERVATIVE is true, we additionally assume that all the ancestors of
   a block of BBS in the current dominance tree dominate it.  */

void
iterate_fix_dominators (enum cdi_direction dir, VEC (basic_block, heap) *bbs,
			bool conservative)
{
  unsigned i;
  basic_block bb, dom;
  struct graph *g;
  int n, y;
  size_t dom_i;
  edge e;
  edge_iterator ei;
  struct pointer_map_t *map;
  int *parent, *son, *brother;
  unsigned int dir_index = dom_convert_dir_to_idx (dir);

  /* We only support updating dominators.  There are some problems with
     updating postdominators (need to add fake edges from infinite loops
     and noreturn functions), and since we do not currently use
     iterate_fix_dominators for postdominators, any attempt to handle these
     problems would be unused, untested, and almost surely buggy.  We keep
     the DIR argument for consistency with the rest of the dominator analysis
     interface.  */
  gcc_assert (dir == CDI_DOMINATORS);
  gcc_assert (dom_computed[dir_index]);

  /* The algorithm we use takes inspiration from the following papers, although
     the details are quite different from any of them:

     [1] G. Ramalingam, T. Reps, An Incremental Algorithm for Maintaining the
	 Dominator Tree of a Reducible Flowgraph
     [2]  V. C. Sreedhar, G. R. Gao, Y.-F. Lee: Incremental computation of
	  dominator trees
     [3]  K. D. Cooper, T. J. Harvey and K. Kennedy: A Simple, Fast Dominance
	  Algorithm

     First, we use the following heuristics to decrease the size of the BBS
     set:
       a) if BB has a single predecessor, then its immediate dominator is this
	  predecessor
       additionally, if CONSERVATIVE is true:
       b) if all the predecessors of BB except for one (X) are dominated by BB,
	  then X is the immediate dominator of BB
       c) if the nearest common ancestor of the predecessors of BB is X and
	  X -> BB is an edge in CFG, then X is the immediate dominator of BB

     Then, we need to establish the dominance relation among the basic blocks
     in BBS.  We split the dominance tree by removing the immediate dominator
     edges from BBS, creating a forest F.  We form a graph G whose vertices
     are BBS and ENTRY and X -> Y is an edge of G if there exists an edge
     X' -> Y in CFG such that X' belongs to the tree of the dominance forest
     whose root is X.  We then determine dominance tree of G.  Note that
     for X, Y in BBS, X dominates Y in CFG if and only if X dominates Y in G.
     In this step, we can use arbitrary algorithm to determine dominators.
     We decided to prefer the algorithm [3] to the algorithm of
     Lengauer and Tarjan, since the set BBS is usually small (rarely exceeding
     10 during gcc bootstrap), and [3] should perform better in this case.

     Finally, we need to determine the immediate dominators for the basic
     blocks of BBS.  If the immediate dominator of X in G is Y, then
     the immediate dominator of X in CFG belongs to the tree of F rooted in
     Y.  We process the dominator tree T of G recursively, starting from leaves.
     Suppose that X_1, X_2, ..., X_k are the sons of Y in T, and that the
     subtrees of the dominance tree of CFG rooted in X_i are already correct.
     Let G' be the subgraph of G induced by {X_1, X_2, ..., X_k}.  We make
     the following observations:
       (i) the immediate dominator of all blocks in a strongly connected
	   component of G' is the same
       (ii) if X has no predecessors in G', then the immediate dominator of X
	    is the nearest common ancestor of the predecessors of X in the
	    subtree of F rooted in Y
     Therefore, it suffices to find the topological ordering of G', and
     process the nodes X_i in this order using the rules (i) and (ii).
     Then, we contract all the nodes X_i with Y in G, so that the further
     steps work correctly.  */

  if (!conservative)
    {
      /* Split the tree now.  If the idoms of blocks in BBS are not
	 conservatively correct, setting the dominators using the
	 heuristics in prune_bbs_to_update_dominators could
	 create cycles in the dominance "tree", and cause ICE.  */
      for (i = 0; VEC_iterate (basic_block, bbs, i, bb); i++)
	set_immediate_dominator (CDI_DOMINATORS, bb, NULL);
    }

  prune_bbs_to_update_dominators (bbs, conservative);
  n = VEC_length (basic_block, bbs);

  if (n == 0)
    return;

  if (n == 1)
    {
      bb = VEC_index (basic_block, bbs, 0);
      set_immediate_dominator (CDI_DOMINATORS, bb,
			       recompute_dominator (CDI_DOMINATORS, bb));
      return;
    }

  /* Construct the graph G.  */
  map = pointer_map_create ();
  for (i = 0; VEC_iterate (basic_block, bbs, i, bb); i++)
    {
      /* If the dominance tree is conservatively correct, split it now.  */
      if (conservative)
	set_immediate_dominator (CDI_DOMINATORS, bb, NULL);
      *pointer_map_insert (map, bb) = (void *) (size_t) i;
    }
  *pointer_map_insert (map, ENTRY_BLOCK_PTR) = (void *) (size_t) n;

  g = new_graph (n + 1);
  for (y = 0; y < g->n_vertices; y++)
    g->vertices[y].data = BITMAP_ALLOC (NULL);
  for (i = 0; VEC_iterate (basic_block, bbs, i, bb); i++)
    {
      FOR_EACH_EDGE (e, ei, bb->preds)
	{
	  dom = root_of_dom_tree (CDI_DOMINATORS, e->src);
	  if (dom == bb)
	    continue;

	  dom_i = (size_t) *pointer_map_contains (map, dom);

	  /* Do not include parallel edges to G.  */
	  if (bitmap_bit_p ((bitmap) g->vertices[dom_i].data, i))
	    continue;

	  bitmap_set_bit ((bitmap) g->vertices[dom_i].data, i);
	  add_edge (g, dom_i, i);
	}
    }
  for (y = 0; y < g->n_vertices; y++)
    BITMAP_FREE (g->vertices[y].data);
  pointer_map_destroy (map);

  /* Find the dominator tree of G.  */
  son = XNEWVEC (int, n + 1);
  brother = XNEWVEC (int, n + 1);
  parent = XNEWVEC (int, n + 1);
  graphds_domtree (g, n, parent, son, brother);

  /* Finally, traverse the tree and find the immediate dominators.  */
  for (y = n; son[y] != -1; y = son[y])
    continue;
  while (y != -1)
    {
      determine_dominators_for_sons (g, bbs, y, son, brother);

      if (brother[y] != -1)
	{
	  y = brother[y];
	  while (son[y] != -1)
	    y = son[y];
	}
      else
	y = parent[y];
    }

  free (son);
  free (brother);
  free (parent);

  free_graph (g);
}

void
add_to_dominance_info (enum cdi_direction dir, basic_block bb)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);

  gcc_assert (dom_computed[dir_index]);
  gcc_assert (!bb->dom[dir_index]);

  n_bbs_in_dom_tree[dir_index]++;
  
  bb->dom[dir_index] = et_new_tree (bb);

  if (dom_computed[dir_index] == DOM_OK)
    dom_computed[dir_index] = DOM_NO_FAST_QUERY;
}

void
delete_from_dominance_info (enum cdi_direction dir, basic_block bb)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);

  gcc_assert (dom_computed[dir_index]);

  et_free_tree (bb->dom[dir_index]);
  bb->dom[dir_index] = NULL;
  n_bbs_in_dom_tree[dir_index]--;

  if (dom_computed[dir_index] == DOM_OK)
    dom_computed[dir_index] = DOM_NO_FAST_QUERY;
}

/* Returns the first son of BB in the dominator or postdominator tree
   as determined by DIR.  */

basic_block
first_dom_son (enum cdi_direction dir, basic_block bb)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  struct et_node *son = bb->dom[dir_index]->son;

  return (basic_block) (son ? son->data : NULL);
}

/* Returns the next dominance son after BB in the dominator or postdominator
   tree as determined by DIR, or NULL if it was the last one.  */

basic_block
next_dom_son (enum cdi_direction dir, basic_block bb)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);
  struct et_node *next = bb->dom[dir_index]->right;

  return (basic_block) (next->father->son == next ? NULL : next->data);
}

/* Return dominance availability for dominance info DIR.  */

enum dom_state
dom_info_state (enum cdi_direction dir)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);

  return dom_computed[dir_index];
}

/* Set the dominance availability for dominance info DIR to NEW_STATE.  */

void
set_dom_info_availability (enum cdi_direction dir, enum dom_state new_state)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);

  dom_computed[dir_index] = new_state;
}

/* Returns true if dominance information for direction DIR is available.  */

bool
dom_info_available_p (enum cdi_direction dir)
{
  unsigned int dir_index = dom_convert_dir_to_idx (dir);

  return dom_computed[dir_index] != DOM_NONE;
}

void
debug_dominance_info (enum cdi_direction dir)
{
  basic_block bb, bb2;
  FOR_EACH_BB (bb)
    if ((bb2 = get_immediate_dominator (dir, bb)))
      fprintf (stderr, "%i %i\n", bb->index, bb2->index);
}

/* Prints to stderr representation of the dominance tree (for direction DIR)
   rooted in ROOT, indented by INDENT tabulators.  If INDENT_FIRST is false,
   the first line of the output is not indented.  */

static void
debug_dominance_tree_1 (enum cdi_direction dir, basic_block root,
			unsigned indent, bool indent_first)
{
  basic_block son;
  unsigned i;
  bool first = true;

  if (indent_first)
    for (i = 0; i < indent; i++)
      fprintf (stderr, "\t");
  fprintf (stderr, "%d\t", root->index);

  for (son = first_dom_son (dir, root);
       son;
       son = next_dom_son (dir, son))
    {
      debug_dominance_tree_1 (dir, son, indent + 1, !first);
      first = false;
    }

  if (first)
    fprintf (stderr, "\n");
}

/* Prints to stderr representation of the dominance tree (for direction DIR)
   rooted in ROOT.  */

void
debug_dominance_tree (enum cdi_direction dir, basic_block root)
{
  debug_dominance_tree_1 (dir, root, 0, false);
}
