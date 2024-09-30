#include <stdio.h>

int longueur(char *chaine) {
    int i = 0;
    while (chaine[i] != '\0') {
        i++;
    }
    return i;
}

void copie(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void concatene(char *dest, char *src) {
    int i = 0;
    while (dest[i] != '\0') {
        i++;
    }
    int j = 0;
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}


int main() {
    char chaine1[100];
    char chaine2[100];
    printf("Saisir une chaine de caractere : ");
    scanf("%s", chaine1);

    printf("Saisir une autre chaine de caractere : ");
    scanf("%s", chaine2);

    printf("Longueur de chaine1 : %d\n", longueur(chaine1));
    printf("Longueur de chaine2 : %d\n", longueur(chaine2));
    char chaine3[100];
    copie(chaine3, chaine1);
    printf("Copie de chaine1 dans chaine3 : %s\n", chaine3);
    concatene(chaine3, chaine2);
    printf("Concatenation de chaine1 et chaine2 dans chaine3 : %s\n", chaine3);
    return 0;
}

