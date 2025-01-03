#include "defs.h"
#include "data.h"
#include "decl.h"

// Parsing of expressions 

// Parse a primary factor and return an AST node representing it. 
// Using Pratt Parser Method 

static struct ASTnode *primary(void){
  struct ASTnode *n;
  int id; 

  // For an INTLIT token, make a leaf AST node for it and scan in the next token. Otherwise a syntax error for any other token type.
  switch (Token.token){
    case T_INTLIT:
      n = mkastleaf(A_INTLIT, Token.intvalue);
      break; 
    
    case T_IDENT: 
      // Check that this identifier exists 
      id = findglob(Text);
      if (id == -1)
        fatals("Unknown variable", Text);

      // Make a leaf AST node for it 
      n = mkastleaf(A_IDENT, id);
      break; 

    default: 
      fatald("Syntax error, token", Token.token);
  }

    // Scan in the next token and return the leaf node 
    scan(&Token);
    return(n);
}


// Convert a token into an AST operation 
int arithop(int tokentype){
  switch (tokentype){
    case T_PLUS:
      return (A_ADD);
    case T_MINUS:
      return (A_SUBTRACT);
    case T_STAR:
      return (A_MULTIPLY);
    case T_SLASH:
      return (A_DIVIDE);
    default: 
      fprintf(stderr, "Unknown token in arithop() on line%d, token %d \n", Line, tokentype);
      exit(1);
  }
}

// Operator precedence for each token 
static int OpPrec[] = {0, 10, 10, 20, 20, 0};
//                    EOF +   -   *   /   INTLIT 
// higher number means higher precedence than lower numbers 

// check that we have a binary operator and return its precedence 

static int op_precedence(int tokentype) {
  int prec = OpPrec[tokentype];
  if (prec == 0){
    fprintf(stderr, "Syntax error on line %d, token %d \n", Line, tokentype);
    exit(1);
  }
  return (prec);
}


// Return an AST tree whose root is a binary operator 
// Parameter ptp is the previous token's precedence. 
struct ASTnode *binexpr(int ptp){ // binary expression 
  struct ASTnode *left, *right;
  int tokentype;

  // Get the integer literal on the left. 
  // Fetch the next token at the same time. 
  left = primary(); // primary node from the integer literal 

  // If we hit a semicolon, return just the left node 
  tokentype = Token.token;
  if (tokentype == T_SEMI)
    return (left);
 
    printf("Current token: %d, intvalue :%d\n",tokentype,Token.intvalue);
  // While the precedence of this token is more than that of the previous token precedence 
  while (op_precedence(tokentype) > ptp){

    // Fetch in the next integer literal 
    scan(&Token);

    // Recursively call binexpr() with the precedence of our token to build a sub-tree 
    right = binexpr(OpPrec[tokentype]);

    // Join that sub-tree with ours. Convert the token into an AST operation at the same time. 
    left = mkastnode(arithop(tokentype), left, right, 0);

    // Update the details of the current token.
    // If we hit a semicolon, return just the left node 
    tokentype = Token.token;
    if (tokentype == T_SEMI)
      return (left);
  }

  // Return the tree we have when the precedence is the same or lower 
  return (left);
}
