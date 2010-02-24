/* Yacc file for tree2vcg.

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

%{
  #include <stdio.h>
  #include <string.h>
  #include <assert.h>

  #include <libiberty.h>
  #include <obstack.h>

  #include "tree2vcg.h"

/*
  Define global variables:
    <none>

  Use global variables:
    vvp_current_function
    vvp_first_function
    vvp_last_function
    vvp_insn_obstack

  Define extern functions:
    vvp_set_yy_debug
    vvp_finalize_last_bb

  Use extern functions:
    vvp_finalize_last_bb
    vvp_new_function
    vvp_lookup_and_add_bb
    vvp_lookup_and_add_edge
*/

  static char *insns;
  static int len;
  static int seen_bb = 0;

  static struct vvp_basic_block *current_bb;

  extern int yylex (void);
  extern void yyerror (char const *);
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
    vvp_finalize_last_bb ();

    vvp_current_function = vvp_new_function ($<str>2); /* FN_NAME */
    if (vvp_first_function == NULL)
      {
        vvp_first_function = vvp_current_function;
        vvp_last_function = vvp_current_function;
      }
    else
      {
        assert (vvp_last_function != NULL);

        vvp_last_function->next = vvp_current_function;
        vvp_last_function = vvp_current_function;
      }
  }
	| BB BB_NUM {
    vvp_finalize_last_bb ();

    seen_bb = 1;
    current_bb = vvp_lookup_and_add_bb (vvp_current_function, $<str>2);
  }
        | PRED pred_nums 
        | SUCC succ_nums {
  }
	| STMT {
    obstack_grow (&vvp_insn_obstack, $<str>1, strlen ($<str>1));
    obstack_grow (&vvp_insn_obstack, "  \n", 3);
    free ($<str>1);
  }

pred_nums:	/* empty */
	| pred_nums PRED_NUM {
    vvp_lookup_and_add_edge (vvp_current_function, $<str>2, current_bb->name);
  }

succ_nums:	/* empty */
	| succ_nums SUCC_NUM {
    vvp_lookup_and_add_edge (vvp_current_function, current_bb->name, $<str>2);
  }

%%

void
yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

void
vvp_set_yy_debug (void)
{
  yydebug = 1;
}

void
vvp_finalize_last_bb (void)
{
  if (seen_bb && current_bb != NULL)
    {
      len = obstack_object_size (&vvp_insn_obstack);
      if (len > 0)
        {
          insns = (char *)obstack_finish (&vvp_insn_obstack);
          assert (insns[len-1] == '\n');
          insns[len-1] = '\0';
          current_bb->text = insns;
        }
      else
        {
          current_bb->text = "   ";
        }
    }
  seen_bb = 0;
}

