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
  struct edge *prev;

  struct gdl_edge *x_edge;
};

struct basic_block
{
  char *name;

  int pred_num;
  int succ_num;
  int visited;
  int dfs_order;
  int vertical_order;

  struct edge *pred;
  struct edge *succ;

  struct basic_block *next;
  struct basic_block *prev;

  struct gdl_graph *x_graph;
};

struct control_flow_graph
{
  int bb_num;
  int edge_num;
  struct basic_block *entry;
  struct basic_block *exit;
  struct basic_block *node;
  struct edge *edge;
};

struct function
{
  char *name;
  struct contral_flow_graph *cfg;
  struct function *next;
  struct function *prev;

  struct gdl_graph *x_graph;
};

