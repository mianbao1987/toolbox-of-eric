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
#include "cfg.h"

extern FILE *fin, *fout;

extern struct obstack insn_obstack;

extern struct function *first_function; 
extern struct function *last_function;
extern struct function *current_function;
extern struct basic_block *current_bb;

extern struct gdl_graph *top_graph;

/* yacc.y */
extern void finalize_last_bb (void);

/* output.c */
extern void output_vcg (void);

/* options.c */
extern void handle_options (int argc, char *argv[]);

/* fine_tune.c */
extern void fine_tune_vcg (void);
#endif
