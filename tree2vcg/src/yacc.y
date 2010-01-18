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
    if (seen_bb && bb_graph != NULL && bb_node != NULL)
      {
        len = obstack_object_size (&insn_obstack);
        if (len > 0)
          {
            insns = (char *)obstack_finish (&insn_obstack);
            assert (insns[len-1] == '\n');
            insns[len-1] = '\0';
            set_node_label (bb_node, insns);
          }
        else
          {
            set_node_label (bb_node, "   ");
          }
      }
    seen_bb = 0;

    fun_graph = new_graph ($<str>2); /* FN_NAME */
    add_subgraph (top_graph, fun_graph);

    bb_node = new_node ("ENTRY");
    add_node (fun_graph, bb_node);
    bb_node = new_node ("EXIT");
    add_node (fun_graph, bb_node);
  }
	| BB BB_NUM {
    if (seen_bb && bb_graph != NULL && bb_node != NULL)
      {
        len = obstack_object_size (&insn_obstack);
        if (len > 0)
          {
            insns = (char *)obstack_finish (&insn_obstack);
            assert (insns[len-1] == '\n');
            insns[len-1] = '\0';
            set_node_label (bb_node, insns);
          }
        else
          {
            set_node_label (bb_node, "   ");
          }
      }
    seen_bb = 1;

    fnname = get_graph_title (fun_graph);
    //bb_node = new_node (concat (fnname, "_bb", $<str>2, NULL)); /* BB_NUM */
    bb_node = new_node (NULL); /* BB_NUM */

    bb_graph = new_graph (concat (fnname, "_BB", $<str>2, NULL));
    set_graph_label (bb_graph, concat ("bb ", $<str>2, NULL));

    add_node (bb_graph, bb_node);
    add_subgraph (fun_graph, bb_graph);
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
        current_edge = new_edge ($<str>2, get_node_title (bb_graph));
        add_edge (fun_graph, current_edge);
      }
  }

succ_nums:	/* empty */
	| succ_nums SUCC_NUM {
    if (strcmp ($<str>2, "EXIT") == 0)
      current_edge = new_edge (get_node_title (bb_graph), $<str>2);
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
