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
  #include <libiberty.h>
  #include <obstack.h>
  #include "tree2vcg.h"

  int yylex (void);
  void yyerror (char const *);
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

%type <val> FN BB PRED SUCC BB_NUM PRED_NUM SUCC_NUM
%type <str> FN_NAME STMT

%debug 
%verbose

%%

input:	/* empty */
	| input line
;

line: FN FN_NAME {
    current_graph = new_graph ($<str>2); /* FN_NAME */
    add_graph (top_graph, current_graph);
  }
	| BB BB_NUM {
    current_node = new_node ($<val>2); /* BB_NUM */
    add_node (current_graph, current_node);
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
    current_edge = new_edge ($<str>2, get_node_title (current_node));
    add_edge (current_graph, current_edge);
  }

succ_nums:	/* empty */
	| succ_nums SUCC_NUM {
    current_edge = new_edge (get_node_title (current_node), $<str>2);
    add_edge (current_graph, current_edge);
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
