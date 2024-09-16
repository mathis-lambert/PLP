#include <stdio.h>

void afficher_binaire(int n) {
    int bits[32]; // Tableau pour stocker les bits (32 bits pour un entier)
    int i = 0;

    // Gérer le cas où n est nul
    if (n == 0) {
        printf("0\n");
        return;
    }

    // Rajouter les bits dans le tableau
    while (n > 0) {
        bits[i] = n % 2;
        n = n / 2;
        i++;
    }

    // Afficher les bits en ordre inverse car on a rempli le tableau à l'envers (du bit de poids faible au bit de poids fort)
    printf("Représentation binaire : ");
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", bits[j]);
    }
    printf("\n");
}

int main() {
    int nombre;

    printf("Entrez un nombre entier : ");
    scanf("%d", &nombre);

    afficher_binaire(nombre);

    return 0;
}
