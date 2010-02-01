/* Control flow graph

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

#ifndef CFG_H
#define CFG_H

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

enum edge_type
{
  UNKNOWN_EDGE,
  DFST_EDGE,
  ADVANCING_EDGE,
  RETREATING_EDGE,
  CROSS_EDGE
};

struct edge
{
  enum edge_type type;

  struct basic_block *source;
  struct basic_block *target;

  struct edge *next;
};

struct vec_edge
{
  struct edge *edge;
  struct vec_edge *next;
};

struct basic_block
{
  char *name;
  char *text;

  int pred_num;
  int succ_num;
  int visited;
  int dfs_order;
  int max_distance;

  struct vec_edge *pred;
  struct vec_edge *last_pred;
  struct vec_edge *succ;
  struct vec_edge *last_succ;

  struct basic_block *next;
};

struct control_flow_graph
{
  int bb_num;
  int edge_num;
  struct basic_block *entry; /* also the first bb */
  struct basic_block *exit; /* also  the last bb */
  struct basic_block *bb;
  struct basic_block *last_bb;
  struct edge *edge;
  struct edge *last_edge;
};

struct function
{
  char *name;
  struct control_flow_graph *cfg;
  struct function *next;
};

extern struct function *new_function (char *name);

extern struct basic_block *lookup_and_add_bb (struct function *func,
                                              char *name);

extern struct edge *lookup_and_add_edge (struct function *func,
                                         char *source_name,
                                         char *target_name);

#endif
