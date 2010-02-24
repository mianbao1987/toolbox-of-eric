#include <config.h>

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "plugin.h"
#include "plugin-version.h"

#include "gcc-plugin.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "toplev.h"
#include "gimple.h"
#include "tree-pass.h"
#include "intl.h"
#include "langhooks.h"

int plugin_is_GPL_compatible;

int
plugin_init (struct plugin_name_args *plugin_info,
             struct plugin_gcc_version *version)
{
  if (!plugin_default_version_check (version, &gcc_version))
    return 1;

  return 0;
}

void
vvp_dump_file (tree fn, FILE *dump)
{
  const char *dname, *aname;

  dname = lang_hooks.decl_printable_name (fn, 2);
  aname = (IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (fn)));
  fprintf (dump, "\n;; Function %s (%s)\n\n", dname, aname);
  
  dump_function_to_file (fn, dump, TDF_BLOCKS);
}

int
vcgview (void)
{
  int argc = 2;
  char *argv[2] = {"vcgview", "tmp.vcg"};
  FILE *dump_file, *vcg_file;
  
  tree fn;

  pid_t pid;

  fn = current_function_decl;
  dump_file = fopen ("tmp.dump", "w");
  vcg_file = fopen ("tmp.vcg", "w");

  vvp_dump_file (fn, dump_file);

  fclose (dump_file);

  dump_file = fopen ("tmp.dump", "r");
  vvp_tree2vcg (dump_file, vcg_file);

  fclose (dump_file);
  fclose (vcg_file);

  pid = fork ();
  if (pid == 0)
    system ("vcgview tmp.vcg");

  return 0;
  //return vcgview_main (argc, argv);
}
