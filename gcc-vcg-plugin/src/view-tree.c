#include "tree.h"

void
dump_tree_base (struct tree_base s)
{
  
}

void
dump_tree_common (struct tree_common s)
{
  dump_tree_base (s.base);
  dump_tree (s.chain);
  dump_tree (s.type);
}

void
dump_tree_decl_minimal (struct tree_decl_minimal s)
{
  dump_tree_common (s.common);
  dump_tree (s.name);
  dump_tree (s.context);
}

void
dump_tree_decl_common (struct tree_decl_common s)
{
  dump_tree_decl_minimal (s.common);
  dump_tree (s.size);
  dump_tree (s.size_unit);
  dump_tree (s.initial);
  dump_tree (s.attributes);
  dump_tree (s.abstract_origin);
}

void
dump_tree_decl_with_rtl (struct tree_decl_with_rtl s)
{
  dump_tree_decl_common (s.common);
}

void
dump_tree_decl_with_wis (struct tree_decl_with_wis s)
{
  dump_tree_decl_with_rtl (s.common)
  dump_tree (s.assembler_name);
  dump_tree (s.section_name);
  dump_tree (s.comdat_group);
}

void
dump_tree_decl_non_common (struct tree_decl_non_common s)
{
  dump_tree_decl_with_wis (s.common);
  dump_tree (s.saved_tree);
  dump_tree (s.arguments);
  dump_tree (s.result);
  dump_tree (s.vindex);
}

void
dump_tree (tree t)
{
  switch (TREE_CODE (t))
    {
    case TS_BASE:
      dump_tree_base (t->base);
      break;
      
    case TS_COMMON:
      dump_tree_common (t->common);
      break;
      
    case TS_INT_CST:
      dump_tree_int_cst (t->int_cst);
      break;
      
    case TS_REAL_CST:
      dump_tree_real_cst (t->real_cst);
      break;
      
    case TS_FIXED_CST:
      dump_tree_fixed_cst (t->fixed_cst);
      break;
      
    case TS_VECTOR:
      dump_tree_vector (t->vector);
      break;
      
    case TS_STRING:
      dump_tree_string (t->string);
      break;
      
    case TS_COMPLEX:
      dump_tree_complex (t->complex);
      break;
      
    case TS_IDENTIFIER:
      dump_tree_identifier (t->identifier);
      break;
      
    case TS_DECL_MINIMAL:
      dump_tree_decl_minimal (t->decl_minimal);
      break;
      
    case TS_DECL_COMMON:
      dump_tree_decl_common (t->decl_common);
      break;
      
    case TS_DECL_WRTL:
      dump_tree_decl_wrtl (t->decl_wrtl);
      break;
      
    case TS_DECL_NON_COMMON:
      dump_tree_decl_non_common (t->decl_non_common);
      break;
      
    case TS_DECL_WITH_VIS:
      dump_tree_decl_with_vis (t->decl_with_vis);
      break;
      
    case TS_FIELD_DECL:
      dump_tree_field_decl (t->field_decl);
      break;
      
    case TS_VAR_DECL:
      dump_tree_var_decl (t->var_decl);
      break;
      
    case TS_PARM_DECL:
      dump_tree_parm_decl (t->parm_decl);
      break;
      
    case TS_LABEL_DECL:
      dump_tree_label_decl (t->label_decl);
      break;
      
    case TS_RESULT_DECL:
      dump_tree_result_decl (t->result_decl);
      break;
      
    case TS_CONST_DECL:
      dump_tree_const_decl (t->const_decl);
      break;
      
    case TS_TYPE_DECL:
      dump_tree_type_decl (t->type_decl);
      break;
      
    case TS_FUNCTION_DECL:
      dump_tree_function_decl (t->function_decl);
      break;
      
      #define S (t->function_decl)
      dump_tree_decl_non_common (S.common);
      dump_tree (S.function_specific_target);
      dump_tree (S.function_specific_optimization);
      break;
    case TS_TYPE:
      dump_tree_type (t->type);
      break;
      
    case TS_LIST:
      dump_tree_list (t->list);
      break;
      
    case TS_VEC:
      dump_tree_vec (t->vec);
      break;
      
    case TS_EXP:
      dump_tree_exp (t->exp);
      break;
      
    case TS_SSA_NAME:
      dump_tree_ssa_name (t->ssa_name);
      break;
      
    case TS_BLOCK:
      dump_tree_block (t->block);
      break;
      
    case TS_BINFO:
      dump_tree_binfo (t->binfo);
      break;
      
    case TS_STATEMENT_LIST:
      dump_tree_statement_list (t->statement_list);
      break;
      
    case TS_CONSTRUCTOR:
      dump_tree_constructor (t->constructor);
      break;
      
    case TS_OMP_CLAUSE:
      dump_tree_omp_clause (t->omp_clause);
      break;
      
    case TS_OPTIMIZATION:
      dump_tree_optimization (t->optimization);
      break;
      
    case TS_TARGET_OPTION:
      dump_tree_target_option (t->target_option);
      break;
    }
}

void
vcg_plugin_view_tree (tree t)
{
}


