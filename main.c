#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main() {
    char source[] = "let x = 5 + 3 - 2 * 4 / 2\nprint x";

    Lexer lexer;
    lexer_init(&lexer, source);

    Token token;

    //  Print tokens
    do {
        token = lexer_next_token(&lexer);
        printf("Token Type: %-10d Value: %s\n", token.type, token.value);
    } while (token.type != TOKEN_EOF);

    // Reset lexer
    lexer_init(&lexer, source);

    //  Parse
    Parser parser;
    parser_init(&parser, &lexer);

    ASTNode *tree = parse(&parser);

    printf("Parsed successfully!\n");

    //  Execute
    Context ctx;
    ctx.count = 0;

    execute(tree, &ctx);

    return 0;
}