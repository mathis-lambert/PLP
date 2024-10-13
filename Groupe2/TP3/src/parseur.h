#ifndef PARSEUR_H
#define PARSEUR_H

#include "lexer.h"

typedef enum {
    NODE_NUMBER,
    NODE_OPERATOR
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        double value;  // Si le nœud est un nombre
        struct {
            char operator;
            struct ASTNode* left;
            struct ASTNode* right;
        } op;  // Si le nœud est un opérateur
    };
} ASTNode;

ASTNode* parse_tokens(Token* tokens, int num_tokens);
void free_ast(ASTNode* node);

#endif // PARSEUR_H
