#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    Lexer *lexer;       // pointer to lexer
    Token current_token; // current token we are looking at
} Parser;

// functions
void parser_init(Parser *parser, Lexer *lexer);
ASTNode* parse(Parser *parser);
void parser_expect(Parser *parser, TokenType type);
#endif