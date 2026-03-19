#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// connect parser with lexer and read the first token
void parser_init(Parser *parser, Lexer *lexer) {
    parser->lexer = lexer;
    parser->current_token = lexer_next_token(lexer);
}

// expect the current token to be of a certain type and advance to the next token
void parser_expect(Parser *parser, TokenType type) {
    if (parser->current_token.type == type) {
        parser->current_token = lexer_next_token(parser->lexer);
    } else {
        printf("Syntax Error!\n");
        exit(1);
    }
}

// Create node
ASTNode* create_node(ASTNodeType type, char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));

    node->type = type;
    strcpy(node->value, value);

    // Initialize children to NULL
    node->left = NULL;
    node->right = NULL;

    return node;
}

// Parse factor (numbers and identifiers)
// examples: 5, x
ASTNode* parse_factor(Parser *parser) {

    Token token = parser->current_token;

    if (token.type == TOKEN_NUMBER) {
        parser_expect(parser, TOKEN_NUMBER);
        return create_node(AST_NUMBER, token.value);
    }

    if (token.type == TOKEN_IDENTIFIER) {
        parser_expect(parser, TOKEN_IDENTIFIER);
        return create_node(AST_IDENTIFIER, token.value);
    }

    printf("Invalid factor\n");
    exit(1);
}

// Parse term (multiplication and division)
// handles * and /
ASTNode* parse_term(Parser *parser) {

    ASTNode *node = parse_factor(parser);

    while (parser->current_token.type == TOKEN_MULT ||
           parser->current_token.type == TOKEN_DIV) {

        Token token = parser->current_token;

        if (token.type == TOKEN_MULT)
            parser_expect(parser, TOKEN_MULT);
        else
            parser_expect(parser, TOKEN_DIV);

        ASTNode *right = parse_factor(parser);

        ASTNode *new_node = create_node(AST_BINOP, token.value);
        new_node->left = node;
        new_node->right = right;

        node = new_node;
    }

    return node;
}

// Parse expression (addition and subtraction)
// handles + and -
ASTNode* parse_expression(Parser *parser) {

    // calls parse_term first to respect operator precedence
    // * and / → higher priority
    // + and - → lower priority
    ASTNode *node = parse_term(parser);

    while (parser->current_token.type == TOKEN_PLUS ||
           parser->current_token.type == TOKEN_MINUS) {

        Token token = parser->current_token;

        if (token.type == TOKEN_PLUS)
            parser_expect(parser, TOKEN_PLUS);
        else
            parser_expect(parser, TOKEN_MINUS);

        ASTNode *right = parse_term(parser);

        ASTNode *new_node = create_node(AST_BINOP, token.value);
        new_node->left = node;
        new_node->right = right;

        node = new_node;
    }

    return node;
}

// Parse statement
// supports:
// let x = expression
// print expression
ASTNode* parse_statement(Parser *parser) {

    // case 1: let x = ...
    if (parser->current_token.type == TOKEN_LET) {

        parser_expect(parser, TOKEN_LET);

        Token var = parser->current_token;
        parser_expect(parser, TOKEN_IDENTIFIER);

        parser_expect(parser, TOKEN_EQUALS);

        ASTNode *expr = parse_expression(parser);

        ASTNode *node = create_node(AST_ASSIGN, "=");
        node->left = create_node(AST_IDENTIFIER, var.value);
        node->right = expr;

        return node;
    }

    // case 2: print ...
    if (parser->current_token.type == TOKEN_PRINT) {

        parser_expect(parser, TOKEN_PRINT);

        ASTNode *expr = parse_expression(parser);

        ASTNode *node = create_node(AST_PRINT, "print");
        node->left = expr;

        return node;
    }

    printf("Invalid statement\n");
    exit(1);
}

// Multiple lines (program entry)
ASTNode* parse_program(Parser *parser) {

    ASTNode *root = NULL;
    ASTNode *current = NULL;

    while (parser->current_token.type != TOKEN_EOF) {

        ASTNode *stmt = parse_statement(parser);

        if (root == NULL) {
            root = stmt;
            current = stmt;
        } else {
            // chain statements (simple linked structure)
            current->right = stmt;
            current = stmt;
        }
    }

    return root;
}
// Entry point of parser
ASTNode* parse(Parser *parser) {
    return parse_program(parser);
}