/* Yacc file for asm2vcg.

   Copyright (C) 2009 Eric Fisher, joefoxreal@gmail.com. 

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
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
  #include "asm2vcg.h"

  int yylex (void);
  void yyerror (char const *);
%}

%union {
  int val;
  char *str;
}

%token PU BB PRED SUCC
%token PU_NAME
%token BB_NUM PRED_NUM SUCC_NUM
%token LABEL INSN
%token NL

%type <val> PU BB PRED SUCC BB_NUM PRED_NUM SUCC_NUM NL
%type <str> PU_NAME LABEL INSN

%debug 
%verbose

%%

input:	/* empty */
	| input line
;

line:	NL
	| statement NL
;

statement: PU PU_NAME {
    if (current_fun_name) 
      { 
        if (current_bb_num != -1)
          {
            output_graph_tailer_bb (current_fun_name, current_bb_num);
            current_bb_num = -1;
          }
        output_graph_tailer_fun (current_fun_name);
        free (current_fun_name);
      }
    current_fun_name = $<str>2; /* PU_NAME */
    output_graph_header_fun(current_fun_name);
  }
	| BB BB_NUM NL PRED pred_nums NL SUCC succ_nums {
    if (current_bb_num != -1)
      {
        output_graph_tailer_bb (current_fun_name, current_bb_num);
      }
    current_bb_num = $<val>2; /* BB_NUM */
    output_edges_bb (current_fun_name, current_bb_num, &pred_obstack, &succ_obstack);
    output_graph_header_bb (current_fun_name, current_bb_num);
  }
	| LABEL {
    seen_label = 1;
    if (current_label)
      free (current_label);
    current_label = xstrdup ($<str>1);
    free ($<str>1);
  }
	| INSN {
    if (seen_label)
      {
        seen_label = 0;
        obstack_grow (&insn_obstack, current_label, strlen (current_label));
        obstack_1grow (&insn_obstack, '\n');
      }
    obstack_grow (&insn_obstack, "  ", 2);
    obstack_grow (&insn_obstack, $<str>1, strlen ($<str>1));
    obstack_grow (&insn_obstack, "  \n", 3);
    free ($<str>1);
  }

pred_nums:	/* empty */
	| pred_nums PRED_NUM {
    obstack_int_grow (&pred_obstack, $<val>2);
  }

succ_nums:	/* empty */
	| succ_nums SUCC_NUM {
    obstack_int_grow (&succ_obstack, $<val>2);
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
