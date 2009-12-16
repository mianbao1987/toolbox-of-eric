%{
  #include <stdio.h>
  extern void yyerror (char const *s);
%}
 
%union {
  int i;
  char *str;
}

%token VERTEX ARROW NL

%%

file:
  | file NL
  | file vertices NL
  | file edges NL

vertices: vertex 
  | vertices vertex 

vertex: VERTEX {
  /* printf ("vertex: %s\n", $<str>1); */
  cfg_add_basic_block ($<str>1);
}

edges: edge 
  | edges edge 

edge: VERTEX ARROW VERTEX {
  /* printf ("edge: %s -> %s\n", $<str>1, $<str>3); */
  cfg_add_edge ($<str>1, $<str>3);
}

%%

void
yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

