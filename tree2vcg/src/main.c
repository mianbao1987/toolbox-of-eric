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

extern FILE *yyin;
extern int yyparse (void);
extern void set_yy_debug (void);

FILE *fin;
FILE *fout;

char *program_name;

#define obstack_chunk_alloc xmalloc
#define obstack_chunk_free free

struct obstack insn_obstack;

int func_num; 
struct function *func_list; 
struct function *current_function; 
struct basic_block *current_basic_block;

struct gdl_graph *top_graph;
struct gdl_graph *current_func_graph;
struct gdl_graph *current_bb_graph;
struct gdl_node *current_bb_node;

char *insns;
int len;
int seen_bb;

void
general_init (void)
{
  func_num = 0;
  func_list = NULL;
  current_function = NULL;

  top_graph = new_graph (NULL);

  seen_bb = 0;
}

void
finalize_node_label (void)
{
  if (seen_bb && current_bb_node != NULL)
    {
      len = obstack_object_size (&insn_obstack);
      if (len > 0)
        {
          insns = (char *)obstack_finish (&insn_obstack);
          assert (insns[len-1] == '\n');
          insns[len-1] = '\0';
          gdl_set_node_label (current_bb_node, insns);
        }
      else
        {
          gdl_set_node_label (current_bb_node, "   ");
        }
    }
  seen_bb = 0;
}

int
main (int argc, char *argv[])
{
  program_name = argv[0];
  handle_options (argc, argv);

  obstack_init (&pred_obstack);
  obstack_init (&succ_obstack);
  obstack_init (&insn_obstack);

  general_init ();

  yyin = fin;
  //set_yy_debug ();
  yyparse ();
  finalize_node_label ();

  fine_tune_graph ();

  output_graph (top_graph);
}
