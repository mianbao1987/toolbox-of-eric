/* The structures according to graph description language (gdl).

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

#ifndef GDL_H
#define GDL_H

enum gdl_shape
{
  BOX,
  RHOMB,
  ELLIPSE,
  TRIANGLE,
  SHAPE_DEFAULT
};

enum gdl_color
{
  BLACK,
  BLUE,
  LIGHTBLUE,
  RED,
  GREEN,
  YELLOW,
  WHITE,
  LIGHTGREY,
  COLOR_DEFAULT
};

enum gdl_linestyle
{
  CONTINUOUS,
  DASHED,
  DOTTED,
  INVISIBLE,
  LINESTYLE_DEFAULT
};

enum gdl_layoutalgorithm
{
  MAX_DEPTH,
  TREE,
  LAYOUTALGORITHM_DEFAULT
};

#define DEF_ATTR(obj, name, type) type name;
struct gdl_node_attr
{
  #include "node-attr.c"
};

struct gdl_edge_attr
{
  #include "edge-attr.c"
};

struct gdl_graph_attr
{
  #include "graph-attr.c"
};
#undef DEF_ATTR

struct gdl_node
{
  struct gdl_node_attr attr;
  struct gdl_node *next;
};

struct gdl_edge
{
  struct gdl_edge_attr attr;
  struct gdl_edge *next;
};

struct gdl_graph
{
  struct gdl_graph_attr attr;
  /* nodes or subgraphs */
  struct gdl_node *nodes;
  struct gdl_graph *subgraphs;
  struct gdl_edge *edges;
  struct gdl_graph *next;
};

extern char *shape_s[SHAPE_DEFAULT + 1];
extern char *color_s[COLOR_DEFAULT + 1];
extern char *linestyle_s[LINESTYLE_DEFAULT + 1];
extern char *layoutalgorithm_s[LAYOUTALGORITHM_DEFAULT + 1];

extern struct gdl_edge *gdl_new_edge (char *sourcename, char *targetname);
extern struct gdl_graph *gdl_new_graph (char *title);
extern struct gdl_graph *gdl_new_bb_graph (char *name);
extern struct gdl_graph *gdl_new_func_graph (char *name);

#define DEF_ATTR(obj, name, type) \
static inline type \
gdl_get_##obj##_##name (struct gdl_##obj *obj) \
{ \
  return obj->attr.name; \
}

#include "node-attr.c"
#include "edge-attr.c"
#include "graph-attr.c"

#undef DEF_ATTR

#define DEF_ATTR(obj, name, type) \
static inline void \
gdl_set_##obj##_##name (struct gdl_##obj *obj, type value) \
{ \
  obj->attr.name = value; \
}

#include "node-attr.c"
#include "edge-attr.c"
#include "graph-attr.c"

#undef DEF_ATTR

#if 0
static inline char *
get_node_shape_s (struct gdl_node *node)
{
  assert (node->shape >= 0 && node->shape <= SHAPE_DEFAULT);
  return shape_s[node->shape];
}

static inline char *
get_node_color_s (struct gdl_node *node)
{
  assert (node->color >= 0 && node->color <= COLOR_DEFAULT);
  return color_s[node->color];
}

static inline void
set_graph_node_color (struct gdl_graph *graph, enum gdl_color color)
{
  assert (color >= 0 && color <= COLOR_DEFAULT);
  graph->color = color;
}

static inline char *
get_graph_shape_s (struct gdl_graph *graph)
{
  assert (graph->shape >= 0 && graph->shape <= SHAPE_DEFAULT);
  return shape_s[graph->shape];
}

static inline char *
get_graph_layoutalgorithm_s (struct gdl_graph *graph)
{
  assert (graph->layoutalgorithm >= 0 
          && graph->layoutalgorithm <= LAYOUTALGORITHM_DEFAULT);
  return layoutalgorithm_s[graph->layoutalgorithm];
}

static inline void
set_graph_layoutalgorithm (struct gdl_graph *graph,
                           enum gdl_layoutalgorithm alg)
{
  assert (alg >= 0 && alg <= LAYOUTALGORITHM_DEFAULT);
  graph->layoutalgorithm = alg;
}

#endif

#endif
