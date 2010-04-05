%{
  #include <string.h>
  #include "yacc.tab.h"
%}

blanks [[:blank:]]*
identifier [[:alpha:]_][[:alnum:]_]*

%option noyywrap

%%

"  calls:" {
    return CALLS;
  }

"  is called by:" {
    return CALLED;
  }

"(defined):" {
    return DEFINED;
  }

"(external):" {
    return EXTERNAL;
  }

"Indirect <indirect>:" {

  }

"<indirect>" {

  }

"possible aliases:".* {

  }

{identifier} {
    yylval.str = strdup (yytext);
    return FUNCTION;
}

. {  }
\n { return NL; }

%%
