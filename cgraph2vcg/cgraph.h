#ifndef CGRAPH_H
#define CGRAPH_H

struct function {
  char *name;
  struct function_list *calls;
  struct function_list *called;
  int met;
  int attr;
};

struct function_list_node {
  struct function *func;
  struct function_list_node *next;
};

struct function_list {
  struct function_list_node *head;
  struct function_list_node *tail;
};

extern struct function_list *all_func_list;
extern struct function_list *met_func_list;
extern struct function_list *current_func_list;

extern struct function * new_function (char *name);
extern struct function_list_node * new_function_list_node (struct function *f);
extern struct function_list * new_function_list (void);
extern void add_function (struct function_list *fl, struct function *f);
extern struct function * find_function (struct function_list *fl, char *name);

extern void output (void);

#endif
