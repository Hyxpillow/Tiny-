/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/


#include "analyze.h"
#include "globals.h"
/* counter for variable memory locations */
static int location = 0;

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode * t,
               void (* preProc) (TreeNode *),
               void (* postProc) (TreeNode *) )
{ if (t != NULL)
  { preProc(t);
    { int i;
      for (i=0; i < MAXCHILDREN; i++)
        traverse(t->child[i],preProc,postProc);
    }
    postProc(t);
    traverse(t->sibling,preProc,postProc);
  }
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t)
{ if (t==NULL) return;
  else return;
}
//------------------------------------------------------------------新增的声明报错语句
static void DeclarationError(TreeNode * t, char * message)
{ fprintf(listing,"Declaration error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode( TreeNode * t)
{ switch (t->nodekind)
  { case StmtK:
      switch (t->kind.stmt)
      { case AssignK:
        case ReadK:
          if (st_lookup(t->attr.name) == -1)
          /* not yet in table, so treat as new definition */
            DeclarationError(t, strcat(t->attr.name, " undeclared identifier"));
          else
          /* already in table, so ignore location, 
             add line number of use only */ 
            st_insert(t->attr.name,t->lineno,0,t->type);
          break;
        default:
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      { case IdK:
          if (st_lookup(t->attr.name) == -1)
            DeclarationError(t, strcat(t->attr.name, " undeclared identifier"));
          else
          /* already in table, so ignore location, 
             add line number of use only */ 
            st_insert(t->attr.name,t->lineno,0,t->type);
          break;
        default:
          break;
      }
      break;
    case Definek:
      switch (t->kind.define)
      { case IntD:
        case CharD:
          if (st_lookup(t->attr.name) == -1)
          /* not yet in table, so treat as new definition */
            st_insert(t->attr.name,t->lineno,location++,t->type);
          else
          /* already in table, so ignore location, 
             add line number of use only */ 
            DeclarationError(t, strcat(t->attr.name, " previous declaration"));
          break;
        
        default:
          break;
      }
      break;
    default:
      break;
  }
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ traverse(syntaxTree,insertNode,nullProc);
  if (TraceAnalyze)
  { fprintf(listing,"\nSymbol table:\n\n");
    printSymTab(listing);
  }
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}


/* Procedure checkNode performs
 * type checking at a single tree node
 */
//------------------------------------------backup---------------
// static void checkNode(TreeNode * t)
// { switch (t->nodekind)
//   { case ExpK:
//       switch (t->kind.exp)
//       { case OpK:
//           if ((t->child[0]->type != Integer) ||
//               (t->child[1]->type != Integer))
//             typeError(t,"Op applied to non-integer");
//           if ((t->attr.op == EQ) || (t->attr.op == LT))
//             t->type = Boolean;
//           else
//             t->type = Integer;
//           break;
//         case ConstK:
//         case IdK:
//           t->type = Integer;
//           break;
//         default:
//           break;
//       }
//       break;
//     case StmtK:
//       switch (t->kind.stmt)
//       { case IfK:
//           if (t->child[0]->type == Integer)
//             typeError(t->child[0],"if test is not Boolean");
//           break;
//         case AssignK:
//           if (t->child[0]->type != Integer)
//             typeError(t->child[0],"assignment of non-integer value");
//           break;
//         case WriteK:
//           if (t->child[0]->type != Integer)
//             typeError(t->child[0],"write of non-integer value");
//           break;
//         case RepeatK:
//           if (t->child[1]->type == Integer)
//             typeError(t->child[1],"repeat test is not Boolean");
//           break;
//         default:
//           break;
//       }
//       break;
//     default:
//       break;  

//   }
// }
static void checkNode(TreeNode * t)
{ int temp_type;
  switch (t->nodekind)
  { case ExpK:
      switch (t->kind.exp)
      { case OpK:
          if ((t->child[0]->type != Integer) ||
              (t->child[1]->type != Integer)) {
                //printf("1: %d 2 : %d\n", t->child[0]->type, t->child[1]->type);
                typeError(t,"Op applied to non-integer");
              }
            
          if ((t->attr.op == EQ) || (t->attr.op == LT) || (t->attr.op == RT) || (t->attr.op == LTE) || (t->attr.op == RTE))
            t->type = Boolean;
          else
            t->type = Integer;
          break;
        case ConstK:
          t->type = Integer;
          break;
        case IdK:
          temp_type = st_lookup_type(t->attr.name);
          if (temp_type == (int)Integer){
            t->type = Integer;
          } else if (temp_type == (int)Char) {
            t->type = Char;
          } else {
            typeError(t, "ID type Error");
          }
          break;
        default:
          typeError(t,"EXP kind ERROR");
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { case IfK:
          if (t->child[0]->type !=Boolean && t->child[0]->type != Integer)
            typeError(t->child[0],"if test is not Boolean");
          break;
        case AssignK:

          if (t->child[0]->type != st_lookup_type(t->attr.name)) {
             //printf("1: %d", t->type);
             typeError(t->child[0],"assignment of non_same type");
          }
          break;
        case WriteK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"write of non-integer value");
          break;
        case RepeatK:
          if (t->child[1]->type !=Boolean)
            typeError(t->child[1],"repeat test is not Boolean");
          break;
        default:
          break;
      }
      break;
    default:
      break;  

  }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ traverse(syntaxTree,nullProc,checkNode);
}
