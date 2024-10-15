#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "lexer.h"
#include "parseur.h"
#include "evaluation.h"
#include "variables.h"
#include <regex.h>

/**
 * Programme qui simule un interpréteur de commandes simple.
 */

// Définition de la structure pour les commandes
typedef struct
{
    char *commande_en;                // Commande en anglais
    char *commande_fr;                // Commande en français
    void (*fonction)(char *, char *); // Pointeur vers la fonction associée à la commande
    char *description_en;             // Description de la commande en anglais
    char *description_fr;             // Description de la commande en français
} Commande;

// Prototypes des fonctions
void afficher_message(char *en, char *fr, char *lang);
void afficher_version(char *unused, char *lang);
void afficher_aide(Commande commandes[], int nombre_commandes, char *lang);
void traiter_echo(char *commande, char *lang);
void traiter_quit(char *unused, char *lang);
void afficher_date(char *unused, char *lang);
void traiter_expression(char *commande, char *lang);
void traiter_variable(char *commande, char *lang);

// Fonctions utilitaires

/**
 * Affiche un message en fonction de la langue choisie.
 * @param en Message en anglais
 * @param fr Message en français
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void afficher_message(char *en, char *fr, char *lang)
{
    printf("%s\n", (strcmp(lang, "fr") == 0) ? fr : en);
}

/**
 * Affiche le résultat en format approprié (entier ou réel).
 * @param result Le résultat à afficher
 */
void print_result(double result)
{
    if (result == (int)result)
    {
        printf("%d\n", (int)result);
    }
    else
    {
        printf("%.6g\n", result); // .6g permet de supprimer les zéros inutiles
    }
}

/**
 * Affiche la version du compilateur.
 * @param unused Paramètre inutilisé
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void afficher_version(char *unused, char *lang)
{
    afficher_message("Compiler version", "Version du compilateur", lang);
    printf(" %s\n", __VERSION__);
}

/**
 * Affiche la liste des commandes disponibles.
 * @param commandes Tableau des commandes disponibles
 * @param nombre_commandes Nombre de commandes dans le tableau
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void afficher_aide(Commande commandes[], int nombre_commandes, char *lang)
{
    afficher_message("List of available commands (including arithmetic calculations):", "Liste des commandes disponibles (y compris les calculs arithmétiques):", lang);
    for (int i = 0; i < nombre_commandes; i++)
    {
        printf("  %s: %s\n",
               (strcmp(lang, "fr") == 0) ? commandes[i].commande_fr : commandes[i].commande_en,
               (strcmp(lang, "fr") == 0) ? commandes[i].description_fr : commandes[i].description_en);
    }
    afficher_message("You can also enter complex arithmetic expressions like '2 + 3' or '1.5 * 4'.", "Vous pouvez également entrer des expressions arithmétiques comme '2 + 3' ou '1.5 * 4'.", lang);
}

/**
 * Traite la commande "echo" ou "afficher".
 * Affiche le texte qui suit la commande.
 * @param commande La commande entrée par l'utilisateur
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void traiter_echo(char *commande, char *lang)
{
    char *texte = strchr(commande, ' '); // Cherche le premier espace pour trouver le texte à afficher
    if (texte)
    {
        texte++; // Passer l'espace
        afficher_message("Echo:", "Afficher:", lang);
        printf(" %s\n", texte);
    }
    else
    {
        afficher_message("Invalid command.", "Commande invalide.", lang);
    }
}

/**
 * Traite la commande "quit" ou "quitter".
 * Arrête le programme.
 * @param unused Paramètre inutilisé
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void traiter_quit(char *unused, char *lang)
{
    afficher_message("Exiting...", "Arrêt...", lang);
    exit(0);
}

/**
 * Affiche la date actuelle.
 * @param unused Paramètre inutilisé
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void afficher_date(char *unused, char *lang)
{
    afficher_message("Date:", "Date:", lang);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("%02d-%02d-%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/**
 * Convertit une chaîne de caractères en minuscules.
 * @param str La chaîne de caractères à convertir
 */
