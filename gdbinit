define debug_aff
  call debug_aff($arg0)
end
document debug_aff
  Prints the affine VAL to the standard error, used for debugging.
  void debug_aff (aff_tree *val)
end

define debug_alias_info
  call debug_alias_info()
end
document debug_alias_info
  Dump alias information on stderr.
  void debug_alias_info (void)
end

define debug_all_asserts
  call debug_all_asserts()
end
document debug_all_asserts
  Dump all the registered assertions for all the names to stderr.
  void debug_all_asserts (void)
end

define debug_all_mem_sym_stats
  call debug_all_mem_sym_stats()
end
document debug_all_mem_sym_stats
  Dump memory reference stats for all memory symbols to stderr.
  void debug_all_mem_sym_stats (void)
end

define debug_all_omp_regions
  call debug_all_omp_regions()
end
document debug_all_omp_regions
  void debug_all_omp_regions (void)
end

define debug_all_value_ranges
  call debug_all_value_ranges()
end
document debug_all_value_ranges
  Dump all value ranges to stderr.
  void debug_all_value_ranges (void)
end

define debug_asserts_for
  call debug_asserts_for($arg0)
end
document debug_asserts_for
  Dump all the registered assertions for NAME to stderr.
  void debug_asserts_for (tree name)
end

define debug_bb
  call debug_bb($arg0)
end
document debug_bb
  void debug_bb (basic_block bb)
end

define debug_bb_n
  call debug_bb_n($arg0)
end
document debug_bb_n
  basic_block debug_bb_n (int n)
end

define debug_binfo
  call debug_binfo($arg0)
end
document debug_binfo
  void debug_binfo (tree elem)
end

define debug_bitmap
  call debug_bitmap($arg0)
end
document debug_bitmap
  Function to be called from the debugger to print the contents of a bitmap.
  void debug_bitmap (const_bitmap head)
end

define debug_bitmap_file
  call debug_bitmap_file($arg0,$arg1)
end
document debug_bitmap_file
  Debugging function to print out the contents of a bitmap.
  void debug_bitmap_file (FILE *file, const_bitmap head)
end

define debug_bitmap_set
  call debug_bitmap_set($arg0)
end
document debug_bitmap_set
  void debug_bitmap_set (bitmap_set_t set)
end

define debug_candidate
  call debug_candidate($arg0)
end
document debug_candidate
  Print candidates info, for debugging purposes. 
  void debug_candidate (int i)
end

define debug_candidates
  call debug_candidates($arg0)
end
document debug_candidates
  Print candidates info, for debugging purposes.  
  void debug_candidates (int trg)
end

define debug_cfg_stats
  call debug_cfg_stats()
end
document debug_cfg_stats
  Dump CFG statistics on stderr.  
  void debug_cfg_stats (void)
end

define debug_cgraph
  call debug_cgraph()
end
document debug_cgraph
  Dump the call graph to stderr. 
  void debug_cgraph (void)
end

define debug_cgraph_node
  call debug_cgraph_node($arg0)
end
document debug_cgraph_node
  Dump call graph node NODE to stderr.
  void debug_cgraph_node (struct cgraph_node *node)
end

define debug_class
  call debug_class($arg0)
end
document debug_class
  Debug interface to hierarchy dumping. 
  void debug_class (tree t)
end

define debug_constraint
  call debug_constraint($arg0)
end
document debug_constraint
  Print out constraint C to stderr. 
  void debug_constraint (constraint_t c)
end

define debug_constraints
  call debug_constraints($arg0)
end
document debug_constraints
  Print out all constraints to stderr. 
  void debug_constraints (void)
end

define debug_currdefs
  call debug_currdefs()
end
document debug_currdefs
  Dump the current reaching definition of every symbol to stderr.
  void debug_currdefs (void)
end

define debug_c_tree
  call debug_c_tree($arg0)
end
document debug_c_tree
  Print the tree T in full, on stderr.
  void debug_c_tree (tree t)
