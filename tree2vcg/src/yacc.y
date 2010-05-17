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

  #include "gdl.h"
  #include "cfg.h"
  #include "tree2vcg.h"

  static char *insns;
  static int len;
  static int seen_bb = 0;

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

%type <val> FN BB PRED SUCC
%type <str> FN_NAME STMT BB_NUM PRED_NUM SUCC_NUM

%debug 
%verbose

%%

input:	/* empty */
	| input line
;

line: FN FN_NAME {
    finish_previous_bb ();

    current_function = new_function ($<str>2); /* FN_NAME */
    if (first_function == NULL)
      {
        first_function = current_function;
        last_function = current_function;
      }
    else
      {
        assert (last_function != NULL);

        last_function->next = current_function;
        last_function = current_function;
      }
  }
	| BB BB_NUM {
    finish_previous_bb ();

    seen_bb = 1;
    current_bb = lookup_and_add_bb (current_function, $<str>2);
  }
        | PRED pred_nums 
        | SUCC succ_nums {
  }
	| STMT {
    obstack_grow (&insn_obstack, $<str>1, strlen ($<str>1));
    obstack_grow (&insn_obstack, "  \n", 3);
    free ($<str>1);
  }

pred_nums:	/* empty */
	| pred_nums PRED_NUM {
    lookup_and_add_edge (current_function, $<str>2, current_bb->name);
  }

succ_nums:	/* empty */
	| succ_nums SUCC_NUM {
    lookup_and_add_edge (current_function, current_bb->name, $<str>2);
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

void
finish_previous_bb (void)
{
  if (seen_bb && current_bb != NULL)
    {
      len = obstack_object_size (&insn_obstack);
      if (len > 0)
        {
          insns = (char *)obstack_finish (&insn_obstack);
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

