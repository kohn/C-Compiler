/***************************
C-minus Compiler -
Compiler Design Course Project
***************************/

#include "globals.h"
#include "utils.h"
#include "parse.h"
#include "symtab.h"
#include "codegen.h"

#define FILE_NAME_LEN 100

FILE* source; /* source code text file */
FILE* listing; /* listing output text file */
FILE* code; /* code text file for TM simulator */


/*debug flags*/
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;
SymbolTable CompoundST;
SymbolTable ParamST;

void init()
{
     CompoundST = newSymbolTable(LOCAL);
     ParamST = newSymbolTabl(PARAM);
}
int main(int argc, char *argv[])
{
  
    char sourcefile[FILE_NAME_LEN]; /* source code file name */

    if (argc != 2){ 
      fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }

    strcpy(sourcefile,argv[1]) ;
    source = fopen(sourcefile,"r");
    if (!source){ 
      fprintf(stderr,"File %s not found\n",sourcefile);
      exit(1);
    }

    listing = stdout; /* send listing to screen */
    fprintf(listing,"\nC-minus Compiler\ntarget: %s\n",sourcefile);

    yyrestart(source);
    yyparse();
    fprintf(listing,"\nParsing Finished...\n");

    if (! Error){ 
      
      // ??????
      fprintf(listing,"\nSemantic Analysis Finished...\n");
    }

    if (! Error){ 
      char * codefile = (char *) calloc(strlen(sourcefile), sizeof(char));
      strcpy(codefile,sourcefile);
      strcat(codefile,".tm");
      code = fopen(codefile,"w");
      if (!code){ 
        fprintf(stderr, "Unable to open %s\n",codefile);
        exit(1);
      }
      codeGen();
      fclose(code);
      fprintf(listing,"\nCode Generation Finished...\n");
    }

    fclose(source);
    return 0;
}


