#include "parseur.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DEBUG_MODE 1 // Activer/désactiver le mode debug

// Crée une pile pour les opérandes
OperandStack* create_operand_stack(int capacity) {
    OperandStack* stack = (OperandStack*)malloc(sizeof(OperandStack));  // Allouer de la mémoire pour la pile

    if (!stack) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire pour la pile d'opérandes\n");
        exit(EXIT_FAILURE);
    }

    stack->data = (Token*)malloc(capacity * sizeof(Token));  // Allouer de la mémoire pour le tableau de données

    if (!stack->data) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire pour le tableau de données de la pile d'opérandes\n");
        exit(EXIT_FAILURE);
    }

    stack->top = -1;  // Initialiser le sommet de la pile
    stack->capacity = capacity;  // Initialiser la capacité de la pile

    if (DEBUG_MODE) {
        printf("Pile d'opérandes créée avec une capacité de %d\n", capacity);
    }

    return stack;
}

// Empile un opérande sur la pile
void push_operand(OperandStack* stack, Token operand) {

    if (stack->top == stack->capacity - 1) {
        fprintf(stderr, "Erreur: Dépassement de capacité de la pile d'opérandes\n");
        exit(EXIT_FAILURE);
    }

    stack->data[++stack->top] = operand;  // Empiler l'opérande

    if (DEBUG_MODE) {
        printf("Opérande empilée: %s\n", operand.value);
    }
}

// Dépile un opérande de la pile
Token pop_operand(OperandStack* stack) {

    if (stack->top == -1) {
        fprintf(stderr, "Erreur: Tentative de dépiler une pile d'opérandes vide\n");
        exit(EXIT_FAILURE);
    }

    Token operand = stack->data[stack->top--];  // Dépiler l'opérande

    if (DEBUG_MODE) {
        printf("Opérande dépilée: %s\n", operand.value);
    }

    return operand;
}

// Retourne l'opérande au sommet de la pile sans le dépiler
Token peek_operand(OperandStack* stack) {

    if (stack->top == -1) {
        fprintf(stderr, "Erreur: Tentative de consulter une pile d'opérandes vide\n");
        exit(EXIT_FAILURE);
    }

    if (DEBUG_MODE) {
        printf("Opérande au sommet de la pile: %s\n", stack->data[stack->top].value);
    }

    return stack->data[stack->top];  // Retourner l'opérande au sommet de la pile
}

// Vérifie si la pile d'opérandes est vide
int is_operand_stack_empty(OperandStack* stack) {
    return stack->top == -1;  // Retourner vrai si la pile est vide
}

// Libère la mémoire allouée pour la pile d'opérandes
void free_operand_stack(OperandStack* stack) {
    free(stack->data);
    free(stack);
}

// Crée une pile pour les opérateurs
OperatorStack* create_operator_stack(int capacity) {
    OperatorStack* stack = (OperatorStack*)malloc(sizeof(OperatorStack));
    if (!stack) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire pour la pile d'opérateurs\n");
        exit(EXIT_FAILURE);
    }
    stack->data = (Token*)malloc(capacity * sizeof(Token));
    if (!stack->data) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire pour le tableau de données de la pile d'opérateurs\n");
        exit(EXIT_FAILURE);
    }
    stack->top = -1;
    stack->capacity = capacity;

    if (DEBUG_MODE) {
        printf("Pile d'opérateurs créée avec une capacité de %d\n", capacity);
    }

    return stack;
}

// Empile un opérateur sur la pile
void push_operator(OperatorStack* stack, Token operator) {
    if (stack->top == stack->capacity - 1) {
        fprintf(stderr, "Erreur: Dépassement de capacité de la pile d'opérateurs\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++stack->top] = operator;

    if (DEBUG_MODE) {
        printf("Opérateur empilé: %s\n", operator.value);
    }
}

// Dépile un opérateur de la pile
Token pop_operator(OperatorStack* stack) {
    if (stack->top == -1) {
        fprintf(stderr, "Erreur: Tentative de dépiler une pile d'opérateurs vide\n");
        exit(EXIT_FAILURE);
    }
    Token operator = stack->data[stack->top--];

    if (DEBUG_MODE) {
        printf("Opérateur dépilé: %s\n", operator.value);
    }

    return operator;
}

// Retourne l'opérateur au sommet de la pile sans le dépiler
Token peek_operator(OperatorStack* stack) {
    if (stack->top == -1) {
        fprintf(stderr, "Erreur: Tentative de consulter une pile d'opérateurs vide\n");
        exit(EXIT_FAILURE);
    }

    if (DEBUG_MODE) {
        printf("Opérateur au sommet de la pile: %s\n", stack->data[stack->top].value);
    }

    return stack->data[stack->top];
}

// Vérifie si la pile d'opérateurs est vide
int is_operator_stack_empty(OperatorStack* stack) {
    return stack->top == -1;
}

// Libère la mémoire allouée pour la pile d'opérateurs
void free_operator_stack(OperatorStack* stack) {
    free(stack->data);
    free(stack);
}

// Fonction pour convertir une expression en notation postfixe (Reverse Polish Notation)
int parse_stack(Token* tokens, int token_count, Token* output) {
    OperatorStack* operator_stack = create_operator_stack(token_count);
    int output_index = 0;

    for (int i = 0; i < token_count; i++) {
        Token token = tokens[i];

        if (token.type == TOKEN_NUMBER) {
            output[output_index++] = token;
            if (DEBUG_MODE) {
                printf("[DEBUG] Ajouté au résultat: %s\n", token.value);
            }
        } else if (token.type == TOKEN_OPERATOR) {
            while (!is_operator_stack_empty(operator_stack) &&
                   precedence(peek_operator(operator_stack).value[0]) >= precedence(token.value[0])) {
                output[output_index++] = pop_operator(operator_stack);
                   }
            push_operator(operator_stack, token);
        } else if (token.type == TOKEN_PARENTHESIS) {
            if (token.value[0] == '(') {
                push_operator(operator_stack, token);
            } else if (token.value[0] == ')') {
                while (!is_operator_stack_empty(operator_stack) && peek_operator(operator_stack).value[0] != '(') {
                    output[output_index++] = pop_operator(operator_stack);
                }
                if (!is_operator_stack_empty(operator_stack) && peek_operator(operator_stack).value[0] != '(') {
                    fprintf(stderr, "Erreur: Parenthèses non équilibrées\n");
                    exit(EXIT_FAILURE);
                } else {
                    pop_operator(operator_stack);
                }
            }
        }
    }

    while (!is_operator_stack_empty(operator_stack)) {
        output[output_index++] = pop_operator(operator_stack);
    }

    if (DEBUG_MODE) {
        printf("[DEBUG] Expression en notation postfixe: ");
        for (int i = 0; i < output_index; i++) {
            printf("%s ", output[i].value);
        }
        printf("\n");
    }

    // Libérer la mémoire allouée
    free_operator_stack(operator_stack);

    if (DEBUG_MODE) {
        printf("Tokens (POSTFIX) : ");
        for (int i = 0; i < output_index; i++) {
            printf("%s ", output[i].value);
        }
        printf("\n");
    }

    return output_index;
}

// Fonction pour vérifier la précédence des opérateurs
int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}