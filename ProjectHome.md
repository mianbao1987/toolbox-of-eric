**libiberty**

> The libiberty library used by the tools here.

**tree2vcg**

> Generate vcg format file from gcc tree dump, which can be viewed as a graph by a vcg tool (e.g. http://code.google.com/p/vcgviewer).

> Gcc can generate vcg format file only for rtl dump. So this tool can help you read the tree-level program.

**asm2vcg**

> Generate vcg format file from .s file. This requires gcc to be patched with output\_bb\_info.patch， which is based on gcc-4.4.0. The parser is based on mips assembly, so it may need a little changes if you want use it on x86 .s files or others.

**dominator**

> Build dominator tree according cfg.

**gdbinit**

> A collection of gcc builtin debug functions based on gcc-4.3.0, which can be used when debug gcc in gdb. Rename it as .gdbinit and put it under home directory or current directory.

**cgraph2vcg**

> Generate vcg format file from CIL's callgraph text (http://hal.cs.berkeley.edu/cil/). CIL's callgraph output is clearer than gcc's. Usage:

> ~/cil-1.3.7/bin/cilly `*`.c -I... --docallgraph > log

> ./cgraph2vcg log

> then, the output file is cgraph.vcg.

**create-profile-labels.patch**

> gcc -fcreate-profile-labels ...

> generate labels for each BB, this is very useful when using oprofile to collect samples of a program. This can make opfrofile to get the samples for each BB.

**gccbat**

> Some scripts to update gcc svn, configure, build and test automatically.


---


Note:

I don't use trunck and branch, and just put each package under svn directory.