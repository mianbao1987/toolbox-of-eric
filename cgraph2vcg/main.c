#include <stdio.h>
#include "cgraph.h"

FILE *fin, *fout;

struct function_list *all_func_list;
struct function_list *met_func_list;

#define VCG_FILE "cgraph.vcg"

extern FILE *yyin;
extern int yyparse (void);
extern void set_yy_debug (void);

int
main (int argc, char *argv[])
{
  if (argc != 2)
    {
      printf ("usage: %s input_file\n", argv[0]);
      return 0;
    }

  fin = fopen (argv[1], "r");
  if (fin == NULL)
    {
      printf ("failed to open file '%s'\n", argv[1]);
      return 0;
    }

  fout = fopen (VCG_FILE, "w");
  if (fout == NULL)
    {
      fclose (fin);
      printf ("failed to open file '%s'\n", VCG_FILE);
      return 0;
    }

  all_func_list = new_function_list ();
  met_func_list = new_function_list ();

  yyin = fin;
  //set_yy_debug (); 
  yyparse ();

  output ();

  fclose (fin);
  fclose (fout);

  return 0;
}
