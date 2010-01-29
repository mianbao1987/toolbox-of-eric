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
#include "cfg.h"
#include "tree2vcg.h"

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

char *layout_algorithm_s[LAYOUT_ALGORITHM_DEFAULT + 1] =
{
  "max_depth",
  "tree",
  NULL
};

struct gdl_graph *
gdl_new_graph (char *title)
{
  struct gdl_graph *graph;

  graph = (struct gdl_graph *) xmalloc (sizeof (struct gdl_graph));
  gdl_set_graph_title (graph, title);
  gdl_set_graph_label (graph, NULL);
  gdl_set_graph_color (graph, COLOR_DEFAULT);
  gdl_set_graph_node_color (graph, COLOR_DEFAULT);
  gdl_set_graph_folding (graph, -1);
  gdl_set_graph_shape (graph, SHAPE_DEFAULT);
  gdl_set_graph_layout_algorithm (graph, LAYOUT_ALGORITHM_DEFAULT);
  gdl_set_graph_near_edges (graph, -1);
  gdl_set_graph_port_sharing (graph, -1);

  graph->node = NULL;
  graph->last_node = NULL;
  graph->subgraph = NULL;
  graph->last_subgraph = NULL;
  graph->edge = NULL;
  graph->last_edge = NULL;
  graph->next = NULL;

  return graph;
}

static struct gdl_node *
gdl_new_node (char *title)
{
  struct gdl_node *node;

  node = (struct gdl_node *) xmalloc (sizeof (struct gdl_node));
  gdl_set_node_title (node, title);
  gdl_set_node_label (node, NULL);
  gdl_set_node_vertical_order (node, -1);
  gdl_set_node_color (node, COLOR_DEFAULT);
  gdl_set_node_shape (node, SHAPE_DEFAULT);

  node->next = NULL;
  
  return node;
}

struct gdl_edge *
gdl_new_edge (char *sourcename, char *targetname)
{
  struct gdl_edge *edge;

  edge = (struct gdl_edge *) xmalloc (sizeof (struct gdl_edge));
  gdl_set_edge_source (edge, sourcename);
  gdl_set_edge_target (edge, targetname);
  gdl_set_edge_label (edge, NULL);
  gdl_set_edge_linestyle (edge, LINESTYLE_DEFAULT);

  edge->next = NULL;
  
  return edge;
}

static void 
gdl_add_subgraph (struct gdl_graph *graph, struct gdl_graph *subgraph)
{
  if (graph->subgraph == NULL)
    {
      graph->subgraph = subgraph;
      graph->last_subgraph = subgraph;
    }
  else
    {
      graph->last_subgraph->next = subgraph;
      graph->last_subgraph = subgraph;
    }
}

static void 
gdl_add_node (struct gdl_graph *graph, struct gdl_node *node)
{
  if (graph->node == NULL)
    {
      graph->node = node;
      graph->last_node = node;
    }
  else
    {
      graph->last_node->next = node;
      graph->last_node = node;
    }
}

static void 
gdl_add_edge (struct gdl_graph *graph, struct gdl_edge *edge)
{
  if (graph->edge == NULL)
    {
      graph->edge = edge;
      graph->last_edge = edge;
    }
  else
    {
      graph->last_edge->next = edge;
      graph->last_edge = edge;
    }
}

