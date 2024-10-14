#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "lexer.h"
#include "parseur.h"
#include "evaluation.h"

/**
 * Programme qui simule un interpréteur de commandes simple.
 */

// Définition de la structure pour les commandes
typedef struct {
    char* commande_en;  // Commande en anglais
    char* commande_fr;  // Commande en français
    void (*fonction)(char*, char*);  // Pointeur vers la fonction associée à la commande
    char* description_en;  // Description de la commande en anglais
    char* description_fr;  // Description de la commande en français
} Commande;

// Prototypes des fonctions
void afficher_message(char* en, char* fr, char* lang);
void afficher_version(char* unused, char* lang);
void afficher_aide(Commande commandes[], int nombre_commandes, char* lang);
void traiter_echo(char* commande, char* lang);
void traiter_quit(char* unused, char* lang);
void afficher_date(char* unused, char* lang);
void traiter_expression(char* commande, char* lang);

// Fonctions utilitaires

/**
 * Affiche un message en fonction de la langue choisie.
 * @param en Message en anglais
 * @param fr Message en français
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void afficher_message(char* en, char* fr, char* lang) {
    printf("%s\n", (strcmp(lang, "fr") == 0) ? fr : en);
}

/**
 * Affiche le résultat en format approprié (entier ou réel).
 * @param result Le résultat à afficher
 */
void print_result(double result) {
    if (result == (int)result) {
        printf("%d\n", (int)result);
    } else {
        printf("%.6g\n", result); // .6g permet de supprimer les zéros inutiles
    }
}


/**
 * Affiche la version du compilateur.
 * @param unused Paramètre inutilisé
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void afficher_version(char* unused, char* lang) {
    afficher_message("Compiler version", "Version du compilateur", lang);
    printf(" %s\n", __VERSION__);
}

/**
 * Affiche la liste des commandes disponibles.
 * @param commandes Tableau des commandes disponibles
 * @param nombre_commandes Nombre de commandes dans le tableau
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void afficher_aide(Commande commandes[], int nombre_commandes, char* lang) {
    afficher_message("List of available commands (including arithmetic calculations):", "Liste des commandes disponibles (y compris les calculs arithmétiques):", lang);
    for (int i = 0; i < nombre_commandes; i++) {
        printf("  %s: %s\n",
               (strcmp(lang, "fr") == 0) ? commandes[i].commande_fr : commandes[i].commande_en,
               (strcmp(lang, "fr") == 0) ? commandes[i].description_fr : commandes[i].description_en);
    }
    afficher_message("You can also enter arithmetic expressions like '2 + 3' or '1.5 * 4'.", "Vous pouvez également entrer des expressions arithmétiques comme '2 + 3' ou '1.5 * 4'.", lang);
}

/**
 * Traite la commande "echo" ou "afficher".
 * Affiche le texte qui suit la commande.
 * @param commande La commande entrée par l'utilisateur
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void traiter_echo(char* commande, char* lang) {
    char* texte = strchr(commande, ' ');  // Cherche le premier espace pour trouver le texte à afficher
    if (texte) {
        texte++; // Passer l'espace
        afficher_message("Echo:", "Afficher:", lang);
        printf(" %s\n", texte);
    } else {
        afficher_message("Invalid command.", "Commande invalide.", lang);
    }
}

/**
 * Traite la commande "quit" ou "quitter".
 * Arrête le programme.
 * @param unused Paramètre inutilisé
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void traiter_quit(char* unused, char* lang) {
    afficher_message("Exiting...", "Arrêt...", lang);
    exit(0);
}

/**
 * Affiche la date actuelle.
 * @param unused Paramètre inutilisé
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void afficher_date(char* unused, char* lang) {
    afficher_message("Date:", "Date:", lang);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("%02d-%02d-%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/**
 * Convertit une chaîne de caractères en minuscules.
 * @param str La chaîne de caractères à convertir
 */
