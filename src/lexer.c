#include <stdio.h>
#include <ctype.h> // for isdigit() and isalpha()
#include <string.h> // for strcmp()
#include "lexer.h"

//Intialize the lexer 
void lexer_init(Lexer *lexer, char *source) {
    lexer->source = source; //store pointer to the source code 
    lexer->position = 0; // start at the first character 
    lexer->current_char = source[0]; // Store the first character
}

//Move to the next character 
void lexer_advance(Lexer *lexer) {
    lexer->position++; // Move one step forward
    if (lexer->source[lexer->position] != '\0') { // Check if we haven't reached the end of the source
        lexer->current_char = lexer->source[lexer->position]; // Update current_char
    } else {
        lexer->current_char = '\0'; // End of input
    }       
}

//Skip spaces, tabs , newlines 
void lexer_skip_whitespace(Lexer*lexer){
     while (lexer->current_char == ' ' || lexer->current_char == '\t' || lexer->current_char == '\n') {
        lexer_advance(lexer);     // keep moving until a nonspace
    }
}

//Parse a number 

Token lexer_number(Lexer*lexer){
    Token token;
    token.type = TOKEN_NUMBER; //  mark as number  
    int i = 0; // Index for storing characters in the token value
    
    // Keep reading the digits until it is a non digit 
    while (isdigit(lexer->current_char)) { 
        token.value[i++]=lexer->current_char;//store the current digit
        lexer_advance(lexer);// move to next char 
    }
    token.value[i] = '\0'; //end string 
    return token; 


}

//Parse identifier
Token lexer_identifier(Lexer *lexer) {
    Token token;
    int i = 0;

    // Keep reading letters for variable names
    while (isalpha(lexer->current_char)) {
        token.value[i++] = lexer->current_char;
        lexer_advance(lexer);
    }
    token.value[i] = '\0';         // end string

    // Check if it is a keyword
    if (strcmp(token.value, "let") == 0) token.type = TOKEN_LET;
    else if (strcmp(token.value, "print") == 0) token.type = TOKEN_PRINT;
    else token.type = TOKEN_IDENTIFIER; // otherwise it's a variable

    return token;
}

//Return the next token 
Token lexer_next_token(Lexer *lexer) {
    while (lexer->current_char != '\0') { // loop until end of input

        // Skip whitespace 
        if (lexer->current_char == ' ' || lexer->current_char == '\t' || lexer->current_char == '\n') {
            lexer_skip_whitespace(lexer);
            continue; // go back to check next char
        }

        //  Identifier
        if (isalpha(lexer->current_char)) {
            return lexer_identifier(lexer);
        }

        //  Number 
        if (isdigit(lexer->current_char)) {
            return lexer_number(lexer);
        }

        // Operators
        if (lexer->current_char == '+') {
            Token token = {TOKEN_PLUS, "+"};
            lexer_advance(lexer);
            return token;
        }

        if (lexer->current_char == '-') {
            Token token = {TOKEN_MINUS, "-"};
            lexer_advance(lexer);
            return token;
        }

        if (lexer->current_char == '*') {
            Token token = {TOKEN_MULT, "*"};
            lexer_advance(lexer);
            return token;
        }

        if (lexer->current_char == '/') {
            Token token = {TOKEN_DIV, "/"};
            lexer_advance(lexer);
            return token;
        }

        //  '='
        if (lexer->current_char == '=') {
            Token token = {TOKEN_EQUALS, "="};
            lexer_advance(lexer);
            return token;
        }

        //Unknown character
        printf("Unexpected character: %c\n", lexer->current_char);
        lexer_advance(lexer);
    }

    // End of file 
    Token token = {TOKEN_EOF, ""};
    return token;
}
