#include "lexer.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Fonction pour ignorer les espaces
void skip_whitespace(const char** input) {
    while (isspace(**input)) {
        (*input)++;
    }
}

// Fonction pour extraire un nombre
Token get_number(const char** input) {
    Token token;
    token.type = TOKEN_NUMBER;
    int index = 0;

    while (isdigit(**input) || **input == '.') {
        token.value[index++] = **input;
        (*input)++;
    }
    token.value[index] = '\0';
    return token;
}

// Fonction pour extraire une parenthèse
Token get_parenthesis(const char** input) {
    Token token;
    token.type = TOKEN_PARENTHESIS;
    token.value[0] = **input;
    token.value[1] = '\0';
    (*input)++;
    return token;
}

// Fonction pour extraire un opérateur
Token get_operator(const char** input) {
    Token token;
    token.type = TOKEN_OPERATOR;
    token.value[0] = **input;
    token.value[1] = '\0';
    (*input)++;
    return token;
}

// Fonction principale pour tokeniser l'entrée
int tokenize(const char* input, Token* output) {
    const char* current = input;
    int token_count = 0;


    while (*current != '\0') {
        skip_whitespace(&current);

        if (isdigit(*current) || *current == '.') {
            // Tokeniser un nombre
            output[(token_count)++] = get_number(&current);
        } else if (*current == '+' || *current == '-' || *current == '*' || *current == '/') {
            // Tokeniser un opérateur
            output[(token_count)++] = get_operator(&current);
        } else if (*current == '(' || *current == ')') {
            // Tokeniser une parenthèse
            output[(token_count)++] = get_parenthesis(&current);
        } else if (*current == '\0') {
            break; // Fin de la chaîne
        } else {
            // Gérer les erreurs de syntaxe
            printf("Unknown token: %c\n", *current);
            current++;
        }
    }

    // Ajouter un token de fin de fichier (EOF)
    Token eof_token;
    eof_token.type = TOKEN_EOF;
    strcpy(eof_token.value, "EOF");
    output[token_count++] = eof_token;

    // Retourner le nombre de tokens
    return token_count;
}