void convertir_en_minuscules(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

/**
 * Traite une commande de calcul mathématique.
 * @param commande La commande entrée par l'utilisateur
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void traiter_expression(char* commande, char* lang) {
    // Tokenize l'expression mathématique
    int token_count = 0; // Nombre de tokens
    Token *tokens = tokenize(commande, &token_count);
    /*
    *  ici je passe l'adresse de token_count pour que la fonction tokenize puisse modifier sa valeur
    *  (passage par référence) car en C on ne peut pas retourner plusieurs valeurs dans une fonction.
    */

    // Parse les tokens pour créer un AST
    // ASTNode* ast = parse_tokens(tokens, token_count);

    // Parse les tokens pour créer une expression en notation postfixe
    Token postfix_tokens[64];
    int postfix_count = parse_stack(tokens, token_count, postfix_tokens);

    // Evaluer l'expression AST
    // double result = evaluate_expression(ast);

    // Evaluer l'expression en notation postfixe
    double result = evaluate_postfix(postfix_tokens, token_count);

    // Affiche le résultat
    afficher_message("Result:", "Résultat:", lang);
    print_result(result);

    // Libère la mémoire allouée (mémoire allouée pour les tokens dans `tokenize` et pour l'AST dans `parse_tokens`)
    free(tokens);
    // free_ast(ast);
}


/**
 * Traite une commande entrée par l'utilisateur.
 * @param commande La commande entrée par l'utilisateur
 * @param commandes Tableau des commandes disponibles
 * @param nombre_commandes Nombre de commandes dans le tableau
 */
void traiter_commande(char* commande, Commande commandes[], int nombre_commandes) {
    char commande_originale[1024];
    strcpy(commande_originale, commande);  // Sauvegarde la commande originale pour les messages d'erreur
    convertir_en_minuscules(commande);  // Convertit la commande en minuscules

    for (int i = 0; i < nombre_commandes; i++) {
        // Vérifie si la commande entrée correspond à une commande en anglais ou en français
        if (strncmp(commande, commandes[i].commande_en, strlen(commandes[i].commande_en)) == 0 ||
            strncmp(commande, commandes[i].commande_fr, strlen(commandes[i].commande_fr)) == 0) {
            // Détermine la langue de la commande
            char* lang = (strncmp(commande, commandes[i].commande_fr, strlen(commandes[i].commande_fr)) == 0) ? "fr" : "en";
            // Exécute la fonction associée à la commande
            if (commandes[i].fonction == (void (*)(char*, char*))afficher_aide) {
                afficher_aide(commandes, nombre_commandes, lang);
            } else {
                commandes[i].fonction(commande, lang);
            }
            return;
        }
    }

    // Si la commande commence par un chiffre, essayer de l'évaluer comme une expression
    if (isdigit(commande[0]) || commande[0] == '(') {
        traiter_expression(commande, "en");
        return;
    }

    // Si la commande n'est pas reconnue, affiche un message d'erreur
    printf("Commande inconnue: '%s'. Assurez-vous de taper la commande en minuscules.\n", commande_originale);
}

int main() {
    // Initialisation des commandes disponibles
    Commande commandes[] = {
        {"quit", "quitter", traiter_quit, "Quit the program", "Quitter le programme"},
        {"echo", "afficher", traiter_echo, "Echo the text", "Afficher le texte"},
        {"date", "date", afficher_date, "Display the current date", "Afficher la date actuelle"},
        {"version", "version", afficher_version, "Display the compiler version", "Afficher la version du compilateur"},
        {"help", "aide", (void (*)(char*, char*))afficher_aide, "Show help", "Afficher l'aide"},
    };
    int nombre_commandes = sizeof(commandes) / sizeof(Commande);

    // Boucle principale pour lire et traiter les commandes utilisateur
    while (1) {
        printf("> ");  // Affiche le prompt de commande
        char commande[1024];
        if (!fgets(commande, sizeof(commande), stdin)) {  // Lit la commande utilisateur
            break;  // Arrête le programme en cas d'erreur de lecture
        }
        commande[strcspn(commande, "\n")] = 0;  // Supprime le caractère de fin de ligne
        if (strlen(commande) > 0) {  // Ignore les commandes vides
            traiter_commande(commande, commandes, nombre_commandes);
        }
        printf("\n");  // Saut de ligne après chaque commande
    }
    return 0;
}