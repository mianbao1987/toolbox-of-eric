#include <stdio.h>
#include <stdlib.h>

#include "cgraph.h"

struct function *
new_function (char *name)
{
  struct function *f;

  f = (struct function *) malloc (sizeof (struct function));
  if (f == NULL)
    {
      printf ("malloc failed\n");
      exit (-1);
    }
  
  f->name = name;
  f->calls = NULL;
  f->called = NULL;
  f->met = 0;
  f->attr = 0;

  return f;
}

struct function_list_node *
new_function_list_node (struct function *f)
{
  struct function_list_node *fn;

  fn = (struct function_list_node *) malloc
       (sizeof (struct function_list_node));
  if (fn == NULL)
    {
      printf ("malloc failed\n");
      exit (-1);
    }

  fn->func = f;
  fn->next = NULL;

  return fn;
}

struct function_list *
new_function_list (void)
{
  struct function_list *fl;

  fl = (struct function_list *) malloc (sizeof (struct function_list));
  if (fl == NULL)
    {
      printf ("malloc failed\n");
      exit (-1);
    }
  
  fl->head = NULL;
  fl->tail = NULL;

  return fl;
}

void
add_function (struct function_list *fl, struct function *f)
{
  struct function_list_node *fn;

  fn = new_function_list_node (f);
  if (fl->tail == NULL)
    {
      fl->head = fl->tail = fn;
    }
  else
    {
      fl->tail->next = fn;
      fl->tail = fn;
    }
}

struct function *
find_function (struct function_list *fl, char *name)
{
  struct function_list_node *fn;

  for (fn = fl->head; fn != NULL; fn = fn->next)
    {
      if (strcmp (fn->func->name, name) == 0)
        return fn->func;
    }

  return NULL;
}

