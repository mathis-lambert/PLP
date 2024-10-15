#include "evaluation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DEBUG_MODE 0 // Activer/désactiver le mode debug

// Fonction utilitaire pour obtenir la valeur d'un opérande sous forme de double
double get_value(const char *value_str)
{
    if (DEBUG_MODE)
    {
        printf("[DEBUG] get_value: Conversion de '%s' en double\n", value_str);
    }
    return atof(value_str); // Convertit la chaîne de caractères en double
}

// Fonction utilitaire pour appliquer un opérateur aux deux opérandes
double apply_operator(char operator, double left, double right)
{
    if (DEBUG_MODE)
    {
        printf("[DEBUG] apply_operator: Application de l'opérateur '%c' sur %.2f et %.2f\n", operator, left, right);
    }
    switch (operator)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        if (right == 0)
        {
            fprintf(stderr, "Erreur: Division par zéro\n");
            exit(EXIT_FAILURE);
        }
        return left / right;
    default:
        fprintf(stderr, "Erreur: Opérateur inconnu '%c'\n", operator);
        exit(EXIT_FAILURE);
    }
}

// Fonction pour substituer les variables dans une expression
void substitute_variable(Token *tokens, int token_count, const char *variable, const char *value)
{
    if (DEBUG_MODE)
    {
        printf("[DEBUG] substitute_variable: Substitution de la variable '%s' avec la valeur '%s'\n", variable, value);
    }
    for (int i = 0; i < token_count; i++)
    {
        if (tokens[i].type == TOKEN_IDENTIFIER && strcmp(tokens[i].value, variable) == 0)
        {
            tokens[i].type = TOKEN_NUMBER;
            strcpy(tokens[i].value, value);
            if (DEBUG_MODE)
            {
                printf("[DEBUG] substitute_variable: Token %d remplacé par la valeur '%s'\n", i, value);
            }
        }
    }
}

// Fonction pour évaluer une expression en notation postfixe (Reverse Polish Notation)
double evaluate_postfix(Token *tokens, int token_count)
{
    OperandStack *operand_stack = create_operand_stack(token_count);

    for (int i = 0; i < token_count; i++)
    { // Parcourir tous les tokens
        Token token = tokens[i];

        if (token.value[0] == '\0')
        { // Fin de la chaîne
            break;
        }

        if (DEBUG_MODE)
        {
            printf("[DEBUG] evaluate_postfix: Traitement du token %d de type %d avec valeur '%s'\n", i, token.type, token.value);
        }

        if (token.type == TOKEN_NUMBER)
        {
            push_operand(operand_stack, token); // Empiler les nombres sur la pile
            if (DEBUG_MODE)
            {
                printf("[DEBUG] evaluate_postfix: Nombre '%s' empilé\n", token.value);
            }
        }
        else if (token.type == TOKEN_OPERATOR)
        {
            if (is_operand_stack_empty(operand_stack) || operand_stack->top < 1)
            { // Vérifier s'il y a assez d'opérandes
                fprintf(stderr, "Erreur: Pas assez d'opérandes pour l'opération\n");
                free_operand_stack(operand_stack);
                exit(EXIT_FAILURE);
            }

            // Dépiler les deux opérandes nécessaires pour l'opération
            Token right_operand = pop_operand(operand_stack);
            Token left_operand = pop_operand(operand_stack);

            if (DEBUG_MODE)
            {
                printf("[DEBUG] evaluate_postfix: Opérandes dépilées - gauche: '%s', droite: '%s'\n", left_operand.value, right_operand.value);
            }

            // Convertir les valeurs des opérandes
            double left_value = get_value(left_operand.value);
            double right_value = get_value(right_operand.value);

            // Appliquer l'opération
            double result = apply_operator(token.value[0], left_value, right_value);

            // Empiler le résultat sous forme de token
            Token result_token;
            result_token.type = TOKEN_NUMBER;
            snprintf(result_token.value, sizeof(result_token.value), "%.2f", result);
            push_operand(operand_stack, result_token); // Empiler le résultat sur la pile

            if (DEBUG_MODE)
            {
                printf("[DEBUG] evaluate_postfix: Résultat de l'opération '%.2f' empilé\n", result);
            }
        }
    }

    // Le résultat final doit être sur la pile d'opérandes
    if (operand_stack->top == 0)
    {
        Token result_token = pop_operand(operand_stack);
        double result = get_value(result_token.value);
        free_operand_stack(operand_stack);
        if (DEBUG_MODE)
        {
            printf("[DEBUG] evaluate_postfix: Résultat final de l'expression: %.2f\n", result);
        }
        return result;
    }
    else
    {
        fprintf(stderr, "Erreur: Expression invalide\n");
        free_operand_stack(operand_stack);
        exit(EXIT_FAILURE);
    }
}

// Fonction pour évaluer une expression lambda
double evaluate_lambda(Token *tokens, int token_count, const char *variable, const char *value)
{
    if (DEBUG_MODE)
    {
        printf("[DEBUG] evaluate_lambda: Évaluation de l'expression lambda avec la variable '%s' et la valeur '%s'\n", variable, value);
    }

    // Substituer la variable dans l'expression
    substitute_variable(tokens, token_count, variable, value);

    // Parse l'expression en notation postfixe
    Token postfix_tokens[64];
    int postfix_count = parse_stack(tokens, token_count, postfix_tokens);

    if (DEBUG_MODE)
    {
        printf("[DEBUG] evaluate_lambda: Expression convertie en notation postfixe\n");
    }

    // Évaluer l'expression postfixée
    return evaluate_postfix(postfix_tokens, postfix_count);
}