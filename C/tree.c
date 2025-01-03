#include "defs.h" 
#include "data.h"
#include "decl.h"

// AST tree functions 


// Build and return a generic AST node 
struct ASTnode *mkastnode(int op, struct ASTnode *left, 
                          struct ASTnode *right, int intvalue){ 

  struct ASTnode *n; // pointer, holds the newly created AST node 

  // Malloac a new ASTnode 
  n = (struct ASTnode *) malloc(sizeof(struct ASTnode)); // this is like a new branch 
  if (n == NULL){
    fatal("Unable to malloc in mkastnode()");
  }
  // Copy in the field values and return it 
  n-> op        = op;
  n-> left      = left; 
  n-> right     = right;
  n-> v.intvalue  = intvalue; 
  return (n);
}

// Make an AST leaf node 
struct ASTnode *mkastleaf(int op, int intvalue){
  // left and right set to NULL, which means that this node has no children 
  return (mkastnode(op, NULL, NULL, intvalue)); // returns a pointer to the newly created leaf node 
}

// Make a unary AST node: only one child 
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue){
  // right is set to NULL, which means that this node has only one child "left"
  return (mkastnode(op, left, NULL, intvalue));
}
