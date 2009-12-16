
#include "common.h"

struct dom_info di;

/* Helper macro for allocating and initializing an array,
   for aesthetic reasons.  */
#define init_ar(var, type, num, content)			\
  do								\
    {								\
      unsigned int i = 1;    /* Catch content == i.  */		\
      if (! (content))						\
	(var) = XCNEWVEC (type, num);				\
      else							\
	{							\
	  (var) = XNEWVEC (type, (num));			\
	  for (i = 0; i < num; i++)				\
	    (var)[i] = (content);				\
	}							\
    }								\
  while (0)

/* Allocate all needed memory in a pessimistic fashion (so we round up).
   This initializes the contents of DI, which already must be allocated.  */

void
init_dom_info (struct dom_info *di)
{
  /* We need memory for n_basic_blocks nodes.  */
  unsigned int num = n_basic_blocks;
  init_ar (di->dfs_parent, TBB, num, 0);
  init_ar (di->path_min, TBB, num, i);
  init_ar (di->key, TBB, num, i);
  init_ar (di->dom, TBB, num, 0);

  init_ar (di->bucket, TBB, num, 0);
  init_ar (di->next_bucket, TBB, num, 0);

  init_ar (di->set_chain, TBB, num, 0);
  init_ar (di->set_size, unsigned int, num, 1);
  init_ar (di->set_child, TBB, num, 0);

  init_ar (di->dfs_order, TBB, (unsigned int) last_basic_block + 1, 0);
  init_ar (di->dfs_to_bb, basic_block, num, 0);

  di->dfsnum = 1;
  di->nodes = 0;
}

#undef init_ar

/* The nonrecursive variant of creating a DFS tree.  DI is our working
   structure, BB the starting basic block for this tree. After this is
   done all nodes reachable from BB were visited, have assigned their 
   dfs number and are linked together to form a tree.  */

static void
calc_dfs_tree_nonrec (struct dom_info *di, basic_block bb)
{
  /* We call this _only_ if bb is not already visited.  */
  edge e;
  TBB child_i, my_i = 0;
  edge_iterator *stack;
  edge_iterator ei, einext;
  int sp;
  /* Start block (ENTRY_BLOCK_PTR for forward problem, EXIT_BLOCK for backward
     problem).  */
  basic_block en_block;
  /* Ending block.  */
  basic_block ex_block;

  stack = XNEWVEC (edge_iterator, n_basic_blocks + 1);
  sp = 0;

  /* Initialize our border blocks, and the first edge.  */
  ei = ei_start (bb->succs);
  en_block = ENTRY_BLOCK_PTR;
  ex_block = EXIT_BLOCK_PTR;

  /* When the stack is empty we break out of this loop.  */
  while (1)
    {
      basic_block bn;

      /* This loop traverses edges e in depth first manner, and fills the
         stack.  */
      while (!ei_end_p (ei))
	{
	  e = ei_edge (ei);

	  /* Deduce from E the current and the next block (BB and BN), and the
	     next edge.  */
	  bn = e->dest;
	  if (bn == ex_block || di->dfs_order[bn->index])
	    {
	      ei_next (&ei);
	      continue;
            }
          bb = e->src;
          einext = ei_start (bn->succs);

	  assert (bn != en_block);

	  /* Fill the DFS tree info calculatable _before_ recursing.  */
	  if (bb != en_block)
	    my_i = di->dfs_order[bb->index];
	  else
	    my_i = di->dfs_order[last_basic_block];
	  child_i = di->dfs_order[bn->index] = di->dfsnum++;
	  di->dfs_to_bb[child_i] = bn;
	  di->dfs_parent[child_i] = my_i;

	  /* Save the current point in the CFG on the stack, and recurse.  */
	  stack[sp++] = ei;
	  ei = einext;
	}

      if (!sp)
	break;
      ei = stack[--sp];

      /* OK.  The edge-list was exhausted, meaning normally we would
         end the recursion.  After returning from the recursive call,
         there were (may be) other statements which were run after a
         child node was completely considered by DFS.  Here is the
         point to do it in the non-recursive variant.
         E.g. The block just completed is in e->dest for forward DFS,
         the block not yet completed (the parent of the one above)
         in e->src.  This could be used e.g. for computing the number of
         descendants or the tree depth.  */
      ei_next (&ei);
    }
  free (stack);
}

void
calc_dfs_tree (struct dom_info *di)
{
  /* The first block is the ENTRY_BLOCK . */
  basic_block begin = ENTRY_BLOCK_PTR;
  di->dfs_order[last_basic_block] = di->dfsnum;
  di->dfs_to_bb[di->dfsnum] = begin;
  di->dfsnum++;

  calc_dfs_tree_nonrec (di, begin);

  di->nodes = di->dfsnum - 1;

  /* This aborts e.g. when there is _no_ path from ENTRY to EXIT at all.  */
  assert (di->nodes == (unsigned int) n_basic_blocks - 1);
}
