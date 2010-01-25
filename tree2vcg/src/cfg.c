
struct parse_unit  *trans_unit;
struct function *func;
struct control_flow_graph *cfg;

struct basic_block *
new_bb (char *name)
{
  struct basic_block *bb;

  bb = (struct basic_block *) xmalloc (sizeof (struct basic_block));
  bb->name = name;

  bb->x_graph = new_graph (name);
  gdl_set_graph_label (bb->x_graph, name);
  bb_node = new_node (NULL);
  gdl_add_subgraph (bb->x_graph, bb_node);

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

  func->x_graph = gdl_new_graph (name);
  gdl_add_subgraph (top_graph,  func->x_graph);

  bb_node = new_node ("ENTRY");
  set_node_label (bb_node, "ENTRY");
  add_node (fun_graph, bb_node);
  bb_node = new_node ("EXIT");
  set_node_label (bb_node, "EXIT");
  add_node (fun_graph, bb_node);

  return func;
}

void
set_cfg_
