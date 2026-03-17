#ifndef LEXER_H
#define LEXER_H

// All token types
typedef enum {
    TOKEN_LET,
    TOKEN_PRINT,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,   
    TOKEN_EQUALS,
    TOKEN_EOF, // End of file/input
} TokenType;

// Token strct ( what each token stores)
typedef struct {
    TokenType type; // Type of token
    char value[64];  //Actual text
    } Token;

//Lexer struct ( what the lexer stores)
typedef struct {
    char *source; // pointer to the source code text 
    int position; //current index in the source string 
    char current_char; // the character at 'position'

} Lexer;

//Functions for the lexer 
void lexer_init(Lexer *lexer, char *source); //Initializes the lexer with the source code
Token lexer_next_token(Lexer *lexer); //get the next token



#endif // LEXER_H