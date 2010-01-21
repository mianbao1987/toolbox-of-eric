/* Output vcg description file according to the tree dump file.

   Copyright (C) 2009 Eric Fisher, joefoxreal@gmail.com. 

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <unistd.h>
#include <error.h>
#include <libiberty.h>
#include <obstack.h>

#include <argp.h>

#include "gdl.h"
#include "tree2vcg.h"

enum cfg_edge_type
{
  UNKNOWN_EDGE,
  DFST_EDGE,
  ADVANCING_EDGE,
  RETREATING_EDGE,
  CROSS_EDGE
};

struct cfg_edge
{
  int source_index;
  int target_index;
  enum cfg_edge_type type;
};

struct cfg_node
{
  int pred_num;
  int succ_num;
  //struct gdl_graph *entry;
  struct cfg_edge **preds;
  struct cfg_edge **succs;
  int visited;
  int dfs_order;
};

struct cfg_graph
{
  int node_num;
  struct cfg_node **nodes;
};

struct cfg_graph *graph;

void
init_cfg (void)
{
  int i;
  struct cfg_node *node;

  graph = (struct cfg_graph *) xmalloc (sizeof (struct cfg_graph));
  graph->node_num = 16;
  graph->nodes = (struct cfg_node **) 
                 xmalloc (sizeof (struct cfg_node *) * graph->node_num);

  i = 0;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 0;
  node->succ_num = 1;
  node->succs = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 2;
  node->succs[0]->type = UNKNOWN_EDGE;

  i = 1;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[1];
  node->pred_num = 1;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 15;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->succ_num = 0;

  i = 2;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 1;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 0;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->succ_num = 2;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 3;
  node->succs[0]->type = UNKNOWN_EDGE;
  node->succs[1] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[1]->source_index = i;
  node->succs[1]->target_index = 7;
  node->succs[1]->type = UNKNOWN_EDGE;

  i = 3;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 1;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 2;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->succ_num = 2;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 4;
  node->succs[0]->type = UNKNOWN_EDGE;
  node->succs[1] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[1]->source_index = i;
  node->succs[1]->target_index = 13;
  node->succs[1]->type = UNKNOWN_EDGE;

  i = 4;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 1;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 3;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->succ_num = 2;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 5;
  node->succs[0]->type = UNKNOWN_EDGE;
  node->succs[1] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[1]->source_index = i;
  node->succs[1]->target_index = 13;
  node->succs[1]->type = UNKNOWN_EDGE;

  i = 5;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 2;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 4;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->preds[1] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[1]->source_index = 6;
  node->preds[1]->target_index = i;
  node->preds[1]->type = UNKNOWN_EDGE;
  node->succ_num = 2;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 6;
  node->succs[0]->type = UNKNOWN_EDGE;
  node->succs[1] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[1]->source_index = i;
  node->succs[1]->target_index = 13;
  node->succs[1]->type = UNKNOWN_EDGE;

  i = 6;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 1;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 5;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->succ_num = 2;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 5;
  node->succs[0]->type = UNKNOWN_EDGE;
  node->succs[1] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[1]->source_index = i;
  node->succs[1]->target_index = 13;
  node->succs[1]->type = UNKNOWN_EDGE;

  i = 7;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 1;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 2;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->succ_num = 2;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 8;
  node->succs[0]->type = UNKNOWN_EDGE;
  node->succs[1] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[1]->source_index = i;
  node->succs[1]->target_index = 11;
  node->succs[1]->type = UNKNOWN_EDGE;

  i = 8;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 1;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 7;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->succ_num = 2;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 9;
  node->succs[0]->type = UNKNOWN_EDGE;
  node->succs[1] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[1]->source_index = i;
  node->succs[1]->target_index = 11;
  node->succs[1]->type = UNKNOWN_EDGE;

  i = 9;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 2;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 8;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->preds[1] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[1]->source_index = 10;
  node->preds[1]->target_index = i;
  node->preds[1]->type = UNKNOWN_EDGE;
  node->succ_num = 2;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 10;
  node->succs[0]->type = UNKNOWN_EDGE;
  node->succs[1] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[1]->source_index = i;
  node->succs[1]->target_index = 11;
  node->succs[1]->type = UNKNOWN_EDGE;

  i = 10;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 1;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 9;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->succ_num = 2;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 9;
  node->succs[0]->type = UNKNOWN_EDGE;
  node->succs[1] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[1]->source_index = i;
  node->succs[1]->target_index = 11;
  node->succs[1]->type = UNKNOWN_EDGE;

  i = 11;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 4;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 7;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->preds[1] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[1]->source_index = 8;
  node->preds[1]->target_index = i;
  node->preds[1]->type = UNKNOWN_EDGE;
  node->preds[2] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[2]->source_index = 9;
  node->preds[2]->target_index = i;
  node->preds[2]->type = UNKNOWN_EDGE;
  node->preds[3] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[3]->source_index = 10;
  node->preds[3]->target_index = i;
  node->preds[3]->type = UNKNOWN_EDGE;
  node->succ_num = 2;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 12;
  node->succs[0]->type = UNKNOWN_EDGE;
  node->succs[1] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[1]->source_index = i;
  node->succs[1]->target_index = 13;
  node->succs[1]->type = UNKNOWN_EDGE;

  i = 12;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 1;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 11;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->succ_num = 1;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 13;
  node->succs[0]->type = UNKNOWN_EDGE;

  i = 13;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 6;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 3;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->preds[1] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[1]->source_index = 4;
  node->preds[1]->target_index = i;
  node->preds[1]->type = UNKNOWN_EDGE;
  node->preds[2] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[2]->source_index = 5;
  node->preds[2]->target_index = i;
  node->preds[2]->type = UNKNOWN_EDGE;
  node->preds[3] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[3]->source_index = 6;
  node->preds[3]->target_index = i;
  node->preds[3]->type = UNKNOWN_EDGE;
  node->preds[4] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[4]->source_index = 11;
  node->preds[4]->target_index = i;
  node->preds[4]->type = UNKNOWN_EDGE;
  node->preds[5] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[5]->source_index = 12;
  node->preds[5]->target_index = i;
  node->preds[5]->type = UNKNOWN_EDGE;
  node->succ_num = 2;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 14;
  node->succs[0]->type = UNKNOWN_EDGE;
  node->succs[1] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[1]->source_index = i;
  node->succs[1]->target_index = 15;
  node->succs[1]->type = UNKNOWN_EDGE;

  i = 14;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 1;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 13;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->succ_num = 1;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 15;
  node->succs[0]->type = UNKNOWN_EDGE;

  i = 15;
  graph->nodes[i] = (struct cfg_node *) xmalloc (sizeof (struct cfg_node));
  node = graph->nodes[i];
  node->pred_num = 2;
  node->preds = (struct cfg_edge **)
                xmalloc (sizeof (struct cfg_edge) * node->pred_num);
  node->preds[0] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[0]->source_index = 13;
  node->preds[0]->target_index = i;
  node->preds[0]->type = UNKNOWN_EDGE;
  node->preds[1] = (struct cfg_edge *) xmalloc  (sizeof (struct cfg_edge));
  node->preds[1]->source_index = 14;
  node->preds[1]->target_index = i;
  node->preds[1]->type = UNKNOWN_EDGE;
  node->succ_num = 1;
  node->succs = (struct cfg_edge **)
                 xmalloc (sizeof (struct cfg_edge) * node->succ_num);
  node->succs[0] = (struct cfg_edge *) xmalloc (sizeof (struct cfg_edge));
  node->succs[0]->source_index = i;
  node->succs[0]->target_index = 1;
  node->succs[0]->type = UNKNOWN_EDGE;
}

int count;

void
search (int n)
{
  int i, j;
  struct cfg_node *node, *succ_node;
  struct cfg_edge *edge;

  node = graph->nodes[n];
  node->visited = 1;

  for (i = 0; i < node->succ_num; i++)
    {
      edge = node->succs[i];
      succ_node = graph->nodes[edge->target_index];
      if (succ_node->visited == 0)
        {
          edge->type = DFST_EDGE;
          for (j = 0; j < succ_node->pred_num; j++)
            {
              if (succ_node->preds[j]->source_index == n)
                succ_node->preds[j]->type = DFST_EDGE;
            }
          search (edge->target_index);
        }
    }
  node->dfs_order = count;
  count--;
}

void
depth_first_search (void)
{
  int i;

  for (i = 0; i < graph->node_num; i++)
    {
      graph->nodes[i]->visited = 0;
    }

  count = graph->node_num;
  search (0);
}

int
is_ancestor (int source, int target)
{
  int i;
  int index;
  struct cfg_node *node;
  struct cfg_edge *edge;  

  index = target;
  node = graph->nodes[index];
  do
    {
      if (index == source)
        return 1;
      
      for (i = 0;  i < node->pred_num; i++)
        {
          edge = node->preds[i];
          if (edge->type == DFST_EDGE)
            {
              index = edge->source_index;
              node = graph->nodes[index];
              break;
            }
        }
    } while (index != 0);

  return 0;
}

void
mark_edge (struct cfg_edge *edge)
{
  int source_index, target_index;

  source_index = edge->source_index;
  target_index = edge->target_index;

  if (is_ancestor (source_index, target_index))
    edge->type = ADVANCING_EDGE;
  else if (is_ancestor (target_index, source_index))
    edge->type = RETREATING_EDGE;
  else
    edge->type = CROSS_EDGE;
}

void
mark_other_edges (void)
{
  int i, j;
  struct cfg_node *node;
  struct cfg_edge *edge;

  for (i = 0; i < graph->node_num; i++)
    {
      node = graph->nodes[i];
      for (j = 0; j < node->succ_num; j++)
        {
          edge = node->succs[j];
          if (edge->type == UNKNOWN_EDGE)
            {
              mark_edge (edge);
            }
        }
    }
}

void
calc_vertical_order (void)
{
  int i, j;
  struct cfg_node *node;
  struct cfg_edge *edge;

  init_cfg ();

  depth_first_search ();

  mark_other_edges ();

  for (i = 0; i < graph->node_num; i++)
    {
      node = graph->nodes[i];
      printf ("node: %d\n", i);
      printf ("dfs order: %d\n", node->dfs_order);
      for (j = 0; j < node->succ_num; j++)
        {
          edge = node->succs[j];
          if (edge->type == DFST_EDGE)
            printf ("edge type: dfst\n");

          if (edge->type == ADVANCING_EDGE)
            printf ("edge type: advancing\n");

          if (edge->type == RETREATING_EDGE)
            printf ("edge type: retreating\n");

          if (edge->type == CROSS_EDGE)
            printf ("edge type: cross\n");

          if (edge->type == UNKNOWN_EDGE)
            printf ("edge type: unknown\n");

          printf ("edge: %d -> %d\n", edge->source_index,
                  edge->target_index);
        }
    }  
}

int
main (void)
{
  calc_vertical_order ();

  return 0; 
}

#if 0
void
fine_tune_graph (void)
{
  struct gdl_graph *fun_graph, *bb_graph;

  /* common attributes */
  set_graph_node_color (top_graph, LIGHTGREY);
  set_graph_node_shape (top_graph, ELLIPSE);
  set_graph_layoutalgorithm (top_graph, MAX_DEPTH);

  set_graph_folding (top_graph, 0);
  for (fun_graph = top_graph->subgraphs; fun_graph; fun_graph = fun_graph->next)
    {
      for (bb_graph = fun_graph->subgraphs; bb_graph; bb_graph = bb_graph->next)
        {
          set_graph_folding (bb_graph, 1);
        }
      set_graph_folding (fun_graph, 1);
    }

  calc_vertical_order ();
}
#endif
