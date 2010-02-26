#include <config.h>

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "gcc-plugin.h"
#include "plugin.h"
#include "plugin-version.h"

#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "toplev.h"
#include "gimple.h"
#include "tree-pass.h"
#include "intl.h"
#include "langhooks.h"

/* plugin license check */
int plugin_is_GPL_compatible;

/* vcg viewer tool, default is vcgview */
char *vcg_viewer = "vcgview";

/* plugin initialization */
int
plugin_init (struct plugin_name_args *plugin_info,
             struct plugin_gcc_version *version)
{
  int i;
  int argc = plugin_info->argc;
  struct plugin_argument *argv = plugin_info->argv;

  if (!plugin_default_version_check (version, &gcc_version))
    return 1;

  for (i = 0; i < argc; i++)
    {
      printf ("key: %s\n", argv[i].key);
      printf ("value: %s\n", argv[i].value);
      /* Get the vcg viewer tool, default is "vcgview". */
      if (strcmp (argv[i].key, "viewer") == 0)
        {
          vcg_viewer = argv[i].value;
        }
    }

  return 0;
}

void
vcg_plugin_dump_file (tree fn, FILE *dump)
{
  const char *dname, *aname;

  dname = lang_hooks.decl_printable_name (fn, 2);
  aname = (IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (fn)));
  fprintf (dump, "\n;; Function %s (%s)\n\n", dname, aname);
  
  dump_function_to_file (fn, dump, TDF_BLOCKS);
}

int
vcg_plugin_view (void)
{
  char *cmd;
  FILE *dump_file, *vcg_file;
  
  tree fn;

  pid_t pid;

  fn = current_function_decl;
  dump_file = fopen ("tmp.dump", "w");
  vcg_file = fopen ("tmp.vcg", "w");

  vcg_plugin_dump_file (fn, dump_file);

  fclose (dump_file);

  dump_file = fopen ("tmp.dump", "r");
  vcg_plugin_tree2vcg (dump_file, vcg_file);

  fclose (dump_file);
  fclose (vcg_file);

  cmd = concat (vcg_viewer, " tmp.vcg", NULL);
  pid = fork ();
  if (pid == 0)
    {
      system (cmd);
      exit (0);
    }

  return 0;
}
