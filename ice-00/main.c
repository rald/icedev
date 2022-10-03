#include <stdio.h>
#include <stdlib.h>



#include "common.h"



#define TOKEN_IMPLEMENTATION
#include "token.h"

#define LEXER_IMPLEMENTATION
#include "lexer.h"




void loadFile(char *path,char **code,size_t *ncode) {

    FILE *fp = fopen(path, "r");

    if (fp != NULL) {
        if (fseek(fp, 0L, SEEK_END) == 0) {
            long bufsize = ftell(fp);
            if (bufsize == -1) { /* Error */ }

            (*code) = malloc(sizeof(**code) * (bufsize + 1));

            if(fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

            (*ncode)=fread(*code,sizeof(**code),bufsize,fp);
            if ((*ncode) == 0) {
                fprintf(stderr,"Error: cannot read file %s", path);
                free(*code);
                (*code)=NULL;
            } else {
                (*code)[++(*ncode)] = '\0';
            }
        }
        fclose(fp);
    } else {
        perror(path);
    } 
}



int main(int argc,char **argv) {

  char *code=NULL;
  size_t ncode=0;

  Token **tokens=NULL;
  size_t ntokens=0;

   if(argc!=2) {
    fprintf(stderr,"Syntax: %s filename\n",argv[0]);
    return 1;
  }

  loadFile(argv[1],&code,&ncode);

  lex(code,ncode,&tokens,&ntokens);


  return 0;
}


