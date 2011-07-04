/* Transform cfg to vcg.

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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <unistd.h>
#include <error.h>
#include <libiberty.h>
#include <obstack.h>

#include <argp.h>

#include "gdl.h"
#include "asm2vcg.h"

struct gdl_graph *top_graph;

void
cfg_to_vcg (void)
{
  struct gdl_graph *fun_graph;
  struct gdl_graph *bb_graph;
  struct gdl_node *node;
  struct gdl_edge *edge;

  struct control_flow_graph *cfg;
  struct basic_block *bb;
  struct edge *e;

  char *str_a, *str_b;

  /* top graph */
  top_graph = gdl_new_graph (NULL);
  gdl_set_graph_node_shape (top_graph, BOX);
  gdl_set_graph_node_borderwidth (top_graph, 1);
  gdl_set_graph_node_margin (top_graph, 1);
  gdl_set_graph_edge_thickness (top_graph, 1);
  gdl_set_graph_layout_algorithm (top_graph, MAX_DEPTH);
  gdl_set_graph_folding (top_graph, -1);
  gdl_set_graph_splines (top_graph, "yes");

  for (current_function = first_function; current_function != NULL;
       current_function = current_function->next)
    {
      cfg = current_function->cfg;

      /* function graph */
      fun_graph = gdl_new_graph (current_function->name);
      gdl_set_graph_node_color (fun_graph, WHITE);
      gdl_set_graph_folding (fun_graph, 1);
      gdl_add_subgraph (top_graph, fun_graph);

      for (bb = cfg->bb; bb != NULL; bb = bb->next)
        {
          /* bb graph */
          str_a = concat (current_function->name, ".", bb->name, NULL);
          if (strcmp (bb->name, "ENTRY") == 0
              || strcmp (bb->name, "EXIT") == 0)
            str_b = bb->name;
          else
            str_b = concat ("bb ", bb->name, NULL);

          bb_graph = gdl_new_graph (str_a);
          gdl_set_graph_label (bb_graph, str_b);
          gdl_set_graph_vertical_order (bb_graph, bb->max_distance);
          gdl_set_graph_folding (bb_graph, 1);
          gdl_set_graph_shape (bb_graph, ELLIPSE);
          gdl_add_subgraph (fun_graph, bb_graph);

          /* bb node */
          str_a = concat (current_function->name, "_", bb->name, NULL);

          node = gdl_new_node (str_a);
          if (bb->text == NULL)
            gdl_set_node_label (node, bb->name);
          else
            gdl_set_node_label (node, bb->text);

          gdl_set_node_vertical_order (node, bb->max_distance);
          gdl_add_node (bb_graph, node);
        }

      for (e = cfg->edge; e != NULL; e = e->next)
        {
          /* edge */
          str_a = concat (current_function->name, ".", e->source->name, NULL);
          str_b = concat (current_function->name, ".", e->target->name, NULL);
          edge = gdl_new_edge (str_a, str_b);
          if (e->type == RETREATING_EDGE)
            gdl_set_edge_linestyle (edge, DASHED);

          gdl_add_edge (fun_graph, edge);
        }
    }
}
