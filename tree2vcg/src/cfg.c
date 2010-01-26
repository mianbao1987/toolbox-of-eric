
struct basic_block *
new_bb (char *name)
{
  struct basic_block *bb;

  bb = (struct basic_block *) xmalloc (sizeof (struct basic_block));
  bb->name = name;

  bb->x_graph = gdl_new_bb_graph (name);

  return bb;
}

struct control_flow_graph *
new_cfg (void)
{
  struct control_flow_graph *cfg;

  cfg = (struct control_flow_graph *)
        xmalloc (sizeof (struct control_flow_graph));
  cfg->bb_num = 2;
  cfg->edge_num = 0;

  return cfg;  
}

struct function *
new_func (char *name)
{
  struct function *func;

  func = (struct function *) xmalloc (sizeof (struct function));
  func->name = name;
  func->cfg = new_cfg ();
  func->next = NULL:
  func->prev = NULL:

  func->x_graph = gdl_new_func_graph (name);

  return func;
}

void
add_bb (struct function *func, struct basic_block *bb)
{
  assert (func->cfg->entry != NULL && func->cfg->exit != NULL);

  bb->prev = func->cfg->exit->prev;
  bb->next = func->cfg->exit;
  func->cfg->exit->prev->next = bb;
  func->cfg->exit->prev = bb;

  func->cfg->bb_num++;
}

struct basic_block *
lookup_and_add_bb (struct function *func, char *name)
{
  struct basic_block *bb;

  for (bb = func->cfg->entry; bb != func->cfg->exit->next; bb = bb->next)
    {
      if (strcmp (bb->name, name) == 0)
        return bb;
    }

  bb = new_bb (name);
  add_bb (func, bb);

  return bb;
}

struct edge *
lookup_and_add_edge (struct function *func, 
                     char *source_name, char *target_name)
{
  struct basic_block *source_bb, *target_bb;
  struct edge *e;

  source_bb = lookup_and_add_bb (func, source_name);
  target_bb = lookup_and_add_bb (func, target_name);

  for (e = func->cfg->edge; e != NULL; e = e->next)
    {
      if (e->source == source_bb && e->target == target_bb)
        return e;
    }
  e = new_edge (source, target);
  add_edge (func, e);

  return e;
}