void convertir_en_minuscules(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

/**
 * Traite une commande de calcul mathématique.
 * @param commande La commande entrée par l'utilisateur
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void traiter_expression(char *commande, char *lang)
{
    // Tokenize l'expression mathématique
    Token *tokens = (Token *)malloc(64 * sizeof(Token));
    int token_count = tokenize(commande, tokens);

    // Vérifier si c'est une expression lambda
    if (tokens[1].type == TOKEN_LAMBDA)
    {
        // Vérifier la syntaxe et extraire la variable et l'expression
        if (tokens[2].type == TOKEN_IDENTIFIER && tokens[3].value[0] == '.')
        {
            // Extraire la variable et l'expression lambda
            const char *variable = tokens[2].value;

            // Extraire les tokens de l'expression lambda (à partir du 5ème token)
            Token *expression_tokens = &tokens[4];
            int expression_token_count = 0;
            int parenthesis_count = 1;

            // Compter les parenthèses pour identifier la fin de l'expression lambda
            for (int i = 4; i < token_count; i++)
            {
                if (tokens[i].type == TOKEN_PARENTHESIS && tokens[i].value[0] == '(')
                {
                    parenthesis_count++;
                }
                else if (tokens[i].type == TOKEN_PARENTHESIS && tokens[i].value[0] == ')')
                {
                    parenthesis_count--;
                    if (parenthesis_count == 0)
                    {
                        expression_token_count = i - 4;
                        break;
                    }
                }
            }

            if (parenthesis_count != 0)
            {
                afficher_message("Mismatched parentheses in lambda expression.", "Parenthèses non appariées dans l'expression lambda.", lang);
                free(tokens);
                return;
            }

            // Trouver la fin de l'expression lambda pour récupérer l'argument
            int lambda_end_index = 4 + expression_token_count;
            if (lambda_end_index + 1 >= token_count)
            {
                afficher_message("Missing argument for lambda expression.", "Argument manquant pour l'expression lambda.", lang);
                free(tokens);
                return;
            }

            // Extraire l'argument après l'expression lambda (après la parenthèse fermante)
            const char *argument_str = tokens[lambda_end_index + 1].value;

            // Ignorer les espaces
            skip_whitespace(&argument_str);

            // si l'argument existe en tant que variable, on le remplace par sa valeur
            Variable *var = get_variable(argument_str);
            if (var)
            {
                argument_str = get_variable_value(argument_str);
            }
            else if (!isdigit(argument_str[0]) && !var)
            {
                afficher_message("Invalid argument for lambda expression.", "Argument invalide pour l'expression lambda.", lang);
                free(tokens);
                return;
            }

            // Extraire le token de l'argument
            Token argument_token = get_number(&argument_str);

            // afficher les tokens de l'expression lambda
            printf("Lambda expression tokens: ");
            for (int i = 0; i < expression_token_count; i++)
            {
                printf("%s ", expression_tokens[i].value);
            }

            if (argument_token.type == TOKEN_NUMBER)
            {
                // Évaluer l'expression lambda avec l'argument fourni
                double result = evaluate_lambda(expression_tokens, expression_token_count, variable, argument_token.value);
                afficher_message("Result:", "Résultat:", lang);
                print_result(result);
            }
            else
            {
                afficher_message("Invalid argument for lambda expression.", "Argument invalide pour l'expression lambda.", lang);
            }
            free(tokens);
            return;
        }
    }

    // Parse les tokens pour créer une expression en notation postfixe
    Token postfix_tokens[64];
    int postfix_count = parse_stack(tokens, token_count, postfix_tokens);

    // Évaluer l'expression en notation postfixe
    double result = evaluate_postfix(postfix_tokens, postfix_count);

    // Affiche le résultat
    afficher_message("Result:", "Résultat:", lang);
    print_result(result);

    // Libère la mémoire allouée (mémoire allouée pour les tokens dans `tokenize`)
    free(tokens);
}

/**
 * Traite une commande d'affectation de variable.
 * @param commande La commande entrée par l'utilisateur
 * @param lang Langue de la sortie ("en" ou "fr")
 */
void traiter_variable(char *commande, char *lang)
{
    // Déclaration de la regex pour détecter une déclaration de variable
    const char *var_pattern = "^([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*=[[:space:]]*(\"[^\"]*\"|[0-9]+(.[0-9]+)?)";
    regex_t regex;
    int reti;
    regmatch_t matches[4]; // Tableau pour stocker les correspondances

    reti = regcomp(&regex, var_pattern, REG_EXTENDED);
    if (reti)
    {
        fprintf(stderr, "Impossible de compiler la regex\n");
        exit(EXIT_FAILURE);
    }

    // Test de la commande pour voir si elle correspond à une déclaration de variable
    reti = regexec(&regex, commande, 4, matches, 0);
    if (!reti)
    {
        // La commande est une déclaration de variable, extraire le nom et la valeur
        char name[1024];
        char value[1024];

        // Extraire le nom de la variable (correspondance dans matches[1])
        snprintf(name, matches[1].rm_eo - matches[1].rm_so + 1, "%s", commande + matches[1].rm_so);

        // Extraire la valeur de la variable (correspondance dans matches[2])
        snprintf(value, matches[2].rm_eo - matches[2].rm_so + 1, "%s", commande + matches[2].rm_so);

        // Définir la variable
        if (set_variable(name, value))
        {
            afficher_message("Variable defined successfully.", "Variable définie avec succès.", lang);
        }
        regfree(&regex); // Libérer la mémoire allouée à la regex
        return;
    }

    regfree(&regex); // Libérer la mémoire allouée à la regex

    // Si la commande n'est pas reconnue, affiche un message d'erreur
    afficher_message("Invalid variable declaration.", "Déclaration de variable invalide.", lang);
}

/**
 * Traite une commande entrée par l'utilisateur.
 * @param commande La commande entrée par l'utilisateur
 * @param commandes Tableau des commandes disponibles
 * @param nombre_commandes Nombre de commandes dans le tableau
 */
void traiter_commande(char *commande, Commande commandes[], int nombre_commandes)
{
    char commande_originale[1024];
    strcpy(commande_originale, commande); // Sauvegarde la commande originale pour les messages d'erreur
    convertir_en_minuscules(commande);    // Convertit la commande en minuscules

    for (int i = 0; i < nombre_commandes; i++)
    {
        // Vérifie si la commande entrée correspond à une commande en anglais ou en français
        if (strncmp(commande, commandes[i].commande_en, strlen(commandes[i].commande_en)) == 0 ||
            strncmp(commande, commandes[i].commande_fr, strlen(commandes[i].commande_fr)) == 0)
        {
            // Détermine la langue de la commande
            char *lang = (strncmp(commande, commandes[i].commande_fr, strlen(commandes[i].commande_fr)) == 0) ? "fr" : "en";
            // Exécute la fonction associée à la commande
            if (commandes[i].fonction == (void (*)(char *, char *))afficher_aide)
            { // cast nécessaire pour éviter un avertissement
                afficher_aide(commandes, nombre_commandes, lang);
            }
            else
            {
                commandes[i].fonction(commande, lang);
            }
            return;
        }
    }

    // Si la commande commence par un chiffre ou une parenthèse, on l'évalue comme une expression mathématique
    if (isdigit(commande[0]) || commande[0] == '(')
    {
        traiter_expression(commande, "en");
        return;
    }

    // Si la commande est une déclaration de variable
    if (strchr(commande, '='))
    {
        traiter_variable(commande, "en");
        return;
    }

    // Si la commande n'est pas reconnue, essayer de voir si c'est une variable
    Variable *variable = get_variable(commande);
    if (variable)
    {
        print_variable(variable);
        return;
    }

    // Si la commande n'est pas reconnue, affiche un message d'erreur
    printf("Erreur : la variable '%s' n'est pas définie.\n", commande_originale);
}

int main()
{
    // Initialisation des commandes disponibles
    Commande commandes[] = {
        {"quit", "quitter", traiter_quit, "Quit the program", "Quitter le programme"},
        {"echo", "afficher", traiter_echo, "Echo the text", "Afficher le texte"},
        {"date", "date", afficher_date, "Display the current date", "Afficher la date actuelle"},
        {"version", "version", afficher_version, "Display the compiler version", "Afficher la version du compilateur"},
        {"help", "aide", (void (*)(char *, char *))afficher_aide, "Show help", "Afficher l'aide"},
    };
    int nombre_commandes = sizeof(commandes) / sizeof(Commande);

    // Initialisation de la table des variables
    init_symbol_table();

    // Boucle principale pour lire et traiter les commandes utilisateur
    while (1)
    {
        printf("> "); // Affiche le prompt de commande
        char commande[1024];
        if (!fgets(commande, sizeof(commande), stdin))
        {          // Lit la commande utilisateur. On n'utilise pas scanf pour éviter les problèmes de buffer
            break; // Arrête le programme en cas d'erreur de lecture
        }
        commande[strcspn(commande, "\n")] = 0; // Supprime le caractère de fin de ligne
        if (strlen(commande) > 0)
        { // Ignore les commandes vides
            traiter_commande(commande, commandes, nombre_commandes);
        }
        printf("\n"); // Saut de ligne après chaque commande
    }
    return 0;
}