end

define debug_data_dependence_relation
  call debug_data_dependence_relation($arg0)
end
document debug_data_dependence_relation
  Dump function for a DATA_DEPENDENCE_RELATION structure.
  void debug_data_dependence_relation (struct data_dependence_relation *ddr)
end

define debug_decision
  call debug_decision($arg0)
end
document debug_decision
  void debug_decision (struct decision *d)
end

define debug_decision_list
  call debug_decision_list($arg0)
end
document debug_decision_list
  void debug_decision_list (struct decision *d)
end

define debug_decl_set
  call debug_decl_set($arg0)
end
document debug_decl_set
  Dump bitmap SET (assumed to contain VAR_DECLs) to FILE.
  void debug_decl_set (bitmap set)
end

define debug_defs_stack
  call debug_defs_stack($arg0)
end
document debug_defs_stack
  Dump the renaming stack (block_defs_stack) to stderr.  Traverse the
  stack up to a maximum of N levels.  If N is -1, the whole stack is
  dumped.  New levels are created when the dominator tree traversal
  used for renaming enters a new sub-tree.
  void debug_defs_stack (int n)
end

define debug_def_blocks
  call debug_def_blocks()
end
document debug_def_blocks
  Dump the DEF_BLOCKS hash table on stderr. 
  void debug_def_blocks (void)
end

define debug_dependencies
  call debug_dependencies($arg0,$arg1)
end
document debug_dependencies
  Print dependencies information for instructions between HEAD and TAIL.
  void debug_dependencies (rtx head, rtx tail)
end

define debug_dfa_stats
  call debug_dfa_stats()
end
document debug_dfa_stats
  Dump DFA statistics on stderr.
  void debug_dfa_stats (void)
end

define debug_df_chain
  call debug_df_chain($arg0)
end
document debug_df_chain
  void debug_df_chain (struct df_link *link)
end

define debug_df_defno
  call debug_df_defno($arg0)
end
document debug_df_defno
  void debug_df_defno (unsigned int defno)
end

define debug_df_insn
  call debug_df_insn($arg0)
end
document debug_df_insn
  void debug_df_insn (rtx insn)
end

define debug_df_ref
  call debug_df_ref($arg0)
end
document debug_df_ref
  void debug_df_ref (struct df_ref *ref)
end

define debug_df_reg
  call debug_df_reg($arg0)
end
document debug_df_reg
  void debug_df_reg (rtx reg)
end

define debug_df_regno
  call debug_df_regno($arg0)
end
document debug_df_regno
  void debug_df_regno (unsigned int regno)
end

define debug_df_useno
  call debug_df_useno($arg0)
end
document debug_df_useno
  void debug_df_useno (unsigned int defno)
end

define debug_dominance_info
  call debug_dominance_info($arg0)
end
document debug_dominance_info
  void debug_dominance_info (enum cdi_direction dir)
end

define debug_dominance_tree
  call debug_dominance_tree($arg0,$arg1)
end
document debug_dominance_tree
  Prints to stderr representation of the dominance tree (for direction DIR) rooted in ROOT.
  void debug_dominance_tree (enum cdi_direction dir, basic_block root)
end

define debug_dominator_optimization_stats
  call debug_dominator_optimization_stats()
end
document debug_dominator_optimization_stats
  Dump SSA statistics on stderr.
  void debug_dominator_optimization_stats (void)
end

define debug_ds
  call debug_ds($arg0)
end
document debug_ds
  void debug_ds (ds_t s)
end

define debug_dwarf
  call debug_dwarf()
end
document debug_dwarf
  Print all DWARF information collected for the compilation unit. This routine is a debugging aid only. 
  void debug_dwarf (void)
end

define debug_dwarf_die
  call debug_dwarf_die($arg0)
end
document debug_dwarf_die
  Print the information collected for a given DIE.
  void debug_dwarf_die (dw_die_ref die)
end

