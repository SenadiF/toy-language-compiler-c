#ifndef AST_H
#define AST_H

//Types of AST nodes 
typedef enum{
    AST_NUMBER,  //a number 
    AST_IDENTIFIER, // variable
    AST_BINOP,  //operation with two operands
    AST_ASSIGN, //assignment operation
    AST_PRINT  // print statement
}ASTNodeType;

//AST node structure 
typedef struct ASTNode {
    ASTNodeType type;

    // value (for numbers or identifiers)
    char value[64];

    // left and right children (for tree)
    struct ASTNode *left;
    struct ASTNode *right;
    //statements 
    struct ASTNode *next; // for linking statements in a sequence
} ASTNode;

#endif 