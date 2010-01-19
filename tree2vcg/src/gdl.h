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

struct gdl_node_attr
{
  /* bordercolor: Color Entry,
     default is the value of the textcolor attribute for nodes
     Specifies the color for node borders. For the available Color Entries,  
     see section Colors. See also node attributes color and textcolor. */  
  enum gdl_color bordercolor;

  /* borderstyle: Style, default is solid
     Specifies the line style used for drawing the borders of a node. 
     The following Styles are available:

     * solid
     * continuous
     * dashed
     * dotted
     * double
     * triple */
  enum gdl_style style;

  /* borderwidth: Int, default is 2
     Specifies the width of the border of a node in pixels. */
  int borderwidth;

  /* color: Color Entry,
     default is white Specifies the background color of a node. For the
     available Color Entries, see section Colors. See also node attributes 
     textcolor and bordercolor. */
  enum gdl_color color;

  /* focus, no value, no default value
     Sets the focus for the node for which it is specified. After startup this
     node is centered in the graph window. The focus can also be specified for
     summary nodes. It goes without saying that the focus attribute should
     appear only once in a graph specification. */

  /* fontname: "Font File", default is the default vector font drawn by turtle
     graphics routines Specifies a pixel font different from the default vector
     font and used for drawing the node labels.

     This font is given by the name of the aiSee Font File containing the font
     description, e.g. a 12-point Helvetica Bold font can be specified via 
     fontname: "helvB12". 

     Note: If the font file is not in the current directory the environment 
     variable AISEEFONTS has to be set to the directory containing the font 
     description files. For the available Font Files, see additional fonts. */

  /* height: Int
     default is (node label height) pixels
     specifies the height of a node including the border. See also width. */

  /* horizontal_order: Int, default is -1 (i.e. no default)
     In a hierarchical layout, this attribute specifies the horizontal position
     of a node within a level (see vertical_order). Nodes specified by 
     horizontal positions are ordered according to these positions within 
     levels. Nodes without this attribute are inserted into this ordering by 
     the crossing reduction mechanism (see crossing reduction).

     Note: Connected components are handled separately during crossing 
     reduction, thus it is not possible to intermix nodes of different 
     connected components in one ordering sequence. For example, one connected 
     component consists of nodes A, B, C and another of nodes D, E, all nodes 
     being positioned at the same level. Then, for instance, it is not possible
     to specify the following horizontal order at level 0: A, D, C, E.

     Note further: If the algorithm for downward laid-out trees is used the 
     specified horizontal order is retained only within nodes that are children
     of the same node, i.e. in case of downward laid-out trees it is not 
     possible to specify a horizontal order for the entire level. */

  /* iconfile: "File",
     no default value
     Specifies the bitmap file (in PNG, PBM, PPM, or raw PPM format) to be 
     displayed in the node. If the bitmap file to be displayed is not in the 
     current directory the environment variable AISEEICONS can be set to the 
     directory containing the bitmap file. For details, see icons. */

  /* importance: Int, default is 0 (which actually means infinity)
     This is the central attribute when it comes to filtering in fish-eye views
     as it enables the importance of a node to be specified via an integer. Low
     integers signify less important nodes which are filtered out first by a 
     filtering fish-eye view. High integer numbers signify nodes that are 
     important, their being rarely filtered out. A value of 0 represents an 
     infinite importance, the result being that these nodes are never filtered 
     out. This attribute also exists for summary nodes of folded subgraphs, 
     see importance. */

  /* invisible: yes or no, as of aiSee 2.1.94,
     default is no
     yes forces a node to be hidden after the layout calculation. This
     attribute becomes useful when specifying dummy nodes. */
     
  /* label: "String", default is "" (empty string)
     Specifies the text to be displayed inside the node. This text may contain
     control characters, e.g. \n (newline character), that influence the size
     of the node. See character set for more details. If no label is specified,
     the value of the node attribute title is used. */
  char *label;
     
  /* level: Int, default is -1 (i.e. no default)
     This is a synonym for vertical_order. */
     
