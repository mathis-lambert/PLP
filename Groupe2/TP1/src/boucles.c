#include <stdio.h>

int main()
{
    int taille;

    printf("Entrez la taille du triangle (strictement inférieure à 10) : ");
    scanf("%d", &taille);

    if (taille >= 10)
    {
        printf("La taille doit être strictement inférieure à 10.\n");
        return 1;
    }


    // Boucle for
    for (int i = 1; i <= taille; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (j == 1 || j == i || i == taille)
            {
                printf("* ");
            }
            else
            {
                printf("# ");
            }
        }
        printf("\n");
    }

    // Boucle While
    int i = 1;
    while (i <= taille)
    {
        int j = 1;
        while (j <= i)
        {
            if (j == 1 || j == i || i == taille)
            {
                printf("* ");
            }
            else
            {
                printf("# ");
            }
            j++;
        }
        printf("\n");
        i++;
    }

    // Avec do...while
    int i_2 = 1;
    do {
        int j = 1;
        do {
            if (j == 1 || j == i_2 || i_2 == taille) {
                printf("* ");
            } else {
                printf("# ");
            }
            j++;
        } while (j <= i_2);
        printf("\n");
        i_2++;
    } while (i_2 <= taille);

    return 0;
}
