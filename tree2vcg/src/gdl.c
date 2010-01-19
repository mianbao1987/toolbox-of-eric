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

char *shape_s[SHAPE_DEFAULT + 1] =
{
  "box",
  "rhomb",
  "ellipse",
  "triangle",
  NULL
};

char *color_s[COLOR_DEFAULT + 1] =
{
  "black",
  "blue",
  "lightblue",
  "red",
  "green",
  "yellow",
  "white",
  "lightgrey",
  NULL
};

char *linestyle_s[LINESTYLE_DEFAULT + 1] =
{
  "continuous",
  "dashed",
  "dotted",
  "invisible",
  NULL
};

char *layoutalgorithm_s[LAYOUTALGORITHM_DEFAULT + 1] =
{
  "max_depth",
  "tree",
  NULL
};

struct gdl_graph *
new_graph (char *title)
{
  struct gdl_graph *graph;

  graph = (struct gdl_graph *) xmalloc (sizeof (struct gdl_graph));
  set_graph_title (graph, title);
  set_graph_label (graph, NULL);
  set_graph_color (graph, COLOR_DEFAULT);
  set_graph_node_color (graph, COLOR_DEFAULT);
  /*graph->folding = -1;
  graph->shape = SHAPE_DEFAULT;
  graph->layoutalgorithm = LAYOUTALGORITHM_DEFAULT;
  graph->near_edges = -1;
  graph->port_sharing = -1;*/

  graph->nodes = NULL;
  graph->subgraphs = NULL;
  graph->edges = NULL;
  graph->next = NULL;

  return graph;
}

struct gdl_node *
new_node (char *title)
{
  struct gdl_node *node;

  node = (struct gdl_node *) xmalloc (sizeof (struct gdl_node));
  set_node_title (node, title);
  set_node_label (node, NULL);
  /* node->vertical_order = -1;
  node->color = COLOR_DEFAULT;
  node->shape = SHAPE_DEFAULT; */

  node->next = NULL;
  
  return node;
}

struct gdl_edge *
new_edge (char *sourcename, char *targetname)
{
  struct gdl_edge *edge;

  edge = (struct gdl_edge *) xmalloc (sizeof (struct gdl_edge));
 /*  edge->sourcename = sourcename;
  edge->targetname = targetname;
  edge->label = NULL;
  edge->linestyle = LINESTYLE_DEFAULT; */

  edge->next = NULL;
  
  return edge;
}

void 
add_subgraph (struct gdl_graph *graph, struct gdl_graph *subgraph)
{
  if (graph->subgraphs == NULL)
    graph->subgraphs = subgraph;
  else
    {
      subgraph->next = graph->subgraphs;
      graph->subgraphs = subgraph;
    }
}

void 
add_node (struct gdl_graph *graph, struct gdl_node *node)
{
  if (graph->nodes == NULL)
    graph->nodes = node;
  else
    {
      node->next = graph->nodes;
      graph->nodes = node;
    }
}

void 
add_edge (struct gdl_graph *graph, struct gdl_edge *edge)
{
  if (graph->edges == NULL)
    graph->edges = edge;
  else
    {
      edge->next = graph->edges;
      graph->edges = edge;
    }
}


