#include "defs.h"
#include "data.h"
#include "decl.h"

// Miscellaneous functions 

// Ensure that the current token is t, and fetch the next token.
// Otherwise throw an error 

void match(int expectedToken, char *what){
  if (Token.token == expectedToken){
    scan(&Token);
  }
  else {
    fatals("Expected",what);
  }
}


// Match a semicolon and fetch the next token 
// Syntax checking for C 
void semi(void){
  match(T_SEMI, ";"); 
}

// Match a left brace and fetch the next token 
void lbrace(void){
  match(T_LBRACE, "{");
}

// Match a left brace and fetch the next token 
void rbrace(void){
  match(T_RBRACE, "}");
}

// Match a left parenthesis and fetch the next token 
void lparen(void){
  match(T_LPAREN, "(");
}

// Match a right parenthesis and fetch the next token 
void rparen(void){
  match(T_RPAREN, ")");
}
// Match an identifier and fetch the nexxt token 
void ident(void){
  match(T_IDENT,"identifier");
}

// Print out fatal messages 
void fatal(char *s){
  fprintf(stderr,"%s on line %d\n",s,Line); exit(1);
}

void fatals(char *s1, char*s2){
  fprintf(stderr,"%s:%s on line %d\n", s1, s2, Line); exit(1);
}

void fatald(char *s, int d){
  fprintf(stderr, "%s:%d on line %d\n", s, d, Line); exit(1);
}

void fatalc(char *s, int c){
  fprintf(stderr, "%s:%c on line %d\n", s, c, Line); exit(1);
}
