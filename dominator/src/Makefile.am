bin_PROGRAMS = dominator

AM_YFLAGS = -d -t
AM_CPPFLAGS = -I$(srcdir)/../include
AM_LDFLAGS = -L../libiberty -liberty

dominator_SOURCES = main.c dfs.c vec.c vec.h common.h yacc.y lex.l
dominator_LDADD = -liberty
