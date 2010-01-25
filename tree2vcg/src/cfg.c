
struct basic_block *
new_bb (char *name)
{
  struct basic_block *bb;

  bb = (struct basic_block *) xmalloc (sizeof (struct basic_block));
  bb->name = name;

  current_bb_graph = new_graph (name);
  bb->x_graph = current_bb_graph;
  gdl_set_graph_label (current_bb_graph, name);

  current_bb_node = new_node (NULL);
  gdl_add_subgraph (current_bb_graph, current_bb_node);

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

  current_func_graph = gdl_new_graph (name);
  func->x_graph = current_func_graph;
  gdl_add_subgraph (top_graph, current_func_graph);

  current_bb_node = new_node ("ENTRY");
  set_node_label (current_bb_node, "ENTRY");
  add_node (current_func_graph, current_bb_node);

  current_bb_node = new_node ("EXIT");
  set_node_label (current_bb_node, "EXIT");
  add_node (current_fun_graph, current_bb_node);

  current_bb_node = NULL;

  return func;
}

void
add_bb (struct control_flow_graph *cfg, struct basic_block *bb)
{
  assert (cfg->entry != NULL && cfg->exit != NULL);

  bb->prev = cfg->exit->prev;
  bb->next = cfg->exit;
  cfg->exit->prev->next = bb;
  cfg->exit->prev = bb;

  cfg->bb_num++;
}
