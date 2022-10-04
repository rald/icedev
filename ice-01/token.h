#ifndef TOKEN_H
#define TOKEN_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "common.h"



typedef enum TokenType {
    TOKENTYPE_NONE=0,
    TOKENTYPE_INT,
    TOKENTYPE_STR,
    TOKENTYPE_IDENT,
    TOKENTYPE_PAREN,
    TOKENTYPE_BRACE,
    TOKENTYPE_TAB,
    TOKENTYPE_NEWLINE,
    TOKENTYPE_SEMICOLON,
    TOKENTYPE_ASSIGN_OP,
    TOKENTYPE_MATH_OP,
    TOKENTYPE_REL_OP,
    TOKENTYPE_LOGIC_OP,
    TOKENTYPE_BIT_OP,
    TOKENTYPE_MAX
} TokenType;



typedef struct Token Token;



struct Token {
    TokenType type;
    char *text;
    size_t ln;
    size_t cl;
};



Token *Token_New(TokenType type,char *text,size_t ln,size_t cl);
void Token_Free(Token *token);
void Token_Append(Token ***tokens,size_t *ntokens,Token *token);


char *TokenTypeNames[]={
  "none",
  "int",
  "str",
  "ident",
  "paren",
  "brace",  
  "tab",
  "newline",
  "semicolon",
  "assign op",
  "math op",
  "rel op",
  "logic op",
  "bit op"  
};



#ifdef TOKEN_IMPLEMENTATION



Token *Token_New(TokenType type,char *text,size_t ln,size_t cl) {
    Token *token=malloc(sizeof(*token));
    if(token) {
        token->type=type;
        token->text=strdup(text);
        token->ln=ln+1;
        token->cl=cl+1;
    }
    return token;
}



void Token_Free(Token *token) {
    free(token->text);
    free(token);
}



void Token_Append(Token ***tokens,size_t *ntokens,Token *token) {
  (*tokens)=realloc(*tokens,sizeof(**tokens)*((*ntokens)+1));
  (*tokens)[(*ntokens)++]=token;
}



char *Token_ToString(Token *token) {
  char *s=malloc(sizeof(*s)*STRING_MAX);
  sprintf(s,"{ type: %s, text: \"%s\", line: %zu, column: %zu }",TokenTypeNames[token->type],token->text,token->ln,token->cl);
  return s;
}



#endif /* TOKEN_IMPLEMENTATION */



#endif /* TOKEN_H */



