/* Header file of tree2vcg.

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

#ifndef TREE2VCG_H
#define TREE2VCG_H

#include "gdl.h"

extern FILE *fin, *fout;

extern struct gdl_graph *top_graph;
extern struct gdl_graph *fun_graph;
extern struct gdl_graph *bb_graph;
extern struct gdl_node *bb_node;
extern struct gdl_edge *current_edge;

extern int seen_label;

extern struct obstack pred_obstack;
extern struct obstack succ_obstack;
extern struct obstack insn_obstack;

/* output.c */
extern void output_graph (struct gdl_graph *graph);

/* options.c */
extern void handle_options (int argc, char *argv[]);

/* fine_tune.c */
extern void fine_tune_graph (void);
#endif
