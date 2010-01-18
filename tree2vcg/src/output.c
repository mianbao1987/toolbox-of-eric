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

#include "gdl.h"
#include "tree2vcg.h"

static void
output_node (struct gdl_node *node)
{
  char *str;
  int val;

  fputs ("node: {\n", fout);

  /* title */
  str = get_node_title (node);
  if (str != NULL)
    fprintf (fout, "title: \"%s\"\n", str);
  
  /* label */
  str = get_node_label (node);
  if (str != NULL)
    fprintf (fout, "label: \"%s\"\n", str);
  
  /* vertical_order */
  val = get_node_vertical_order (node);
  if (val != -1)
    fprintf (fout, "vertical_order: %d\n", val);

  /* shape */
  str = get_node_shape_s (node);
  if (str != NULL)
    fprintf (fout, "shape: %s\n", str); 

  /* color */
  str = get_node_color_s (node);
  if (str != NULL)
    fprintf (fout, "color: %s\n", str); 

  fputs ("}\n", fout);
}

static void
output_edge (struct gdl_edge *edge)
{
  char *str;
  int *val;

  fputs ("edge: {\n", fout);

  /* sourcename */
  str = get_edge_sourcename (edge);
  if (str != NULL)
    fprintf (fout, "sourcename: \"%s\"\n", str);
  
  /* targetname */
  str = get_edge_targetname (edge);
  if (str != NULL)
    fprintf (fout, "targetname: \"%s\"\n", str);
  
  /* label */
  str = get_edge_label (edge);
  if (str != NULL)
    fprintf (fout, "label: \"%s\"\n", str);
  
  /* linestyle */
  str = get_edge_linestyle_s (edge);
  if (str != NULL)
    fprintf (fout, "linestyle: %s\n", str);

  fputs ("}\n", fout);
}

static void
output_graph_attributes (struct gdl_graph *graph)
{
  char *str;
  int *val;

  /* title */
  str = get_graph_title (graph);
  if (str != NULL)
    fprintf (fout, "title: \"%s\"\n", str);

  /* label */
  str = get_graph_label (graph);
  if (str != NULL)
    fprintf (fout, "label: \"%s\"\n", str);

  /* color */
  str = get_graph_color_s (graph);
  if (str != NULL)
    fprintf (fout, "color: %s\n", str);

  /* node.color */
  str = get_graph_node_color_s (graph);
  if (str != NULL)
    fprintf (fout, "node.color: %s\n", str);

  /* folding */
  val = get_graph_folding (graph);
  if (val != -1)
    fprintf (fout, "folding: %d\n", val);

  /* shape */
  str = get_graph_shape_s (graph);
  if (str != NULL)
    fprintf (fout, "shape: %s\n", str);

  /* layoutalgorithm */
  str = get_graph_layoutalgorithm_s (graph);
  if (str != NULL)
    fprintf (fout, "layoutalgorithm: %s\n", str);

  /* near_edges */
  val = get_graph_near_edges (graph);
  if (val != -1)
    fprintf (fout, "near_edges: %s\n", val ? "yes" : "no");

  /* port_sharing */
  val = get_graph_port_sharing (graph);
  if (val != -1)
    fprintf (fout, "port_sharing: %s\n", val ? "yes" : "no");
}

void
output_graph (struct gdl_graph *graph)
{
  struct gdl_node *nodes, *node;
  struct gdl_edge *edges, *edge;
  struct gdl_graph *subgraphs, *subgraph;

  fputs ("graph: {\n", fout);

  /* general graph attributes */
  output_graph_attributes (graph);

  /* list of nodes or subgraphs */
  nodes = get_graph_nodes (graph);
  for (node = nodes; node != NULL; node = node->next)
    output_node (node);

  subgraphs = get_graph_subgraphs (graph);
  for (subgraph = subgraphs; subgraph != NULL; subgraph = subgraph->next)
    output_graph (subgraph);

  /* list of edges */
  edges = get_graph_edges (graph);
  for (edge = edges; edge != NULL; edge = edge->next)
    output_edge (edge);

  fputs ("}\n", fout);
}
