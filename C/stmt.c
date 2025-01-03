#include "defs.h"
#include "data.h"
#include "decl.h"


// Parsing of statements 

// statements: statement 
//        | statement statements 
//       ; 
//
// statement: 'print' expression ';'
//       ;

// Parse one or more statements 
void statements(void){
  struct ASTnode *tree;
  int reg;

  while (1){
    // Match a 'print' as the first token 
    match(T_PRINT, "print");

    // Parse the following expression and generate the assembly code 
    tree = binexpr(0);
    reg = genAST(tree); // converts the tree into assembly code 
    genprintint(reg); // print to the screen 
    genfreeregs();    // free the register 

    // Match the following semicolon and stop if we are at EOF 
    semi();
    if (Token.token == T_EOF)
      return; 
  }
}
