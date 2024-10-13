#include "parseur.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Crée un nœud de type nombre.
 * @param value La valeur du nombre
 * @return Un pointeur vers le nœud AST créé
 */
ASTNode* create_number_node(double value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));  // Allouer de la mémoire pour le nœud AST de la taille de la structure ASTNode
    if (!node) {
        printf("Erreur: Impossible d'allouer de la mémoire pour le nœud AST\n");
        exit(1);
    }
    node->type = NODE_NUMBER;  // Initialiser le type du nœud
    node->value = value;  // Initialiser la valeur du nombre
    return node;
}

/**
 * Crée un nœud de type opérateur.
 * @param operator L'opérateur
 * @param left Le sous-arbre gauche
 * @param right Le sous-arbre droit
 * @return Un pointeur vers le nœud AST créé
 */
ASTNode* create_operator_node(char operator, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));  // Allouer de la mémoire pour le nœud AST de la taille de la structure ASTNode
    if (!node) {
        printf("Erreur: Impossible d'allouer de la mémoire pour le nœud AST\n");
        exit(1);
    }
    node->type = NODE_OPERATOR;  // Initialiser le type du nœud
    node->op.operator = operator;  // Initialiser l'opérateur
    node->op.left = left;  // Initialiser le sous-arbre gauche
    node->op.right = right;  // Initialiser le sous-arbre droit
    return node;
}

/**
 * Analyse les tokens pour créer un AST.
 * @param tokens Un tableau de tokens
 * @param num_tokens Le nombre de tokens
 * @return Un pointeur vers la racine de l'AST
 */
ASTNode* parse_tokens(Token* tokens, int num_tokens) {
    if (num_tokens < 3) {
        printf("Erreur: Expression invalide, trop peu de tokens.\n");
        exit(1);
    }

    // On s'attend à une structure de type: Nombre - Opérateur - Nombre
    // Dans le cadre de ce TP, on ne gère pas les expressions plus complexes (par exemple, 1 + 2 * 3)
    Token number1 = tokens[0];
    Token operator = tokens[1];
    Token number2 = tokens[2];

    if (number1.type != TOKEN_NUMBER || number2.type != TOKEN_NUMBER || operator.type != TOKEN_OPERATOR) {
        printf("Erreur: Syntaxe invalide.\n");
        exit(1);
    }

    // Convertir les valeurs des tokens de type nombre en double
    double value1 = atof(number1.value);  // `atof` convertit une chaîne de caractères en double
    double value2 = atof(number2.value);

    // Créer les nœuds correspondants
    ASTNode* left_node = create_number_node(value1);
    ASTNode* right_node = create_number_node(value2);
    ASTNode* root = create_operator_node(operator.value[0], left_node, right_node);

    return root;
}

/**
 * Libère la mémoire utilisée par l'AST.
 * @param node Le nœud à libérer
 */
void free_ast(ASTNode* node) {
    if (node == NULL) {
        return;
    }

    if (node->type == NODE_OPERATOR) {
        free_ast(node->op.left);
        free_ast(node->op.right);
    }

    free(node);
}
