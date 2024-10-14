#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_PARENTHESIS,
    TOKEN_UNKNOWN,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char value[64];
} Token;

void skip_whitespace(const char** input);
Token get_number(const char** input);
Token get_parenthesis(const char** input);
Token get_operator(const char** input);

Token *tokenize(const char* input, int *token_count);

#endif // LEXER_H
