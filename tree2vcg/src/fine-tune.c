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
#include "cfg.h"
#include "tree2vcg.h"

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
mark_edges (void)
{
  int i, j;
  struct cfg_node *node;
  struct cfg_edge *edge;

  for (i = 0; i < graph->node_num; i++)
    {
      node = graph->nodes[i];
      for (j = 0; j < node->pred_num; j++)
        {
          edge = node->preds[j];
          if (edge->type == UNKNOWN_EDGE)
            {
              mark_edge (edge);
            }
        }
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

int
calc_vertical_order (struct cfg_node *node)
{
  int i;
  int val, max = 0;
  struct cfg_node *pred_node;
  struct cfg_edge *edge;

  if (node->vertical_order == 0)
    {
      for (i = 0; i < node->pred_num; i++)
        {
          edge = node->preds[i];
          if (edge->type == RETREATING_EDGE)
            continue;
          val = calc_vertical_order (graph->nodes[edge->source_index]);
          max = max > val ? max : val;
        }
      node->vertical_order = max + 1;
    }
  return node->vertical_order;
}

void
set_vertical_order (void)
{
  int i, j;
  struct cfg_node *node;
  struct cfg_edge *edge;

  init_cfg ();

  depth_first_search ();

  mark_edges ();

  calc_vertical_order (graph->nodes[1]);

  for (i = 0; i < graph->node_num; i++)
    {
      node = graph->nodes[i];
      printf ("node: %d\n", i);
      printf ("vertical order: %d\n", node->vertical_order);
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

void
fine_tune_graph (void)
{
  struct gdl_graph *fun_graph, *bb_graph;

  set_vertical_order ();

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
}