  /* loc: { x: Int y: Int }, no default value
     Specifies the location of a node, i.e. the x and y coordinates in relation
     to the coordinate system of the graph. The origin is in the upper left
     corner. For example, the specification loc:{x:100 y:200} places a node at
     location (100, 200) in the coordinate system. 
     
     The location specification is not valid unless locations are specified for
     all nodes, otherwise aiSee calculates appropriate x and y coordinates
     according to the layout algorithm chosen. */
     
  /* margin: Int, as of aiSee 2.1.89,
     default is 3 if the value of borderwidth is > 0,
     0 if the value of borderwidth is 0
     Specifies the horizontal and vertical offset between the border of a node
     and its label in pixels. Useful for rectangular nodes only. */
     
  /* scaling: Float, default is 1.0
     Specifies the scaling factor of a node. This attribute is normally used to
     change the node text size. See also shrink / stretch. */
     
  /* shape: Shape, default is box
     Specifies the Shape of a node. The following Shapes are available:
     
         * box
         * triangle
         * circle
         * ellipse
         * rhomb
         * hexagon
         * trapeze
         * uptrapeze
         * lparallelogram
         * rparallelogram
     
     Please note that drawing ellipses is slower than drawing other shapes. */
  enum gdl_shape shape;
     
  /* shrink: Int, default is 1
     stretch: Int, default is 1
     Specify the shrinking and stretching factor of a node. The values of the
     node attributes width, height, borderwidth and the size of the label is
     scaled by ((stretch / shrink) * 100) percent. The scale value can also be
     specified by the node attribute scaling.
     
     The actual scaling factor of a node is determined by the scale factor of a
     node in relation to the scale factor of the graph, i.e. if the scaling
     factors are 2.0 for the graph and 1.5 for the node, the node is scaled by
     a factor of 3.0 as compared to normal size. */
     
  /* textcolor: Color Entry, default is black
     Specifies the color for text labels of nodes. If no bordercolor is
     specified, then this attribute also specifies the color for node border.
     For the available Color Entries, see section Colors. See also node
     attribute color. */
     
  /* textmode: center, or left_justify, or right_justify, default is center
     Specifies the alignment of text within a node. */
     	
     
  /* title: "String", no default value
     Specifies the unique string identifying the node. This attribute is
     mandatory for the node specification. */
  char *title;
     
  /* useractioncmd3: "String", default is "" (empty string)
     As of aiSee 3.beta, enables a command to be specified that can be executed
     by clicking on the node in the User Actions Mode. */
     
  /* vertical_order: maxlevel or Int, default is -1 (i.e. no default)
     In a hierarchical layout, this attribute specifies the vertical position
     of a node. maxlevel tries to position the node at the maximum calculated
     level. Generally speaking, the vertical position of a node is called level
     or rank (see rank assignment), with the node attribute level being a
     synonym for the attribute vertical_order.
     
     All nodes of level 0 form the uppermost layer (if the graph orientation is
     top_to_bottom). Nodes of level 1 form the second layer, etc. The level
     specification is not in effect unless automatic layout is being
     calculated. Layout is calculated automatically if there is at least one
     node without a specified location (see loc attribute for nodes and loc
     attribute for summary nodes).
     
     The level specification may conflict with a near edge specification,
     because the source and target node of a near edge have to have the same
     level. In this case, the level specification of the source or the target
     node of the near edge is ignored. */
  int vertical_order;
     
  /* width: Int
     default is (node label width) pixels
     specifies the width of a node including the border. See also height. */ 
  int width;
};

struct gdl_node
{
  struct gdl_node_attr attr;
  struct gdl_node *next;
};

struct gdl_edge_attr
{
  char *sourcename;
  char *targetname;
  char *label;
  enum gdl_linestyle linestyle;
  struct gdl_edge *next;
};

struct gdl_edge
{
  struct gdl_edge_attr attr;
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
  int node_borderwidth;
  int node_margin;
  int edge_thickness;
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
