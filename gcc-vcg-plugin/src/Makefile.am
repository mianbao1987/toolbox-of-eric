## Process this file with automake to produce Makefile.in

LIBTOOL = @LIBTOOL@

AM_YFLAGS = -d -t
AM_CFLAGS = $(LIBERTY_INC)

GCCPLUGINS_DIR = `gcc -print-file-name=plugin`

INCLUDES = \
        -I $(GCCPLUGINS_DIR)/include \
        -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\"

lib_LTLIBRARIES = libvcg-plugin.la

libvcg_plugin_la_SOURCES = \
        vcg-plugin.c \
        tree2vcg.c tree2vcg.h gdl.c gdl.h cfg.c cfg.h \
        fine-tune.c output.c tree2vcg-yacc.y tree2vcg-lex.l

libvcg_plugin_la_LIBADD = $(INTLLIBS)

