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

#include "cfg.h"
#include "tree2vcg.h"

/*
  Define global variables:
    <none>

  Use global variables:
    vvp_current_function
    vvp_first_function

  Define extern functions:
    vvp_fine_tune_cfg

  Use extern functions:
    <none>
*/

static int count;
static struct vvp_control_flow_graph *cfg;

static void
search (struct vvp_basic_block *bb)
{
  struct vvp_basic_block *succ_bb;
  struct vvp_vec_edge *ve;
  struct vvp_edge *e;

  bb->visited = 1;

  for (ve = bb->succ; ve != NULL; ve = ve->next)
    {
      e = ve->edge;
      succ_bb = e->target;
      if (succ_bb->visited == 0)
        {
          e->type = VVP_DFST_EDGE;
          search (succ_bb);
        }
    }
  bb->dfs_order = count;
  count--;
}

static void
depth_first_search (void)
{
  struct vvp_basic_block *bb;
 
  for (bb = cfg->bb; bb != NULL; bb = bb->next)
    {
      bb->visited = 0;
    }

  count = cfg->bb_num;
  search (cfg->entry);
}

static int
is_ancestor (struct vvp_basic_block *source, struct vvp_basic_block *target)
{
  struct vvp_basic_block *bb;
  struct vvp_vec_edge *ve;
  struct vvp_edge *e;

  bb = target;
  do
    {
      if (bb == source)
        return 1;
      
      for (ve = bb->pred;  ve != NULL; ve = ve->next)
        {
          e = ve->edge;
          if (e->type == VVP_DFST_EDGE)
            {
              bb = e->source;
              break;
            }
        }
    } while (bb != cfg->entry);

  return 0;
}

static void
mark_edge (struct vvp_edge *e)
{
  struct vvp_basic_block *source;
  struct vvp_basic_block *target;

  source = e->source;
  target = e->target;

  if (is_ancestor (target, source))
    e->type = VVP_RETREATING_EDGE;
  else if (is_ancestor (source, target))
    e->type = VVP_ADVANCING_EDGE;
  else
    e->type = VVP_CROSS_EDGE;
}

static void
mark_edges (void)
{
  struct vvp_edge *e;

  for (e = cfg->edge; e != NULL; e = e->next)
    if (e->type == VVP_UNKNOWN_EDGE)
      mark_edge (e);
}

static int
calc_max_distance_recursive (struct vvp_basic_block *bb)
{
  int val, max = 0;
  struct vvp_vec_edge *ve;
  struct vvp_edge *e;

  if (bb->max_distance == 0)
    {
      for (ve = bb->pred; ve != NULL; ve = ve->next)
        {
          e = ve->edge;
          if (e->type == VVP_RETREATING_EDGE)
            continue;
          val = calc_max_distance_recursive (e->source);
          max = max > val ? max : val;
        }
      bb->max_distance = max + 1;
    }
  return bb->max_distance;
}

static void
calc_max_distance (void)
{
  struct vvp_basic_block *bb;

  depth_first_search ();

  mark_edges ();

  calc_max_distance_recursive (cfg->exit);
  for (bb = cfg->bb; bb != NULL; bb = bb->next)
    {
      if (bb->max_distance == 0)
        calc_max_distance_recursive (bb);
    }
}

void
vvp_fine_tune_cfg (void)
{
  for (vvp_current_function = vvp_first_function;
       vvp_current_function != NULL;
       vvp_current_function = vvp_current_function->next)
    {
      cfg = vvp_current_function->cfg;
      calc_max_distance ();
    }
}
