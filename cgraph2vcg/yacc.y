%{
  #include "cgraph.h"

  void yyerror (char const *s);

  struct function *current_func;
  struct function_list *current_func_list;

  static int attr;
%}

%union {
  int val;
  char *str;
}

%token FUNCTION CALLS CALLED NL DEFINED EXTERNAL

%type <str> FUNCTION
%type <val> NL CALLS CALLED DEFINED EXTERNAL
%type <val> attribute

%debug
%verbose

%%

input: /* empty */
	| input unit
	| input NL

unit: FUNCTION attribute NL {
    current_func = find_function (all_func_list, $<str>1);
    if (current_func == NULL)
      {
        current_func = new_function ($<str>1);
        current_func->calls = new_function_list ();
        current_func->called = new_function_list ();
        add_function (all_func_list, current_func);
      }

    current_func->met = 1;
    if (attr == 1)
      current_func->attr = 1;

    if (find_function (met_func_list, $<str>1) == NULL)
      {
        add_function (met_func_list, current_func);
      }
    
  } CALLS {
    current_func_list = current_func->calls;

  } function_list NL {
    current_func->calls = current_func_list;

  } CALLED {
    current_func_list = current_func->called;

  } function_list NL {
    current_func->called = current_func_list;
  }

function_list: /* empty */
	| function_list FUNCTION {
    struct function *func;
    
    func = find_function (all_func_list, $<str>2);
    if (func == NULL)
      {
        func = new_function ($<str>2);
        func->calls = new_function_list ();
        func->called = new_function_list ();
        add_function (all_func_list, func);
      }

    if (find_function (current_func_list, $<str>2) == NULL)
      add_function (current_func_list, func);
  }

attribute: DEFINED {
    attr = 1;
  }
	| EXTERNAL {
    attr = 0;
  }

%%

void
yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

void
set_yy_debug (void)
{
  yydebug = 1;
}

