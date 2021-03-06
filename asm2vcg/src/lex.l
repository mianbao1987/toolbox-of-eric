/* Lex file for asm2vcg.

   Copyright (C) 2009 Eric Fisher, joefoxreal@gmail.com. 

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */

%{
  #include <assert.h>
  #include <string.h>
  #include <libiberty.h>
  #include "yacc.h"
%}

blanks [[:blank:]]*
digits [[:digit:]]+
identifier [[:alpha:]][[:alnum:]_]*

%option noyywrap

%s fn 
%s bb
%s pred
%s succ

%%

^{blanks}".ent"/.* {
    BEGIN (fn);
    return FN;
  }

<fn>{identifier} {
    yylval.str = xstrdup (yytext);
    return FN_NAME;
  }

^{blanks}"# BLOCK" {
    BEGIN (bb);
    return BB;
  }

<bb>{digits} {
    yylval.str = xstrdup (yytext);
    BEGIN (INITIAL);
    return BB_NUM;
  }

^{blanks}"# PRED:" {
    BEGIN (pred);
    return PRED;
  }

<pred>"ENTRY" {
    yylval.str = xstrdup (yytext);
    return PRED_NUM;
  }

<pred>{digits} {
    yylval.str = xstrdup (yytext);
    return PRED_NUM;
  }

^{blanks}"# SUCC:" {
    BEGIN (succ);
    return SUCC;
  }

<succ>"EXIT" {
    yylval.str = xstrdup (yytext);
    return SUCC_NUM;
  }

<succ>{digits} {
    yylval.str = xstrdup (yytext);
    return SUCC_NUM;
  }

^{blanks}"."?{identifier}":".* {
    char *s, *t;

    for (s = yytext; *s == ' ' || *s == '\t'; s++);
    t = strchr (yytext, ':');
    yylval.str = xstrndup (s, t - s + 1);
    return LABEL;
  }

^{blanks}{identifier}.* {
    char *s, *t;

    for (s = yytext; *s == ' ' || *s == '\t'; s++);
    t = strchr (yytext, '#');
    if (t == NULL)
      t = yytext + strlen (yytext);
    t--;
    while (*t == ' ' || *t == '\t') t--;
    assert (s < t);
    yylval.str = xstrndup (s, t - s + 1);
    return STMT;
  }

<pred,succ>"("[^\)]*")" { /* omit */ }
<pred,succ>"["[^\]]*"]" { /* omit */ }
<pred>\n { BEGIN (INITIAL); }
<succ>\n { BEGIN (INITIAL); }

"#".* {
    /* omit other comments */
  }

^{blanks}"."{identifier}.* {
    /* omit other asm directive */
  }

. { /* omit others */ }
\n { /* omit others */ }

%%
