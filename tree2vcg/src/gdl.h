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
  SHAPE_MAX
};

enum gdl_color
{
  BLACK,
  BLUE,
  RED,
  GREEN,
  YELLOW,
  COLOR_MAX
};

enum linestye
{
  CONTINUOUS,
  DASHED,
  DOTTED,
  INVISIBLE,
  LINESTYE_MAX
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
  enum gld_linestyle linestyle;
  struct gdl_edge *next;
};

struct gdl_graph
{
  char *title;
  char *label;
  enum gdl_color color;
  int folding;
  enum gdl_shape shape;
  enum gdl_layoutalgorithm layoutalgorithm;
  bool near_edges;
  bool port_sharing;
  /* nodes or subgraphs */
  struct gdl_node *nodes;
  struct gdl_graph *subgraphs;
  struct gdl_edge *edges;
  struct gdl_graph *next;
};

#endif
