/* The structures according to graph description language (gdl).

   Copyright (C) 2009, 2010 Mingjie Xing, mingjie.xing@gmail.com. 

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

enum gdl_layout_algorithm
{
  MAX_DEPTH,
  TREE,
  LAYOUT_ALGORITHM_DEFAULT
};

#define DEF_ATTR(obj, name, type) type name;
struct gdl_node_attr
{
  #include "node-attr.def"
};

struct gdl_edge_attr
{
  #include "edge-attr.def"
};

struct gdl_graph_attr
{
  #include "graph-attr.def"
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
  struct gdl_node *node;
  struct gdl_node *last_node;
  struct gdl_graph *subgraph;
  struct gdl_graph *last_subgraph;
  struct gdl_edge *edge;
  struct gdl_edge *last_edge;
  struct gdl_graph *next;
};

extern char *shape_s[SHAPE_DEFAULT + 1];
extern char *color_s[COLOR_DEFAULT + 1];
extern char *linestyle_s[LINESTYLE_DEFAULT + 1];
extern char *layout_algorithm_s[LAYOUT_ALGORITHM_DEFAULT + 1];

extern struct gdl_graph *gdl_new_graph (char *title);
extern struct gdl_node *gdl_new_node (char *title);
extern struct gdl_edge *gdl_new_edge (char *source, char *target);
extern void gdl_add_subgraph (struct gdl_graph *graph,
                              struct gdl_graph *subgraph);
extern void gdl_add_node (struct gdl_graph *graph, struct gdl_node *node);
extern void gdl_add_edge (struct gdl_graph *graph, struct gdl_edge *edge);

#define DEF_ATTR(obj, name, type) \
static inline type \
gdl_get_##obj##_##name (struct gdl_##obj *obj) \
{ \
  return obj->attr.name; \
}

#include "node-attr.def"
#include "edge-attr.def"
#include "graph-attr.def"

#undef DEF_ATTR

#define DEF_ATTR(obj, name, type) \
static inline void \
gdl_set_##obj##_##name (struct gdl_##obj *obj, type value) \
{ \
  obj->attr.name = value; \
}

#include "node-attr.def"
#include "edge-attr.def"
#include "graph-attr.def"

#undef DEF_ATTR

static inline char *
gdl_get_node_shape_s (struct gdl_node *node)
{
  assert (node->attr.shape >= 0 && node->attr.shape <= SHAPE_DEFAULT);
  return shape_s[node->attr.shape];
}

static inline char *
gdl_get_node_color_s (struct gdl_node *node)
{
  assert (node->attr.color >= 0 && node->attr.color <= COLOR_DEFAULT);
  return color_s[node->attr.color];
}

static inline char *
gdl_get_edge_linestyle_s (struct gdl_edge *edge)
{
  return linestyle_s[edge->attr.linestyle];
}

static inline char *
gdl_get_graph_color_s (struct gdl_graph *graph)
{
  return color_s[graph->attr.color];
}

static inline char *
gdl_get_graph_node_color_s (struct gdl_graph *graph)
{
  return color_s[graph->attr.node_color];
}

static inline char *
gdl_get_graph_shape_s (struct gdl_graph *graph)
{
  assert (graph->attr.shape >= 0 && graph->attr.shape <= SHAPE_DEFAULT);
  return shape_s[graph->attr.shape];
}

static inline char *
gdl_get_graph_layout_algorithm_s (struct gdl_graph *graph)
{
  assert (graph->attr.layout_algorithm >= 0 
          && graph->attr.layout_algorithm <= LAYOUT_ALGORITHM_DEFAULT);
  return layout_algorithm_s[graph->attr.layout_algorithm];
}

static inline struct gdl_node *
gdl_get_graph_node (struct gdl_graph *graph)
{
  return graph->node;
}

static inline struct gdl_edge *
gdl_get_graph_edge (struct gdl_graph *graph)
{
  return graph->edge;
}

static inline struct gdl_graph *
gdl_get_graph_subgraph (struct gdl_graph *graph)
{
  return graph->subgraph;
}

#endif
