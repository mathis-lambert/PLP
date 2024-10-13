#include "evaluation.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Fonction récursive pour évaluer un AST.
 * @param root Le nœud racine de l'AST
 * @return Le résultat de l'évaluation
 */
double evaluate_expression(ASTNode* root) {
    if (root == NULL) {
        printf("Erreur: Expression invalide.\n");
        exit(1);
    }

    // Si le nœud est de type nombre, retourner la valeur directement
    if (root->type == NODE_NUMBER) { // `->` est une notation pour accéder à un membre d'une structure à travers un pointeur
        return root->value; // `root->value` est équivalent à `(*root).value`
    }

    // Si le nœud est de type opérateur, évaluer récursivement les sous-arbres gauche et droit
    if (root->type == NODE_OPERATOR) {
        double left_value = evaluate_expression(root->op.left);
        double right_value = evaluate_expression(root->op.right);
        char operator = root->op.operator;

        switch (operator) {
        case '+':
            return left_value + right_value;
        case '-':
            return left_value - right_value;
        case '*':
            return left_value * right_value;
        case '/':
            if (right_value == 0) {
                printf("Erreur: Division par zéro.\n");
                exit(1);
            }
            return left_value / right_value;
        default:
            printf("Erreur: Opérateur inconnu '%c'.\n", operator);
            exit(1);
        }
    }

    // Si on atteint ce point, il y a une erreur dans l'AST. En théorie, ca ne devrait jamais arriver.
    printf("Erreur: Nœud AST invalide.\n");
    exit(1);
}