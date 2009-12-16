#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <assert.h>
#include "libiberty.h"

typedef int bool;
typedef struct basic_block_def *basic_block;
typedef struct edge_def *edge;

#define true 1
#define false 0

#define MEM_STAT_DECL
#define ALONE_MEM_STAT_DECL void
#define PASS_MEM_STAT
#define ALONE_PASS_MEM_STAT
#define MEM_STAT_INFO
#define ALONE_MEM_STAT_INFO

#include "vec.h"

DEF_VEC_P(basic_block);
DEF_VEC_ALLOC_P(basic_block,heap);

DEF_VEC_P(edge);
DEF_VEC_ALLOC_P(edge,heap);

struct basic_block_def {
  int index;
  char *name;
  VEC(edge,heap) *preds;
  VEC(edge,heap) *succs; 
};

struct edge_def {
  basic_block src;
  basic_block dest;
};

/* Iterator object for edges.  */

typedef struct {
  unsigned index;
  VEC(edge,heap) **container;
} edge_iterator;

struct control_flow_graph_def
{
  /* Block pointers for the exit and entry of a function.
     These are always the head and tail of the basic block list.  */
  basic_block x_entry_block_ptr;
  basic_block x_exit_block_ptr;
  /* Index by basic block number, get basic block struct info.  */
  VEC(basic_block,heap) *x_basic_block_info;
  /* Number of basic blocks in this flow graph.  */
  int x_n_basic_blocks;
  /* Number of edges in this flow graph.  */
  int x_n_edges;
  /* The first free basic block number.  */
  int x_last_basic_block;
};
typedef struct control_flow_graph_def *control_flow_graph;

#define EDGE_COUNT(ev) VEC_length (edge, (ev))
#define EDGE_I(ev,i)                    VEC_index  (edge, (ev), (i))

static inline VEC(edge,heap) *   
ei_container (edge_iterator i)                
{                                      
  assert (i.container);                             
  return *i.container;                                     
} 

/* Return the edge pointed to by the iterator `i'.  */
static inline edge
ei_edge (edge_iterator i)
{
  return EDGE_I (ei_container (i), i.index);
}

#define ei_start(iter) ei_start_1 (&(iter))
#define ei_last(iter) ei_last_1 (&(iter))
  
/* Return an iterator pointing to the start of an edge vector.  */
static inline edge_iterator
ei_start_1 (VEC(edge,heap) **ev)
{ 
  edge_iterator i;
    
  i.index = 0;
  i.container = ev;

  return i;
} 
                                                    
/* Return an iterator pointing to the last element of an edge               
   vector.  */                                 
static inline edge_iterator                                
ei_last_1 (VEC(edge,heap) **ev)                                  
{                                              
  edge_iterator i;                                    
                                                      
  i.index = EDGE_COUNT (*ev) - 1;                                  
  i.container = ev;                                                        
                                                     
  return i;                                               
}                                                               
                                                                                          
/* Is the iterator `i' at the end of the sequence?  */                  
static inline bool                                        
ei_end_p (edge_iterator i)                               
{                                                                    
  return (i.index == EDGE_COUNT (ei_container (i)));                       
}                                                             
                 
/* Advance the iterator to the next element.  */                   
static inline void                                          
ei_next (edge_iterator *i)                                    
{
  assert (i->index < EDGE_COUNT (ei_container (*i)));             
  i->index++;
}

control_flow_graph cfg;

#define ENTRY_BLOCK_PTR         (cfg->x_entry_block_ptr)
#define EXIT_BLOCK_PTR          (cfg->x_exit_block_ptr)
#define basic_block_info        (cfg->x_basic_block_info)
#define n_basic_blocks          (cfg->x_n_basic_blocks)
#define n_edges                 (cfg->x_n_edges)
#define last_basic_block        (cfg->x_last_basic_block)

/* Special block numbers [markers] for entry and exit.  */
#define ENTRY_BLOCK (0)
#define EXIT_BLOCK (1)

#define BASIC_BLOCK(N)          (VEC_index (basic_block, basic_block_info, (N)))          
#define SET_BASIC_BLOCK(N,BB)   (VEC_replace (basic_block, basic_block_info, (N), (BB)))

/* We name our nodes with integers, beginning with 1.  Zero is reserved for
   'undefined' or 'end of list'.  The name of each node is given by the dfs
   number of the corresponding basic block.  Please note, that we include the
   artificial ENTRY_BLOCK (or EXIT_BLOCK in the post-dom case) in our lists to
   support multiple entry points.  Its dfs number is of course 1.  */

/* Type of Basic Block aka. TBB */
typedef unsigned int TBB;

/* We work in a poor-mans object oriented fashion, and carry an instance of
   this structure through all our 'methods'.  It holds various arrays
   reflecting the (sub)structure of the flowgraph.  Most of them are of type
   TBB and are also indexed by TBB.  */

struct dom_info
{
  /* The parent of a node in the DFS tree.  */
  TBB *dfs_parent;
  /* For a node x key[x] is roughly the node nearest to the root from which
     exists a way to x only over nodes behind x.  Such a node is also called
     semidominator.  */
  TBB *key;
  /* The value in path_min[x] is the node y on the path from x to the root of
     the tree x is in with the smallest key[y].  */
  TBB *path_min;
  /* bucket[x] points to the first node of the set of nodes having x as key.  */
  TBB *bucket;
  /* And next_bucket[x] points to the next node.  */
  TBB *next_bucket;
  /* After the algorithm is done, dom[x] contains the immediate dominator
     of x.  */
  TBB *dom;

  /* The following few fields implement the structures needed for disjoint
     sets.  */
  /* set_chain[x] is the next node on the path from x to the representative
     of the set containing x.  If set_chain[x]==0 then x is a root.  */
  TBB *set_chain;
  /* set_size[x] is the number of elements in the set named by x.  */
  unsigned int *set_size;
  /* set_child[x] is used for balancing the tree representing a set.  It can
     be understood as the next sibling of x.  */
  TBB *set_child;

  /* If b is the number of a basic block (BB->index), dfs_order[b] is the
     number of that node in DFS order counted from 1.  This is an index
     into most of the other arrays in this structure.  */
  TBB *dfs_order;
  /* If x is the DFS-index of a node which corresponds with a basic block,
     dfs_to_bb[x] is that basic block.  Note, that in our structure there are
     more nodes that basic blocks, so only dfs_to_bb[dfs_order[bb->index]]==bb
     is true for every basic block bb, but not the opposite.  */
  basic_block *dfs_to_bb;

  /* This is the next free DFS number when creating the DFS tree.  */
  unsigned int dfsnum;
  /* The number of nodes in the DFS tree (==dfsnum-1).  */
  unsigned int nodes;
};

extern struct dom_info di;

#endif

