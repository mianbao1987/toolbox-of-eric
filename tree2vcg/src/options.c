/* Handle command line options.

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

#include <error.h>

#include <argp.h>
/*
#include "gdl.h"
#include "tree2vcg.h"
*/

char *fin_name, *fout_name;
FILE *fin, *fout;

const char *argp_program_version = "tree2vcg 0.3";
const char *argp_program_bug_address = "joefoxreal@gmail.com";

static struct argp_option options[] = {
  {"output", 'o', "FILE", 0, "Output to FILE instead of standard output"},
  {NULL}
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  switch (key)
    {
    case 'o':
      fout_name = arg;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp argp = {options, parse_opt, NULL, NULL};

void
handle_options (int argc, char *argv[])
{
  int arg_index;
  
  argp_parse (&argp, argc, argv, 0, &arg_index, 0);

  fout = stdout;
  fin = stdin;
  /* Set fout. */
  if (fout_name)
    {
      fout = fopen (fout_name, "w");
      if (fout == 0)
        error (-1, 0, "Failed to open file '%s'", fout_name);
    }
  /* Pick the first input file only. */
  if (arg_index < argc)
    {
      fin_name = argv[arg_index];
    }
  /* Set fin. */
  if (fin_name)
    {
      fin = fopen (fin_name, "r");
      if (fin == 0)
        error (-1, 0, "Failed to open file '%s'", fin_name);
    }
}

