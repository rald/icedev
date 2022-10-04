#ifndef LEXER_H
#define LEXER_H



#include <stdio.h>
#include <string.h>
#include <ctype.h>



#define TAB_SIZE 2
#define TEXT_MAX 256



typedef enum LexerState {
	LEXERSTATE_DEFAULT=0,
	LEXERSTATE_INT,
	LEXERSTATE_STR,
	LEXERSTATE_IDENT,       
} LexerState;



void lex(char *code,size_t ncode,Token ***tokens,size_t *ntokens);



#ifdef LEXER_IMPLEMENTATION



void lex(char *code,size_t ncode,Token ***tokens,size_t *ntokens) {

  LexerState lexerState=LEXERSTATE_DEFAULT;

  size_t i=0;

  int c0,c1;

  size_t ln=0,cl=0;
	size_t sln=0,scl=0;

  char t[TEXT_MAX]="";

  while(i<ncode) {

  	c0=code[i];
  	if(i<=ncode-1) c1=code[i+1]; else c1=-1;

  	switch(lexerState) {
  	case LEXERSTATE_DEFAULT:
  		if(isdigit(c0)) {
  			sln=ln; scl=cl;
  			lexerState=LEXERSTATE_INT;
  			i--;
  			cl--;
  		} else if(isalpha(c0)) {
  			sln=ln; scl=cl;
  			lexerState=LEXERSTATE_IDENT;
  			i--;
  			cl--;
  		} else if(c0=='\"') {
 				sln=ln; scl=cl;
   			lexerState=LEXERSTATE_STR;
  		} else if(  
  					(c0=='=' && c1=='=') ||
  					(c0=='<' && c1=='=') ||
  					(c0=='>' && c1=='=') ||
  					(c0=='!' && c1=='=') ) {
  			sprintf(t,"%c%c",c0,c1);
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_REL_OP,t,ln,cl));
  			t[0]='\0';
  			i++;
  			cl++;
  		} else if(  (c0=='&' && c1=='&') ||
  								(c0=='|' && c1=='|') ) {
  			sprintf(t,"%c%c",c0,c1);
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_LOGIC_OP,t,ln,cl));
  			t[0]='\0';
  			i++;
  			cl++;
  		} else if(c0=='=') {
  			sprintf(t,"%c",c0);
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_ASSIGN_OP,t,ln,cl));
  			t[0]='\0';
  		} else if(c0=='+' || c0=='-') {
  			sprintf(t,"%c",c0);
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_MATH_OP,t,ln,cl));
  			t[0]='\0';
  		} else if(c0=='!' || c0=='&' || c0=='|') {
  			sprintf(t,"%c",c0);
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_LOGIC_OP,t,ln,cl));
  			t[0]='\0';
  		} else if(c0=='(' || c0==')') {
  			sprintf(t,"%c",c0);
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_PAREN,t,ln,cl));
  			t[0]='\0';
  		} else if(c0=='{' || c1=='}') {
  			sprintf(t,"%c",c0);
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_BRACE,t,ln,cl));
  			t[0]='\0';
  		} else if(c0=='\t') {
  			sprintf(t,"%c",c0);
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_TAB,t,ln,cl));
  			t[0]='\0';
  			cl+=TAB_SIZE;
  		} else if(c0==';') {
  			sprintf(t,"%c",c0);
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_SEMICOLON,t,ln,cl));
  			t[0]='\0';
  		} else if(c0=='\n') {
  			sprintf(t,"%c",c0);
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_NEWLINE,t,ln,cl));
  			t[0]='\0';
  			cl=0;
  			ln++;
  		} else {
  		}
  		break;
  	case LEXERSTATE_INT:
  		if(isdigit(c0)) {
  		  char s[2]={c0,'\0'};
  			strcat(t,s);    
  		} else {
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_INT,t,sln,scl));
  			t[0]='\0';
  			i--;
  			cl--;
  			lexerState=LEXERSTATE_DEFAULT;
  		}
  		break;
  	case LEXERSTATE_STR:
  		if(c0!='\"') {
    		char s[2]={'\0','\0'};
  			if(c0=='\\') {
  			  s[0]=c0;
  				strcat(t,s);    
  				c0=code[++i];
  				cl++;
  			}
  			if(c0!='\0') {
    			s[0]=c0;
  			  strcat(t,s);    
  			 }
  		} else {
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_STR,t,sln,scl));
  			t[0]='\0';
  			lexerState=LEXERSTATE_DEFAULT;
  		}
  		break;
  	case LEXERSTATE_IDENT:
  		if(isalnum(c0)) {
  			char s[2]={c0,'\0'};
  			strcat(t,s);    
  		} else {
  			Token_Append(tokens,ntokens,Token_New(TOKENTYPE_IDENT,t,sln,scl));
  			t[0]='\0';
  			i--;
  			cl--;
  			lexerState=LEXERSTATE_DEFAULT;
  		}
  		break;
  	}

  	i++;
  	cl++;
  }
}



#endif /* LEXER_IMPLEMENTATION */



#endif /* LEXER_H */



