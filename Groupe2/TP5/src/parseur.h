#ifndef PARSEUR_STACK_H
#define PARSEUR_STACK_H

#include "lexer.h"

// Contrairement à parseur.h qui utilise des arbres AST, parseur_stack.h utilise une pile pour transformer les expressions en notation postfixe (RPN).
// C'est une approche différente qui permet d'éviter la récursion et de gérer les expressions plus complexes.

// ------ FONCTIONNEMENT DE LA PILE ------
// La pile est une structure de données qui fonctionne selon le principe LIFO (Last In, First Out).
// Cela signifie que le dernier élément ajouté à la pile est le premier élément à être retiré.
// Dans le cadre de la conversion d'expressions, on peut utiliser une pile pour stocker les opérateurs et appliquer la priorité des opérateurs.

// Définition de la structure OperandStack
typedef struct {
    Token* data;    // Tableau dynamique de tokens
    int top;        // Indice du sommet de la pile
    int capacity;   // Capacité maximale de la pile
} OperandStack;

// Définition de la structure OperatorStack
typedef struct {
    Token* data;    // Tableau dynamique de tokens
    int top;        // Indice du sommet de la pile
    int capacity;   // Capacité maximale de la pile
} OperatorStack;

// Définition de la structure LambdaExpression
typedef struct {
    char variable_name[64];
    Token* expression_tokens;
    int expression_token_count;
} LambdaExpression;

// Fonctions pour la pile d'opérandes
OperandStack* create_operand_stack(int capacity);
void push_operand(OperandStack* stack, Token operand);
Token pop_operand(OperandStack* stack);
Token peek_operand(OperandStack* stack);
int is_operand_stack_empty(OperandStack* stack);
void free_operand_stack(OperandStack* stack);

// Fonctions pour la pile d'opérateurs
OperatorStack* create_operator_stack(int capacity);
void push_operator(OperatorStack* stack, Token operator);
Token pop_operator(OperatorStack* stack);
Token peek_operator(OperatorStack* stack);
int is_operator_stack_empty(OperatorStack* stack);
void free_operator_stack(OperatorStack* stack);

// Fonction de parsing pour convertir une expression en notation postfixe
int parse_stack(Token* tokens, int token_count, Token* output);

// parser les expressions lambda
int parse_lambda_expression(Token* tokens, int token_count, LambdaExpression* lambda);

// Fonction pour vérifier la précédence des opérateurs
int precedence(char operator);

#endif // PARSEUR_STACK_H