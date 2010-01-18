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
  LAYOUTALGORITHM_DEFAULT
};

struct gdl_node
{
  char *title;
  char *label;
  int vertical_order;
  enum gdl_shape shape;
  enum gdl_color color;
  struct gdl_node *next;
};

struct gdl_edge
{
  char *sourcename;
  char *targetname;
  char *label;
  enum gdl_linestyle linestyle;
  struct gdl_edge *next;
};

struct gdl_graph
{
  char *title;
  char *label;
  enum gdl_color color;
  enum gdl_color node_color;
  int folding;
  enum gdl_shape shape;
  enum gdl_layoutalgorithm layoutalgorithm;
  int near_edges;
  int port_sharing;
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

extern struct gdl_graph *new_graph (char *title);
extern struct gdl_node *new_node (char *title);
extern struct gdl_edge *new_edge (char *sourcename, char *targetname);

extern void add_subgraph (struct gdl_graph *graph,  
                          struct gdl_graph *subgraph);
extern void add_node (struct gdl_graph *graph, struct gdl_node *node);
extern void add_edge (struct gdl_graph *graph, struct gdl_edge *edge);


static inline char *
get_node_title (struct gdl_node *node)
{
  return node->title;
}

static inline char *
get_node_label (struct gdl_node *node)
{
  return node->label;
}

static inline void
set_node_label (struct gdl_node *node, char *label)
{
  node->label = label;
}

static inline int
get_node_vertical_order (struct gdl_node *node)
{
  return node->vertical_order;
}

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

static inline char *
get_edge_sourcename (struct gdl_edge *edge)
{
  return edge->sourcename;
}

static inline char *
get_edge_targetname (struct gdl_edge *edge)
{
  return edge->targetname;
}

static inline char *
get_edge_label (struct gdl_edge *edge)
{
  return edge->label;
}

static inline char *
get_edge_linestyle_s (struct gdl_edge *edge)
{
  assert (edge->linestyle >= 0 && edge->linestyle <= LINESTYLE_DEFAULT);
  return linestyle_s[edge->linestyle];
}

static inline char *
get_graph_title (struct gdl_graph *graph)
{
  return graph->title;
}

static inline char *
get_graph_label (struct gdl_graph *graph)
{
  return graph->label;
}

static inline void
set_graph_label (struct gdl_graph *graph, char *label)
{
  graph->label = label;
}

static inline char *
get_graph_color_s (struct gdl_graph *graph)
{
  assert (graph->color >= 0 && graph->color <= COLOR_DEFAULT);
  return color_s[graph->color];
}

static inline char *
get_graph_node_color_s (struct gdl_graph *graph)
{
  assert (graph->node_color >= 0 && graph->node_color <= COLOR_DEFAULT);
  return color_s[graph->node_color];
}

static inline void
set_graph_node_color (struct gdl_graph *graph, enum gdl_color color)
{
  assert (color >= 0 && color <= COLOR_DEFAULT);
  graph->color = color;
}

static inline int
get_graph_folding (struct gdl_graph *graph)
{
  return graph->folding;
}

static inline void
set_graph_folding (struct gdl_graph *graph, int folding)
{
  graph->folding = folding;
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

static inline int
get_graph_near_edges (struct gdl_graph *graph)
{
  return graph->near_edges;
}

static inline int
get_graph_port_sharing (struct gdl_graph *graph)
{
  return graph->port_sharing;
}

static inline struct gdl_node *
get_graph_nodes (struct gdl_graph *graph)
{
  return graph->nodes;
}

static inline struct gdl_edge *
get_graph_edges (struct gdl_graph *graph)
{
  return graph->edges;
}

static inline struct gdl_graph *
get_graph_subgraphs (struct gdl_graph *graph)
{
  return graph->subgraphs;
}

#endif
