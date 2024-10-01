#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

// Définition de la structure pour les commandes
typedef struct
{
    char* commande;
    void (*fonction)(char*); // Change function pointer to accept char* argument
    char* description;
} Commande;

// Prototypes des fonctions
void afficher_version(char* unused);
void afficher_aide(Commande commandes[], int nombre_commandes);
void traiter_echo(char* commande);
void traiter_quit(char* unused);
void afficher_date(char* unused);

void afficher_version(char* unused)
{
    printf("Version %s\n", __VERSION__);
}

void afficher_aide(Commande commandes[], int const nombre_commandes)
{
    printf("Liste des commandes disponibles:\n");

    // Parcours du tableau de commandes
    for (int i = 0; i < nombre_commandes; i++)
    {
        printf("  %s: %s\n", commandes[i].commande, commandes[i].description);
    }
}

void traiter_echo(char* commande)
{
    // Affiche le texte après la commande "echo"
    printf("Echo: ");

    // Imprime la chaîne à partir de l'index 5, si la commande est "echo"
    if (strncmp(commande, "echo ", 5) == 0)
    {
        printf("%s\n", commande + 5);
    }
    else
    {
        printf("Commande invalide.\n");
    }
}

void traiter_quit(char* unused)
{
    printf("Arrêt...\n");
    exit(0);
}

void afficher_date(char* unused)
{
    printf("Date: ");
    // Imprime la date du jour
    time_t const t = time(NULL);
    struct tm const tm = *localtime(&t);
    printf("%02d-%02d-%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min,
           tm.tm_sec);
}

void traiter_commande(char* commande, Commande commandes[], int const nombre_commandes)
{
    for (int i = 0; i < nombre_commandes; i++)
    {
        // Vérifie si la commande entrée par l'utilisateur correspond à une commande valide
        if (strncmp(commande, commandes[i].commande, strlen(commandes[i].commande)) == 0)
        {
            // Exécute la fonction associée à la commande
            if (commandes[i].fonction == (void (*)(char*))afficher_aide)
            {
                // Si la commande est "help", affiche l'aide
                afficher_aide(commandes, nombre_commandes);
            }
            else
            {
                commandes[i].fonction(commande);
            }

            return;
        }
    }
    printf("Commande non reconnue. Tapez 'help' pour afficher la liste des commandes disponibles.\n");
    return;
}

int main()
{
    // déclarer les commandes
    Commande commandes[] = {
        {"quit", traiter_quit, "Quitter le programme"},
        {"echo", traiter_echo, "Afficher du texte"},
        {"date", afficher_date, "Afficher la date et l'heure actuelles"},
        {"version", afficher_version, "Afficher la version du programme"},
        {"help", (void (*)(char*))afficher_aide, "Afficher l'aide"} // Cast help to match signature
    };

    int const nombre_commandes = sizeof(commandes) / sizeof(Commande);

    // Boucle principale qui lit et traite les commandes utilisateur
    while (1)
    {
        printf("> "); // Affiche le prompt de commande

        // Buffer pour stocker la commande utilisateur
        char commande[1024];

        // Lit la commande utilisateur et la stocke dans le buffer
        fgets(commande, sizeof(commande), stdin);

        // Enlève le caractère de fin de ligne ajouté par fgets
        commande[strcspn(commande, "\n")] = 0;

        if (strlen(commande) == 0)
        {
            // Ignore les commandes vides
            continue;
        }

        // Parcours du tableau de commandes
        traiter_commande(commande, commandes, nombre_commandes);

        printf("\n"); // Saut de ligne après la sortie
    }

    return 0;
}
