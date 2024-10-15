#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_PARENTHESIS,
    TOKEN_LAMBDA,        // Pour le mot-clé "lambda"
    TOKEN_IDENTIFIER,    // Pour la variable (par exemple, "x")
    TOKEN_UNKNOWN,
    TOKEN_EOF
} TokenType;


typedef struct {
    TokenType type;
    char value[64];
} Token;

void skip_whitespace(const char** input);  // Fonction pour ignorer les espaces
Token get_number(const char** input);  // Fonction pour extraire un nombre
Token get_parenthesis(const char** input);  // Fonction pour extraire une parenthèse
Token get_lambda(const char** input);  // Fonction pour extraire le mot-clé "lambda"
Token get_identifier(const char** input);  // Fonction pour extraire une variable
Token get_operator(const char** input);  // Fonction pour extraire un opérateur

int tokenize(const char* input, Token* output);  // Fonction principale pour tokeniser l'entrée

#endif // LEXER_H
