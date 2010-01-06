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

#include "tree2vcg.h"

extern FILE *yyin;
extern int yyparse (void);
extern void set_yy_debug (void);

FILE *fin;
FILE *fout;

char *program_name;
char *program_version = "0.1";

char *current_fun_name;
int current_bb_num = -1;
char *current_label;
char *current_insn;

int seen_label = 0;

#define ENTRY_ID 0
#define EXIT_ID 1

#define obstack_chunk_alloc xmalloc
#define obstack_chunk_free free

struct obstack pred_obstack;
struct obstack succ_obstack;
struct obstack insn_obstack;

void
output_graph_header (void)
{
  fputs ("graph: {\n", fout);
  fputs ("port_sharing: no\n", fout);
}

void
output_graph_tailer (void)
{
  fputs ("}\n", fout);
}

void
output_graph_header_fun (const char *fun_name)
{
  fprintf (fout, "graph: { title: \"%s\"\n", fun_name);
  fprintf (fout, "folding: 1\n");
  fprintf (fout, "hidden: 2\n");
  fprintf (fout, "node: { title: \"%s.BB%d\" label: \"%s\" }\n",
           fun_name, ENTRY_ID, "ENTRY");
}

void
output_graph_tailer_fun (const char *fun_name)
{
  fprintf (fout, "node: { title: \"%s.BB%d\" label: \"%s\" }\n",
           fun_name, EXIT_ID, "EXIT");
  fprintf (fout, "}\n");
}

void
output_graph_header_bb (const char *fun_name, const int bb_num)
{
  fprintf (fout, "graph: {\n");
  fprintf (fout, "title: \"%s.BB%d\"\n", fun_name, bb_num);
  fprintf (fout, "folding: 1\n");
  fprintf (fout, "color: lightblue\n");
  fprintf (fout, "label: \"bb %d\"\n", bb_num);
  //fprintf (fout, "\n");
}

void
output_graph_tailer_bb (const char *fun_name, const int bb_num)
{
  char *insns;
  int len, i;
  
  len = obstack_object_size (&insn_obstack);
  if (len > 0)
    {
      insns = (char *)obstack_finish (&insn_obstack);
      assert (insns[len-1] == '\n');
      insns[len-1] = '\0';

      fprintf (fout, "node: {\n");
      fprintf (fout, "  title: \"%s.%d\"\n", fun_name, bb_num);
      fprintf (fout, "  color: green\n");
      /* fprintf (fout, "  label: \"<bb %d>\n%s\"",bb_num, insns); */
      fprintf (fout, "  label: \"<bb %d>\n",bb_num);
      for (i = 0; i < len - 1; i++)
        { 
          if (insns[i] == '"')
            fprintf (fout, "\\");
          fprintf (fout, "%c", insns[i]);
        }
      fprintf (fout, "\"");  
      fprintf (fout, "}\n");  
      obstack_free (&insn_obstack, insns);
    }
  fprintf (fout, "}\n");

}

void
output_edges_bb (const char *fun_name, const int bb_num,
                 struct obstack *pred_obstack,
                 struct obstack *succ_obstack)
{
  int i;
  int pred_nums, succ_nums;
  int *pred, *succ;

  pred_nums = obstack_object_size (pred_obstack) / sizeof (int);
  succ_nums = obstack_object_size (succ_obstack) / sizeof (int);

  pred = (int *)obstack_finish (pred_obstack);
  succ = (int *)obstack_finish (succ_obstack);

  for (i = 0; i < pred_nums; i++)
    if (pred[i] == 0)
      fprintf (fout,
               "edge: { sourcename: \"%s.BB%d\" targetname: \"%s.BB%d\" }\n",
               fun_name, pred[i], fun_name, bb_num);
    
  for (i = 0; i < succ_nums; i++)
    fprintf (fout,
             "edge: { sourcename: \"%s.BB%d\" targetname: \"%s.BB%d\" }\n",
             fun_name, bb_num, fun_name, succ[i]);

  /*if (succ_nums == 0)
    fprintf (fout,
             "edge: { sourcename: \"%s.BB%d\" targetname: \"%s.BB%d\" }\n",
             fun_name, bb_num, fun_name, MAX_ID);*/

  obstack_free (pred_obstack, pred);
  obstack_free (succ_obstack, succ);
}

void
usage (void)
{
  fprintf (stdout, "%s asm_file [-o out_file|-v|-h]\n", program_name);
}

void
version (void)
{
  fprintf (stdout, "version %s\n", program_version);
}

void
handle_option (int argc, char *argv[])
{
  int c;
  char *fin_name, *fout_name;

  fin_name = 0;
  fout_name = 0;
  while ((c = getopt (argc, argv, "ho:v")) != -1)
    {
      switch (c)
        {
        case 'h':
          usage ();
          exit (0);
        case 'o':
          fout_name = optarg;
          break;
        case 'v':
          version ();
          exit (0);
        default:
          usage ();
          exit (0);
        }
    }
  /* Pick the first input file only. */
  if (optind < argc)
    {
      fin_name = argv[optind];
    }
  /* Set fin. */
  if (fin_name)
    {
      fin = fopen (fin_name, "r");
      if (fin == 0)
        error (-1, 0, "Failed to open file '%s'", fin_name);
    }
  else
    {
      fin = stdin;
    }
  /* Set fout. */
  if (fout_name)
    {
      fout = fopen (fout_name, "w");
      if (fout == 0)
        error (-1, 0, "Failed to open file '%s'", fout_name);
    }
  else
    {
      fout = stdout;
    }
}

int
main (int argc, char *argv[])
{
  program_name = argv[0];
  handle_option (argc, argv);

  obstack_init (&pred_obstack);
  obstack_init (&succ_obstack);
  obstack_init (&insn_obstack);

  output_graph_header ();
  yyin = fin;
  //set_yy_debug ();
  yyparse ();

  if (current_bb_num != -1)
    {
      output_graph_tailer_bb (current_fun_name, current_bb_num);
    }
  if (current_fun_name)
    {
      output_graph_tailer_fun (current_fun_name);
      free (current_fun_name);
    }

  output_graph_tailer ();
}
