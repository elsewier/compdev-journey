#include "defs.h" 
#define extern_ 
#include "data.h"
#undef extern_ 
#include "decl.h"
#include <errno.h>

// Compiler setup and top-level execution 

// Initialise global variables 

static void init(){ 
  Line = 1;
  Putback = '\n';
}

// Print out a usage if started incorrectly 
static void usage(char *prog){
  fprintf(stderr, "Usage: %s infile \n", prog);
  exit(1);
}

// List of printable tokens 
char *tokstr[] = { "+", "-", "*", "/", "intlit"};

// Loop scanning in all the tokens in the input file. 
// Print out details of each token found.
static void scanfile(){ 
  struct token T; 

  while (scan(&T)){
    printf("Token %s",tokstr[T.token]);
    if (T.token == T_INTLIT)
      printf(", value %d",T.intvalue);
    printf("\n");
  }
}

// Main program: checkc arguments and a print a usage if we dont have an argument. 
// Open up the input file and call scanfile to scan the tokens in it. 

void main(int argc, char *argv[]){
  struct ASTnode *tree;
  if (argc != 2)
    usage(argv[0]);

  init();

  if ((Infile = fopen(argv[1], "r")) == NULL){
    fprintf(stderr, "Unable to open %s: %s\n", argv[1],strerror(errno));
    exit(1);
  }

  // Create the output file 
  if((Outfile = fopen("out.s","w")) == NULL){
    fprintf(stderr, "Unable to create out.s: %s\n",strerror(errno));
    exit(1);
  }

  // scanfile();
  scan(&Token);                   // Get the first token from the input 
  genpreamble();                  // Output the preamble 
  tree = compound_statement();    // Parse the compound statement in the input 
  genAST(tree, NOREG, 0);         // Generate the assembly code for it 
  genpostamble();                 // Output the postamble 
  fclose(Outfile);
  exit(0);
}