define debug_ebitmap
  call debug_ebitmap($arg0)
end
document debug_ebitmap
  Dump ebitmap BMAP to stderr.
  void debug_ebitmap (ebitmap bmap)
end

define debug_find_tree
  p debug_find_tree($arg0,$arg1)
end
document debug_find_tree
  bool debug_find_tree (tree top, tree search)
end

define debug_find_var_in_block_tree
  p debug_find_var_in_block_tree($arg0,$arg1)
end
document debug_find_var_in_block_tree
  If VAR is present in a subblock of BLOCK, return the subblock.
  tree debug_find_var_in_block_tree (tree var, tree block)
end

define debug_flow_info
  call debug_flow_info()
end
document debug_flow_info
  void debug_flow_info (void)
end

define debug_fold_checksum
  call debug_fold_checksum($arg0)
end
document debug_fold_checksum
  Helper function for outputting the checksum of a tree T.  When
  debugging with gdb, you can "define mynext" to be "next" followed
  by "call debug_fold_checksum (op0)", then just trace down till the
  outputs differ. 
  void debug_fold_checksum (const_tree t)
end

define debug_function
  call debug_function($arg0,$arg1)
end
document debug_function
  Dump FUNCTION_DECL FN to stderr using FLAGS (see TDF_* in tree.h)
  void debug_function (tree fn, int flags)
end

define debug_generic_expr
  call debug_generic_expr($arg0)
end
document debug_generic_expr
  Debugging function to print out a generic expression.
  void debug_generic_expr (tree t)
end

define debug_generic_stmt
  call debug_generic_stmt($arg0)
end
document debug_generic_stmt
  Debugging function to print out a generic statement.
  void debug_generic_stmt (tree t)
end

define debug_immediate_uses
  call debug_immediate_uses()
end
document debug_immediate_uses
  Dump def-use edges on stderr.
  void debug_immediate_uses (void)
end

define debug_immediate_uses_for
  call debug_immediate_uses_for($arg0)
end
document debug_immediate_uses_for
  Dump def-use edges on stderr.
  void debug_immediate_uses_for (tree var)
end

define debug_insn_slim
  call debug_insn_slim($arg0)
end
document debug_insn_slim
  Emit a slim dump of X (an insn) to stderr.
  void debug_insn_slim (rtx x)
end

define debug_lattice_value
  call debug_lattice_value($arg0)
end
document debug_lattice_value
  Print lattice value VAL to stderr. 
  void debug_lattice_value (prop_value_t val)
end

define debug_loop
  call debug_loop($arg0,$arg1)
end
document debug_loop
  Print on stderr the code of LOOP, at some VERBOSITY level. 
  void debug_loop (struct loop *loop, int verbosity)
end

define debug_loops
  call debug_loops($arg0)
end
document debug_loops
  Debugging loops structure at tree level, at some VERBOSITY level.
  void debug_loops (int verbosity)
end

define debug_loop_num
  call debug_loop_num($arg0,$arg1)
end
document debug_loop_num
  Print on stderr the code of loop number NUM, at some VERBOSITY level.
  void debug_loop_num (unsigned num, int verbosity)
end

define debug_may_aliases_for
  call debug_may_aliases_for($arg0)
end
document debug_may_aliases_for
  Dump to stderr the list of variables that may be aliasing VAR.
  void debug_may_aliases_for (tree var)
end

define debug_memory_partitions
  call debug_memory_partitions()
end
document debug_memory_partitions
  Dump memory partition information to stderr.
  void debug_memory_partitions (void)
end

define debug_mem_ref_stats
  call debug_mem_ref_stats()
end
document debug_mem_ref_stats
  Dump memory reference stats for function FN to stderr.
  void debug_mem_ref_stats (void)
end

define debug_mem_sym_stats
  call debug_mem_sym_stats($arg0)
end
document debug_mem_sym_stats
  Dump memory reference stats for variable VAR to stderr.
  void debug_mem_sym_stats (tree var)
