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

extern char *current_fun_name;
extern int current_bb_num;
extern char *current_label;
extern char *current_insn;

extern int seen_label;

extern struct obstack pred_obstack;
extern struct obstack succ_obstack;
extern struct obstack insn_obstack;

extern void output_graph_header_fun (const char *fun_name);
extern void output_graph_tailer_fun (const char *fun_name);
extern void output_graph_header_bb (const char *fun_name, const int bb_num);
extern void output_graph_tailer_bb (const char *fun_name, const int bb_num);
extern void output_edges_bb (const char *fun_name, const int bb_num,
                             struct obstack *pred_obstack,
                             struct obstack *succ_obstack);
extern void output_node_insn (const char *fun_name, const char *insn);

#endif
