#ifndef EVALUATION_H
#define EVALUATION_H

#include "parseur.h"

// Fonction utilitaire pour obtenir la valeur d'un opérande sous forme de double
double get_value(const char* value_str);

// Fonction utilitaire pour appliquer un opérateur aux deux opérandes
double apply_operator(char operator, double left, double right);

// Fonction pour évaluer une expression en notation postfixe (Reverse Polish Notation)
double evaluate_postfix(Token* tokens, int token_count);

// Fonction pour substituer les variables dans une expression
void substitute_variable(Token* tokens, int token_count, const char* variable, const char* value);

// Vérifie si la pile d'opérandes est vide
int is_operand_stack_empty(OperandStack* stack);

// Evaluer une expression lambda
double evaluate_lambda(Token* tokens, int token_count, const char* variable, const char* value);

#endif // EVALUATION_H