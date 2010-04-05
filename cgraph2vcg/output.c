#include <stdio.h>
#include "cgraph.h"

extern FILE *fout;

void
output (void)
{
  struct function_list_node *fn, *fn2;

  fprintf (fout, "graph: {\n\
orientation: left_to_right\n");

  for (fn = met_func_list->head; fn != NULL; fn = fn->next)
    {
      if (fn->func->attr == 0)
        {
          printf ("omit external function '%s'\n", fn->func->name);
          continue;
        }

      fprintf (fout, "node: {\n\
title: \"%s\"\n\
label: \"%s\"\n\
}\n", fn->func->name, fn->func->name);

      if (fn->func->calls == NULL)
        continue;

      for (fn2 = fn->func->calls->head; fn2 != NULL; fn2 = fn2->next)
        {
          if (fn2->func->attr == 0)
            {
              printf ("omit external function '%s'\n", fn2->func->name);
              continue;
            }

          fprintf (fout, "edge: {sourcename: \"%s\" targetname: \"%s\"}\n",
                   fn->func->name, fn2->func->name);
        }
    }

  for (fn = all_func_list->head; fn != NULL; fn = fn->next)
    {
      if (fn->func->met == 1)
        continue;

      if (fn->func->attr == 0)
        continue;

      printf ("Warning: add missing function '%s'\n", fn->func->name);
      fprintf (fout, "node: {\n\
title: \"%s\"\n\
label: \"%s\"\n\
}\n", fn->func->name, fn->func->name);

      if (fn->func->calls == NULL)
        continue;

      for (fn2 = fn->func->calls->head; fn2 != NULL; fn2 = fn2->next)
        {
          if (fn2->func->attr == 0)
            continue;

          fprintf (fout, "edge: {sourcename: \"%s\" targetname: \"%s\"}\n",
                   fn->func->name, fn2->func->name);
        }

    }

  fprintf (fout, "}\n");
}
