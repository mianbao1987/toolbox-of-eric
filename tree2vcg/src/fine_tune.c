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

#include <argp.h>

#include "gdl.h"
#include "tree2vcg.h"

void
fine_tune_graph (void)
{
  struct gdl_graph *fun_graph, *bb_graph;

  /* common attributes */
  set_graph_node_color (top_graph, LIGHTGREY);
  set_graph_node_shape (top_graph, ELLIPSE);
  set_graph_layoutalgorithm (top_graph, MAX_DEPTH);

  set_graph_folding (top_graph, 0);
  for (fun_graph = top_graph->subgraphs; fun_graph; fun_graph = fun_graph->next)
    {
      for (bb_graph = fun_graph->subgraphs; bb_graph; bb_graph = bb_graph->next)
        {
          set_graph_folding (bb_graph, 1);
        }
      set_graph_folding (fun_graph, 1);
    }
}

