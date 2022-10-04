#include <SDL/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#include "common.h"



#define TOKEN_IMPLEMENTATION
#include "token.h"

#define LEXER_IMPLEMENTATION
#include "lexer.h"




int loadFile(char *path,char **code,size_t *ncode) {

	FILE *fp = fopen(path, "r");

	if (fp != NULL) {
		if (fseek(fp, 0L, SEEK_END) == 0) {
			long bufsize = ftell(fp);
			if (bufsize == -1) { 
				return 2;		
			}

			(*code) = malloc(sizeof(**code) * (bufsize + 1));

			if(fseek(fp, 0L, SEEK_SET) != 0) {
				return 3;
			}

			(*ncode)=fread(*code,sizeof(**code),bufsize,fp);
			(*code)[++(*ncode)] = '\0';
		}
		fclose(fp);
	} else {
		perror(path);
		return 1;
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

	for(size_t i=0;i<ntokens;i++) {
		printf("%s\n",Token_ToString(tokens[i]));
	}

	return 0;
}


