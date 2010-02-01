/* Output vcg description file according to the tree dump file.

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

struct function *first_function; 
struct function *last_function; 
struct function *current_function; 
struct basic_block *current_bb;

void
general_init (void)
{
  obstack_init (&insn_obstack);

  first_function = NULL;
  last_function = NULL;
  current_function = NULL;
}

int
main (int argc, char *argv[])
{
  program_name = argv[0];
  handle_options (argc, argv);

  general_init ();

  yyin = fin;
  //set_yy_debug ();
  yyparse ();
  finalize_last_bb ();

  fine_tune_cfg ();

  cfg_to_vcg ();

  output_vcg ();

  return 0;
}
