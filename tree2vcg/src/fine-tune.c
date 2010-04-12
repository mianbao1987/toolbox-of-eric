/* Fine tune cfg.

   Copyright (C) 2009, 2010 Eric Fisher, joefoxreal@gmail.com. 

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
static struct control_flow_graph *cfg;

void
search (struct basic_block *bb)
{
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
calc_max_distance_recursive (struct basic_block *bb)
{
  int val, max = 0;
  struct vec_edge *ve;
  struct edge *e;

  if (bb->max_distance == 0)
    {
      for (ve = bb->pred; ve != NULL; ve = ve->next)
        {
          e = ve->edge;
          if (e->type == RETREATING_EDGE)
            continue;
          val = calc_max_distance_recursive (e->source);
          max = max > val ? max : val;
        }
      bb->max_distance = max + 1;
    }
  return bb->max_distance;
}

void
calc_max_distance (void)
{
  int val, max = 0;
  struct basic_block *bb;

  depth_first_search ();

  mark_edges ();

  max = calc_max_distance_recursive (cfg->exit);
  for (bb = cfg->bb; bb != NULL; bb = bb->next)
    {
      if (bb->max_distance == 0)
        {
          val = calc_max_distance_recursive (bb);
          max = max > val ? max : val + 1;
        }
    }
  cfg->exit->max_distance = max;
}

void
fine_tune_cfg (void)
{
  for (current_function = first_function; current_function != NULL;
       current_function = current_function->next)
    {
      cfg = current_function->cfg;
      calc_max_distance ();
    }
}
