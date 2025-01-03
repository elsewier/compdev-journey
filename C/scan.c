#include "defs.h"
#include "data.h"
#include "decl.h"


// This file is doing lexical scanning


// Returns the position of character "c" in string "s", or "-1" if c is not found 

static int chrpos(char *s, int c){
  char *p; // pointer 
  p = strchr(s,c); // this function find the first occurrence of the character "c"" in the string "s"
  return (p ? p - s : -1); // this operator check if p is not "NULL". If p is not "NULL", it calculates the position of "c" by substracting the pointer to the start of the string "s" from the pointer p.
}


// Get the next character from the input file 
// static definition means that it is available on this file only
static int next(void) {
  int c; // character "c"

  if (Putback) {                // Use the character put  
    c = Putback;                // back if there is one 
    Putback = 0;
    return c; 
  }

  // tracking our current line 
  c = fgetc(Infile);            // Read from input file 
  if ('\n' == c)
    Line++;                     // Increment line count 
  return c; 
}

// Put back an unwanted character 
// if we have read too far ahead, we need to put it back to the input stream 
static void putback(int c){
  Putback = c; 
}


// This functions skips whitespace characters until it gets a non-whitespace character, and returns it 

static int skip(void){
  int c; 

  c = next(); // read 
  while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) { // do while non-character 
    c = next();
  }
  return (c); // returns the first character encountered 
}

// Scan and return an integer literal value from the input file
static int scanint(int c){ 
  int k, val = 0; 

  // Convert each character into an integer value 
  while ((k = chrpos("0123456789",c)) >= 0){
    val = val * 10 + k;
    c = next(); // find the next digit 
  }

  // if we hit a non-integer character, we need to put it back to the input stream 
  putback(c);
  return val; 
}

// Scan an identifier from the input file and store it in buf[].
// Return the identifier's length 
static int scanident(int c, char *buf, int lim){
  int i = 0;

  // Allow digits, alpha and underscores 
  while (isalpha(c) || isdigit(c) || '_' == c){
    // Error if we hit the identifier length limit 
    // Else append to buf[] and get next character 
    if (lim - 1 == i){
      printf("Identifier is too long on line %d\n",Line);
      exit(1);
    } else if (i < lim - 1){
      buf[i++] = c;
    }
    c = next();
  }
  // We hit a non-valid character, put it back. 
  // NUL-terminate the buf[] and return the length 
  putback(c);
  buf[i] = '\0';
  return (i);
}

// Given a word from the input, return the matching keyword token number or 0 if its not a keyword.
// Switch on the first letter so that we don't have to waste time strcomp()ing against all the keywords. 
static int keyword(char *s) {
  switch(*s) {
    case 'i':
      if (!strcmp(s, "int"))
        return (T_INT);
      break;
    case 'p':
      if(!strcmp(s, "print"))
  return (T_PRINT);
      break;
  }
  return (0);
}



// Scan and return the next token found in the input 
// Return 1 if the token valid, 0 if no tokens left 

int scan (struct token *t) {
  int c, tokentype; 

  // Skip whitespaces 
  c = skip(); 

  // Determine the token based on the input character 

  switch (c) {
    case EOF: 
      t->token = T_EOF;
      return (0);
    case '+':
      t->token = T_PLUS;  // assigning the token structure 
      break; 
    case '-':
      t->token = T_MINUS; // assigning the token structure 
      break; 
    case '*':
      t->token = T_STAR;  // assigning the token structure 
      break; 
    case '/':
      t->token = T_SLASH; // assigning the token structure 
      break; 
    case ';':
      t->token = T_SEMI;
      break;
    case '=':
      t->token = T_EQUALS;
      break; 
    default:
    // If its a digit, scan the literal integer value in 

    if(isdigit(c)){ 
      t->intvalue = scanint(c); // if we found a decimal digit character, call the helper function with this first character 
      t->token    = T_INTLIT;
      break;
    } else if (isalpha(c) || '_' == c){
        // Read in a keyword or identifier 
        scanident(c, Text, TEXTLEN);

        // If its a recognised keyword, return that token 
        if (tokentype = keyword(Text)){
          t-> token = tokentype;
          break;
        }
        // Not a recognised keyword, so it must be an identifier 
        t->token = T_IDENT;
        break;
      }

    // The character isnt part of any recognised token, error 
    fatalc("Unrecognised character",c);
  }
  // We have found a token! return 1 
  return (1); 
}
