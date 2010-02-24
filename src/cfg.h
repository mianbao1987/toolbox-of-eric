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

enum vvp_edge_type
{
  VVP_UNKNOWN_EDGE,
  VVP_DFST_EDGE,
  VVP_ADVANCING_EDGE,
  VVP_RETREATING_EDGE,
  VVP_CROSS_EDGE
};

struct vvp_edge
{
  enum vvp_edge_type type;

  struct vvp_basic_block *source;
  struct vvp_basic_block *target;

  struct vvp_edge *next;
};

struct vvp_vec_edge
{
  struct vvp_edge *edge;
  struct vvp_vec_edge *next;
};

struct vvp_basic_block
{
  char *name;
  char *text;

  int pred_num;
  int succ_num;
  int visited;
  int dfs_order;
  int max_distance;

  struct vvp_vec_edge *pred;
  struct vvp_vec_edge *last_pred;
  struct vvp_vec_edge *succ;
  struct vvp_vec_edge *last_succ;

  struct vvp_basic_block *next;
};

struct vvp_control_flow_graph
{
  int bb_num;
  int edge_num;
  struct vvp_basic_block *entry; /* also the first bb */
  struct vvp_basic_block *exit; /* also  the last bb */
  struct vvp_basic_block *bb;
  struct vvp_basic_block *last_bb;
  struct vvp_edge *edge;
  struct vvp_edge *last_edge;
};

struct vvp_function
{
  char *name;
  struct vvp_control_flow_graph *cfg;
  struct vvp_function *next;
};

extern struct vvp_function *vvp_new_function (char *name);
extern struct vvp_basic_block *vvp_lookup_and_add_bb (struct vvp_function *func,
                                                      char *name);
extern struct vvp_edge *vvp_lookup_and_add_edge (struct vvp_function *func,
                                                 char *source_name,
                                                 char *target_name);

#endif