end

define debug_mp_info
  call debug_mp_info($arg0)
end
document debug_mp_info
  Dump the MP_INFO array to stderr.
  void debug_mp_info (VEC(mem_sym_stats_t,heap) *mp_info)
end

define debug_names_replaced_by
  call debug_names_replaced_by($arg0)
end
document debug_names_replaced_by
  Dump all the names replaced by NAME to stderr.
  void debug_names_replaced_by (tree name)
end

define debug_omega_problem
  call debug_omega_problem($arg0)
end
document debug_omega_problem
  Debug problem PB.
  void debug_omega_problem (omega_pb pb)
end

define debug_omp_region
  call debug_omp_region($arg0)
end
document debug_omp_region
  void debug_omp_region (struct omp_region *region)
end

define debug_ops_vector
  call debug_ops_vector($arg0)
end
document debug_ops_vector
  Dump the operand entry vector OPS to STDERR.
  void debug_ops_vector (VEC (operand_entry_t, heap) *ops)
end

define debug_optab_libfuncs
  call debug_optab_libfuncs()
end
document debug_optab_libfuncs
  Print information about the current contents of the optabs on STDERR.
  void debug_optab_libfuncs (void)
end

define debug_pass
  call debug_pass()
end
document debug_pass
  Call from the debugger to get the current pass name.
  void debug_pass (void)
end

define debug_points_to_info
  call debug_points_to_info()
end
document debug_points_to_info
  Dump points-to info pointed to by PTO into STDERR.
  void debug_points_to_info (void)
end

define debug_points_to_info_for
  call debug_points_to_info_for($arg0)
end
document debug_points_to_info_for
  Dump points-to information for VAR into stderr.
  void debug_points_to_info_for (tree var)
end

define debug_print_page_list
  call debug_print_page_list($arg0)
end
document debug_print_page_list
  Prints the page-entry for object size ORDER, for debugging.
  void debug_print_page_list (int order)
end

define debug_referenced_vars
  call debug_referenced_vars()
end
document debug_referenced_vars
  Dump the list of all the referenced variables to stderr. 
  void debug_referenced_vars (void)
end

define debug_regions
  call debug_regions()
end
document debug_regions
  Print the regions, for debugging purposes.  Callable from debugger.
  void debug_regions (void)
end

define debug_regset
  call debug_regset($arg0)
end
document debug_regset
  Print a human-readable representation of R on the standard error stream.  
  void debug_regset (regset r)
end

define debug_reload
  call debug_reload()
end
document debug_reload
  void debug_reload (void)
end

define debug_rgn_dependencies
  call debug_rgn_dependencies($arg0)
end
document debug_rgn_dependencies
  Print dependences for debugging starting from FROM_BB.
  void debug_rgn_dependencies (int from_bb)
end

define debug_rli
  call debug_rli($arg0)
end
document debug_rli
  Print debugging information about the information in RLI.
  void debug_rli (record_layout_info rli)
end

define debug_rtx
  call debug_rtx($arg0)
end
document debug_rtx
  Call this function from the debugger to see what X looks like.
  void debug_rtx (const_rtx x)
end

define debug_rtx_find
  call debug_rtx_find($arg0,$arg1)
end
document debug_rtx_find
  Call this function to search an rtx list to find one with insn uid UID,
  and then call debug_rtx_list to print it, using DEBUG_RTX_COUNT.
  The found insn is returned to enable further debugging analysis.
  const_rtx debug_rtx_find (const_rtx x, int uid)
end

define debug_rtx_list
  call debug_rtx_list($arg0,$arg1)
end
document debug_rtx_list
  Call this function to print list from X on.
  N is a count of the rtx's to print. Positive values print from the specified
  rtx on.  Negative values print a window around the rtx.
  EG: -5 prints 2 rtx's on either side (in addition to the specified rtx).  
  void debug_rtx_list (const_rtx x, int n)
end

