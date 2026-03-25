#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
// Get the value of a variable(Find the variable in memory)
int get_variable(Context *ctx, char *name) {

    for (int i = 0; i < ctx->count; i++) {
        if (strcmp(ctx->names[i], name) == 0) {
            return ctx->values[i];
        }
    }

    printf("Undefined variable: %s\n", name);
    exit(1);
}

//Set the value of a variable(Store the variable in memory)
void set_variable(Context *ctx, char *name, int value) {

    for (int i = 0; i < ctx->count; i++) {
        if (strcmp(ctx->names[i], name) == 0) {
            ctx->values[i] = value;
            return;
        }
    }

    // new variable
    strcpy(ctx->names[ctx->count], name);
    ctx->values[ctx->count] = value;
    ctx->count++;
}

//evaluate an expression and return its value
int eval(ASTNode *node, Context *ctx) {

    // number
    if (node->type == AST_NUMBER) {
        return atoi(node->value);
    }

    // variable
    if (node->type == AST_IDENTIFIER) {
        return get_variable(ctx, node->value);
    }

    // binary operation
    if (node->type == AST_BINOP) {

        int left = eval(node->left, ctx);
        int right = eval(node->right, ctx);

        if (strcmp(node->value, "+") == 0)
            return left + right;

        if (strcmp(node->value, "-") == 0)
            return left - right;

        if (strcmp(node->value, "*") == 0)
            return left * right;

        if (strcmp(node->value, "/") == 0)
            return left / right;
    }

    printf("Invalid expression\n");
    exit(1);
}

//execute statemnets 
void execute(ASTNode *node, Context *ctx) {

    if (node == NULL) return;

    // assignment
    if (node->type == AST_ASSIGN) {

        char *var_name = node->left->value;
        int value = eval(node->right, ctx);

        set_variable(ctx, var_name, value);
    }

    // print
    else if (node->type == AST_PRINT) {

        int value = eval(node->left, ctx);
        printf("%d\n", value);
    }

    // move to next statement 
    execute(node->next, ctx);
}
