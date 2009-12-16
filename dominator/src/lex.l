%{
  #include <stdio.h>
  #include "yacc.h"
%}

%option noyywrap

%%

[:space:]* {
  /* whitespace */
}

#.* {
  /* comment */
}

[_[:alnum:]]+ {
  yylval.str = strdup (yytext);
  /* printf ("value: %s\n", yylval.str); */
  return VERTEX;
}

-> {
  return ARROW;
}

\n {
  return NL;
}

. {
  /* others */
}

%%

