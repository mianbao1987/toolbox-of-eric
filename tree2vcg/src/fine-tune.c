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

static int count;

void
search (struct basic_block *bb)
{
  struct control_flow_graph *cfg = current_function->cfg;
  struct basic_block *succ_bb;
  struct vec_edge *ve;
  struct edge *e;

  bb->visited = 1;

  for (ve = bb->succ; ve != NULL; ve = ve->next)
    {
      e = ve->edge;
      succ_bb = e->target;
      if (succ_bb->visited == 0)
        {
          e->type = DFST_EDGE;
          search (succ_bb);
        }
    }
  bb->dfs_order = count;
  count--;
}

void
depth_first_search (void)
{
  struct control_flow_graph *cfg = current_function->cfg;
  struct basic_block *bb;
 
  for (bb = cfg->bb; bb != NULL; bb = bb->next)
    {
      bb->visited = 0;
    }

  count = cfg->bb_num;
  search (cfg->entry);
}

int
is_ancestor (struct basic_block *source, struct basic_block *target)
{
  struct control_flow_graph *cfg = current_function->cfg;
  struct basic_block *bb;
  struct vec_edge *ve;
  struct edge *e;

  bb = target;
  do
    {
      if (bb == source)
        return 1;
      
      for (ve = bb->pred;  ve != NULL; ve = ve->next)
        {
          e = ve->edge;
          if (e->type == DFST_EDGE)
            {
              bb = e->source;
              break;
            }
        }
    } while (bb != cfg->entry);

  return 0;
}

void
mark_edge (struct edge *e)
{
  struct basic_block *source;
  struct basic_block *target;

  source = e->source;
  target = e->target;

  if (is_ancestor (target, source))
    e->type = RETREATING_EDGE;
  else if (is_ancestor (source, target))
    e->type = ADVANCING_EDGE;
  else
    e->type = CROSS_EDGE;
}

void
mark_edges (void)
{
  struct control_flow_graph *cfg = current_function->cfg;
  struct edge *e;

  for (e = cfg->edge; e != NULL; e = e->next)
    if (e->type == UNKNOWN_EDGE)
      mark_edge (e);
}

int
calc_max_distance (struct basic_block *bb)
{
  int val, max = 0;
  struct control_flow_graph *cfg = current_function->cfg;
  struct vec_edge *ve;
  struct edge *e;

  if (bb->max_distance == 0)
    {
      for (ve = bb->pred; ve != NULL; ve = ve->next)
        {
          e = ve->edge;
          if (e->type == RETREATING_EDGE)
            continue;
          val = calc_max_distance (e->source);
          max = max > val ? max : val;
        }
      bb->max_distance = max + 1;
    }
  return bb->max_distance;
}

void
set_vertical_order (void)
{
  struct control_flow_graph *cfg = current_function->cfg;
  struct basic_block *bb;
  struct vec_edge *ve;
  struct edge *e;

  depth_first_search ();

  mark_edges ();

  calc_max_distance (cfg->exit);

  for (bb = cfg->bb; bb != NULL; bb = bb->next)
    {
      gdl_set_graph_vertical_order (bb->x_graph, bb->max_distance);
/*
      printf ("node: %s\n", bb->name);
      printf ("vertical order: %d\n", bb->max_distance);
      printf ("dfs order: %d\n", bb->dfs_order);
      for (ve = bb->succ; ve != NULL; ve = ve->next)
        {
          e = ve->edge;
          if (e->type == DFST_EDGE)
            printf ("edge type: dfst\n");

          if (e->type == ADVANCING_EDGE)
            printf ("edge type: advancing\n");

          if (e->type == RETREATING_EDGE)
            printf ("edge type: retreating\n");

          if (e->type == CROSS_EDGE)
            printf ("edge type: cross\n");

          if (e->type == UNKNOWN_EDGE)
            printf ("edge type: unknown\n");

          printf ("edge: %s -> %s\n", e->source->name,
                  e->target->name);
        }
*/
    }  
}

void
fine_tune_graph (void)
{
  struct gdl_graph *fun_graph, *bb_graph;

  for (current_function = first_function; current_function != NULL;
       current_function = current_function->next)
    set_vertical_order ();

  /* common attributes */
  gdl_set_graph_node_color (top_graph, LIGHTGREY);
  gdl_set_graph_node_shape (top_graph, ELLIPSE);
  gdl_set_graph_layout_algorithm (top_graph, MAX_DEPTH);

  gdl_set_graph_folding (top_graph, 0);
  for (fun_graph = top_graph->subgraph; fun_graph; fun_graph = fun_graph->next)
    {
      for (bb_graph = fun_graph->subgraph; bb_graph; bb_graph = bb_graph->next)
        {
          gdl_set_graph_folding (bb_graph, 1);
        }
      gdl_set_graph_folding (fun_graph, 1);
    }
}
