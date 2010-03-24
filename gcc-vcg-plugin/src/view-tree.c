#include "tree.h"

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
      break;
    case TS_COMMON:
    case TS_INT_CST:
    case TS_REAL_CST:
    case TS_FIXED_CST:
    case TS_VECTOR:
    case TS_STRING:
    case TS_COMPLEX:
    case TS_IDENTIFIER:
    case TS_DECL_MINIMAL:
    case TS_DECL_COMMON:
    case TS_DECL_WRTL:
    case TS_DECL_NON_COMMON:
    case TS_DECL_WITH_VIS:
    case TS_FIELD_DECL:
    case TS_VAR_DECL:
    case TS_PARM_DECL:
    case TS_LABEL_DECL:
    case TS_RESULT_DECL:
    case TS_CONST_DECL:
    case TS_TYPE_DECL:
    case TS_FUNCTION_DECL:
      #define S (t->function_decl)
      dump_tree_decl_non_common (S.common);
      dump_tree (S.function_specific_target);
      dump_tree (S.function_specific_optimization);
      break;
    case TS_TYPE:
    case TS_LIST:
    case TS_VEC:
    case TS_EXP:
    case TS_SSA_NAME:
    case TS_BLOCK:
    case TS_BINFO:
    case TS_STATEMENT_LIST:
    case TS_CONSTRUCTOR:
    case TS_OMP_CLAUSE:
    case TS_OPTIMIZATION:
    case TS_TARGET_OPTION:
    }
}

void
vcg_plugin_view_tree (tree t)
{
}


