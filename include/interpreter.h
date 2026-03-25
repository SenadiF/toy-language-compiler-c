#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"

// simple variable storage
typedef struct {
    char names[100][64];   // variable names
    int values[100];       // their values
    int count;             // number of variables
} Context;

// functions
int eval(ASTNode *node, Context *ctx);
void execute(ASTNode *node, Context *ctx);

#endif