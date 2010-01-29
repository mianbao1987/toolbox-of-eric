struct gdl_graph *top_graph;

void
cfg_to_vcg (void)
{
  struct gdl_graph *fun_graph;
  struct gdl_graph *bb_graph;
  struct gdl_node *node;
  struct gdl_edge *edge;

  struct control_flow_graph *cfg = current_function->cfg;
  struct basic_block *bb;
  struct edge *e;

  top_graph = gdl_new_graph (NULL);

  for (current_function = first_function; current_function != NULL;
       current_function = current_function->next)
    {
      fun_graph = gdl_new_graph (current_function->name);
      gdl_add_subgraph (top_graph, fun_graph);

      /* bb to subgraph & node */
      for (bb = cfg->bb; bb != NULL; bb = bb->next)
        {
          bb_graph = gdl_new_graph (bb->name);
          gdl_set_graph_label (bb_graph, bb->name);
          gdl_add_subgraph (fun_graph, bb_graph);

          node = gdl_new_node (NULL);
          gdl_add_node (bb_graph, node);
        }

      /* edge */
      for (e = cfg->edge; e != NULL; e = e->next)
        {
          edge = gdl_new_edge (e->source->name, e->target->name);
          gdl_add_edge (fun_graph, edge);
        }
    }
}
