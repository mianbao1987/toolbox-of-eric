/* 

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

#include <error.h>
#include <libiberty.h>

#include "gdl.h"
#include "cfg.h"
#include "tree2vcg.h"

struct basic_block *
new_bb (char *name)
{
  struct basic_block *bb;

  bb = (struct basic_block *) xmalloc (sizeof (struct basic_block));
  bb->name = name;

  bb->text = NULL;

  bb->pred_num = 0;
  bb->succ_num = 0;
  bb->pred = NULL;
  bb->last_pred = NULL;
  bb->succ = NULL;
  bb->last_succ = NULL; 

  bb->visited = 0;
  bb->dfs_order = 0;
  bb->max_distance = 0;

  bb->next = NULL;

  return bb;
}

struct edge *
new_edge (struct basic_block *source, struct basic_block *target)
{
  struct edge *e;

  e = (struct edge *) xmalloc (sizeof (struct edge));
  e->source = source;
  e->target = target;

  e->type = UNKNOWN_EDGE;
  e->next = NULL;

  return e;
}

struct vec_edge *
new_vec_edge (struct edge *e)
{
  struct vec_edge *ve;

  ve = (struct vec_edge *) xmalloc (sizeof (struct vec_edge));
  ve->edge = e;
  ve->next = NULL;

  return ve;
}

struct control_flow_graph *
new_cfg (void)
{
  struct control_flow_graph *cfg;

  cfg = (struct control_flow_graph *)
        xmalloc (sizeof (struct control_flow_graph));
  cfg->bb_num = 2;
  cfg->edge_num = 0;

  cfg->entry = new_bb ("ENTRY");
  cfg->exit = new_bb ("EXIT");

  cfg->entry->next = cfg->exit;
  cfg->bb = cfg->entry;
  cfg->last_bb = cfg->exit;

  cfg->edge = NULL;
  cfg->last_edge = NULL;

  return cfg;  
}

struct function *
new_function (char *name)
{
  struct function *func;

  func = (struct function *) xmalloc (sizeof (struct function));
  func->name = name;
  func->next = NULL;

  func->cfg = new_cfg ();

  return func;
}

void
add_bb (struct function *func, struct basic_block *bb)
{
  struct control_flow_graph *cfg=func->cfg;

  assert (cfg->bb != NULL && cfg->last_bb != NULL);

  cfg->last_bb->next = bb;
  cfg->last_bb = bb;
  cfg->bb_num++;
}

void
add_edge (struct function *func, struct edge *e)
{
  struct control_flow_graph *cfg=func->cfg;

  if (cfg->edge == NULL)
    {
      cfg->edge = e;
      cfg->last_edge = e;
    }
  else
    {
      assert (cfg->last_edge != NULL);

      cfg->last_edge->next = e;
      cfg->last_edge = e;
    }
  cfg->edge_num++;
}

void
add_succ_vec_edge (struct basic_block *bb, struct vec_edge *ve)
{
  if (bb->succ == NULL)
    {
      bb->succ = ve;
      bb->last_succ = ve;
    }
  else
    {
      assert (bb->last_succ != NULL);

      bb->last_succ->next = ve;
      bb->last_succ = ve;
    }
}

void
add_pred_vec_edge (struct basic_block *bb, struct vec_edge *ve)
{
  if (bb->pred == NULL)
    {
      bb->pred = ve;
      bb->last_pred = ve;
    }
  else
    {
      assert (bb->last_pred != NULL);

      bb->last_pred->next = ve;
      bb->last_pred = ve;
    }
}

struct basic_block *
lookup_and_add_bb (struct function *func, char *name)
{
  struct control_flow_graph *cfg=func->cfg;
  struct basic_block *bb;

  for (bb = cfg->bb; bb != NULL; bb = bb->next)
    {
      if (strcmp (bb->name, name) == 0)
        return bb;
    }

  bb = new_bb (name);
  add_bb (func, bb);

  return bb;
}

struct edge *
lookup_and_add_edge (struct function *func, 
                     char *source_name, char *target_name)
{
  struct control_flow_graph *cfg=func->cfg;
  struct basic_block *source_bb, *target_bb;
  struct edge *e;
  struct vec_edge *ve;

  source_bb = lookup_and_add_bb (func, source_name);
  target_bb = lookup_and_add_bb (func, target_name);

  for (e = cfg->edge; e != NULL; e = e->next)
    {
      if (e->source == source_bb && e->target == target_bb)
        return e;
    }
  e = new_edge (source_bb, target_bb);
  add_edge (func, e);

  for (ve = source_bb->succ; ve != NULL; ve = ve->next)
    if (ve->edge == e)
      break;
   
  if (ve == NULL)
    {
      ve = new_vec_edge (e);
      add_succ_vec_edge (source_bb, ve);
    }

  for (ve = target_bb->pred; ve != NULL; ve = ve->next)
    if (ve->edge == e)
      break;
   
  if (ve == NULL)
    {
      ve = new_vec_edge (e);
      add_pred_vec_edge (target_bb, ve);
    }

  return e;
}