define debug_rtx_range
  call debug_rtx_range($arg0,$arg1)
end
document debug_rtx_range
  Call this function to print an rtx list from START to END inclusive.
  void debug_rtx_range (const_rtx start, const_rtx end)
end

define debug_sa_points_to_info
  call debug_sa_points_to_info()
end
document debug_sa_points_to_info
  Debug points-to information to stderr.
  void debug_sa_points_to_info (void)
end

define debug_sbitmap
  call debug_sbitmap($arg0)
end
document debug_sbitmap
  void debug_sbitmap (const_sbitmap bmap)
end

define debug_solution_for_var
  call debug_solution_for_var($arg0)
end
document debug_solution_for_var
  Print the points-to solution for VAR to stdout.
  void debug_solution_for_var (unsigned int var)
end

define debug_sra_elt_name
  call debug_sra_elt_name($arg0)
end
document debug_sra_elt_name
  Print ELT in a nice human-readable format.
  void debug_sra_elt_name (struct sra_elt *elt)
end

define debug_subvars_for
  call debug_subvars_for($arg0)
end
document debug_subvars_for
  Dumb sub-variables for VAR to stderr.
  void debug_subvars_for (tree var)
end

define debug_ter
  call debug_ter($arg0,$arg1)
end
document debug_ter
  Dump the status of the various tables in the expression table.  This is used
  exclusively to debug TER.  F is the place to send debug info and T is the
  table being debugged. 
  void debug_ter (FILE *f, temp_expr_table_p t)
end

define debug_thunks
  call debug_thunks($arg0)
end
document debug_thunks
  Dump the thunks for FN.
  void debug_thunks (tree fn)
end

define debug_tree
  call debug_tree($arg0)
end
document debug_tree
  Print the node NODE on standard error, for debugging.
  Most nodes referred to by this one are printed recursively
  down to a depth of six.
  void debug_tree (tree node)
end

define debug_tree_bb
  call debug_tree_bb($arg0)
end
document debug_tree_bb
  Dump a basic block on stderr.
  void debug_tree_bb (basic_block bb)
end

define debug_tree_bb_n
  call debug_tree_bb_n($arg0)
end
document debug_tree_bb_n
  Dump basic block with index N on stderr. 
  basic_block debug_tree_bb_n (int n)
end

define debug_tree_cfg
  call debug_tree_cfg($arg0)
end
document debug_tree_cfg
  Dump the CFG on stderr.
  FLAGS are the same used by the tree dumping functions
  (see TDF_* in tree-pass.h).
  void debug_tree_cfg (int flags)
end

define debug_tree_chain
  call debug_tree_chain($arg0)
end
document debug_tree_chain
  Debugging function to print out a chain of trees . 
  void debug_tree_chain (tree t)
end

define debug_tree_ssa
  call debug_tree_ssa()
end
document debug_tree_ssa
  Dump SSA information to stderr. 
  void debug_tree_ssa (void)
end

define debug_tree_ssa_stats
  call debug_tree_ssa_stats()
end
document debug_tree_ssa_stats
  Dump SSA statistics on stderr.
  void debug_tree_ssa_stats (void)
end

define debug_update_ssa
  call debug_update_ssa()
end
document debug_update_ssa
  Dump SSA update information to stderr.
  void debug_update_ssa (void)
end

define debug_value_data
  call debug_value_data($arg0)
end
document debug_value_data
  Dump the value chain data to stderr.
  void debug_value_data (struct value_data *vd)
end

define debug_value_expressions
  call debug_value_expressions($arg0)
end
document debug_value_expressions
  void debug_value_expressions (tree val)
end

define debug_value_range
  call debug_value_range($arg0)
end
document debug_value_range
  Dump value range VR to stderr.
  void debug_value_range (value_range_t *vr)
end

define debug_variable
  call debug_variable($arg0)
end
document debug_variable
  Dump variable VAR and its may-aliases to stderr. 
  void debug_variable (tree var)
end

