/* Yacc file for tree2vcg.

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

%{
  #include <stdio.h>
  #include <string.h>
  #include <assert.h>

  #include <libiberty.h>
  #include <obstack.h>

  #include "tree2vcg.h"

  int yylex (void);
  void yyerror (char const *);

  char *fnname;

  char *insns;
  int len;

  int seen_bb = 0;
%}

%union {
  int val;
  char *str;
}

%token FN BB PRED SUCC
%token FN_NAME
%token BB_NUM PRED_NUM SUCC_NUM
%token STMT
%token NL

%type <val> FN BB PRED SUCC
%type <str> FN_NAME STMT BB_NUM PRED_NUM SUCC_NUM

%debug 
%verbose

%%

input:	/* empty */
	| input line
;

line: FN FN_NAME {
    if (seen_bb && current_function != NULL)
      {
        node = current_function->x_graph->node;  

        len = obstack_object_size (&insn_obstack);
        if (len > 0)
          {
            insns = (char *)obstack_finish (&insn_obstack);
            assert (insns[len-1] == '\n');
            insns[len-1] = '\0';
            gdl_set_node_label (node, insns);
          }
        else
          {
            gdl_set_node_label (node, "   ");
          }
      }
    seen_bb = 0;

    struct function *func;

    func = new_function ($<str>2); /* FN_NAME */
  }
	| BB BB_NUM {
    if (seen_bb)
      {
        node = current_function->x_graph->node;  

        len = obstack_object_size (&insn_obstack);
        if (len > 0)
          {
            insns = (char *)obstack_finish (&insn_obstack);
            assert (insns[len-1] == '\n');
            insns[len-1] = '\0';
            gdl_set_node_label (node, insns);
          }
        else
          {
            gdl_set_node_label (node, "   ");
          }
      }
    seen_bb = 1;

    struct basic_block *bb;

    bb = new_bb ($<str>2);
  }
        | PRED pred_nums 
        | SUCC succ_nums {
  }
	| STMT {
    /* obstack_grow (&insn_obstack, "  ", 2); */
    obstack_grow (&insn_obstack, $<str>1, strlen ($<str>1));
    obstack_grow (&insn_obstack, "  \n", 3);
    free ($<str>1);
  }

pred_nums:	/* empty */
	| pred_nums PRED_NUM {
    if (strcmp ($<str>2, "ENTRY") == 0)
      {
        fnname = get_graph_title (fun_graph);
        current_edge = new_edge (concat (fnname, "_ENTRY", NULL), get_node_title (bb_graph));
        add_edge (fun_graph, current_edge);
      }
  }

succ_nums:	/* empty */
	| succ_nums SUCC_NUM {
    fnname = get_graph_title (fun_graph);
    if (strcmp ($<str>2, "EXIT") == 0)
      current_edge = new_edge (get_node_title (bb_graph), concat (fnname, "_EXIT", NULL));
    else
      current_edge = new_edge (get_node_title (bb_graph),
                               concat (fnname, "_BB", $<str>2, NULL));
    add_edge (fun_graph, current_edge);
  }

%%

void
yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

void
set_yy_debug (void)
{
  yydebug = 1;
}
