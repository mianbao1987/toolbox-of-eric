#include <stdio.h>
#include <stdlib.h>
#include "libiberty.h"
#include "common.h"

const char *program_name;

int
usage (void)
{
  printf ("usage: %s <cfg_file>\n", program_name);
  return 0;
}

extern int yyparse (void);
extern FILE *yyin;

basic_block
cfg_find_basic_block (char *name)
{
  int i;
  basic_block b;

  for (i = 0; i < n_basic_blocks; i++)
    {
      if (strcmp (BASIC_BLOCK (i)->name, name) == 0)
        return BASIC_BLOCK (i);
    }
  return NULL;
}

basic_block
cfg_add_basic_block (char *name)
{
  basic_block bb;

  bb = cfg_find_basic_block (name);
  if (bb != NULL)
    return bb;

  bb = (basic_block) xmalloc (sizeof (struct basic_block_def));
  bb->index = last_basic_block++;
  bb->name = name;
  bb->preds = bb->succs = NULL;
  VEC_safe_push (basic_block, heap, basic_block_info, bb);  
  n_basic_blocks++;

  return bb;
}

edge
cfg_add_edge (char *srcname, char *destname)
{
  edge e;

  e = (edge) xmalloc (sizeof (struct edge_def));
  e->src = cfg_add_basic_block (srcname);
  e->dest = cfg_add_basic_block (destname);
  VEC_safe_push (edge, heap, e->src->succs, e);  
  VEC_safe_push (edge, heap, e->dest->preds, e);  
  n_edges++;
   
  return e;
}

int
init_cfg (char *filename)
{
  yyin = fopen (filename, "r"); 
  if (yyin == NULL)
    return -1;

  cfg = (control_flow_graph) xmalloc (sizeof (struct control_flow_graph_def));
  n_basic_blocks = 0;
  n_edges = 0;
  last_basic_block = 0;

  yyparse ();

  ENTRY_BLOCK_PTR = BASIC_BLOCK (0);
  EXIT_BLOCK_PTR = BASIC_BLOCK (1);

  return 0;
}

extern int yydebug;

int
main (int argc, char *argv[])
{
  int i;
  char **dfs;

  program_name = argv[0];
  //yydebug = 1;

  /* simple option format */  
  if (argc != 2)
    return usage ();
  /* suppose argv[1] is a file */
  if (init_cfg (argv[1]) != 0)
    return usage ();

  init_dom_info (&di);
  calc_dfs_tree (&di);

  dfs = 

  printf ("dfs: ");
  for (i = 2; i < n_basic_blocks; i++)
    {
      printf ("%d ", di.dfs_order[i]);
    }
  printf ("\n");

  return 0;
}

