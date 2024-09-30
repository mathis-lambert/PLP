# Comparaison entre **C** et **Python**

## Bases de la programmation

### Affichage des données

- **C** : Utilise `printf` pour afficher des données. La fonction `printf` nécessite des spécificateurs de format pour
  indiquer le type des variables à afficher. Par exemple, `%d` pour les entiers, `%f` pour les flottants.

Exemple :

```c++
#include <stdio.h>

int main() {
    int nombre = 42;
    printf("Le nombre est : %d\n", nombre);
    return 0;
}
```

| Spécificateur | Type de données   | Description                                                        |
|---------------|-------------------|--------------------------------------------------------------------|
| %c            | char              | Affiche un caractère                                                |
| %d            | int               | Affiche un entier signé                                             |
| %i            | int               | Affiche un entier signé (identique à %d)                            |
| %f            | float             | Affiche un nombre à virgule flottante                               |
| %lf           | double            | Affiche un nombre à virgule flottante (double précision)            |
| %u            | unsigned int      | Affiche un entier non signé                                         |
| %ld           | long int          | Affiche un long entier signé                                        |
| %lu           | unsigned long     | Affiche un long entier non signé                                    |
| %x            | unsigned int      | Affiche un entier non signé en hexadécimal                          |
| %X            | unsigned int      | Affiche un entier non signé en hexadécimal (majuscule)              |
| %o            | unsigned int      | Affiche un entier non signé en octal                                |
| %p            | void*             | Affiche une adresse mémoire                                         |
| %s            | char*             | Affiche une chaîne de caractères                                    |
| %e            | float / double    | Affiche un nombre en notation scientifique                          |
| %g            | float / double    | Affiche un nombre en notation scientifique ou décimale selon la valeur |
| %n            | Aucun             | Stocke le nombre de caractères écrits jusqu'à présent               |
| %%            | Aucun             | Affiche le caractère %                                              |

- **Python** : Utilise `print` pour afficher des données. print est plus flexible et peut gérer plusieurs types de
  données sans spécificateurs de format. Les f-strings (introduits dans **Python** 3.6) permettent une interpolation de
  chaînes propre et efficace.

Exemple :

```python
nombre = 42
print(f"Le nombre est : {nombre}")
```

### Gestion de la mémoire

- **C** : La gestion de la mémoire est manuelle. Les programmeurs doivent allouer et libérer la mémoire en utilisant
  malloc, calloc, realloc, et free. Une mauvaise gestion peut entraîner des fuites de mémoire et des erreurs de
  segmentation.

Exemple :

```c++
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr == NULL) {
        return 1; // Allocation échouée
    }
    *ptr = 5;
    free(ptr); // Libération de la mémoire
    return 0;
}
```

**Python** : La gestion de la mémoire est automatique grâce au ramasse-miettes (garbage collector). Les objets non
utilisés sont automatiquement collectés, ce qui réduit le risque de fuites de mémoire.

## Manipulation des variables

### Déclaration des types

**C** : Les variables doivent être déclarées avec un type explicite (int, float, char, etc.). Le type est déterminé lors
de la compilation.

Exemple :

```c++
int entier = 10;
float flottant = 3.14;
```

**Python** : Le typage est dynamique. Les variables n'ont pas besoin d'une déclaration de type explicite. Le type est
déterminé à l'exécution.

Exemple :

```python
entier = 10
flottant = 3.14
```

**Python** supporte également les annotations de type (introduites dans **Python** 3.5) pour la documentation et
l'analyse statique :

Exemple :

```python
def ajouter(x: int, y: int) -> int:
    return x + y
```

## Opérateurs

### Arithmétiques

**C** : Utilise les opérateurs +, -, *, /, % pour les opérations arithmétiques. La division entre deux entiers est une
division entière par défaut.

Exemple :

```c++
int a = 5;
int b = 2;
int somme = a + b; // somme = 7
int division = a / b; // division = 2
```

**Python** : Utilise les mêmes opérateurs +, -, *, /, %. La division / retourne un flottant, tandis que // retourne une
division entière.

Exemple :

```python
a = 5
b = 2
somme = a + b  # somme = 7
division = a / b  # division = 2.5
division_entier = a // b  # division_entier = 2
```

### Logiques et Bit à Bit

**C** : Les opérateurs logiques sont `&&` (ET), `||` (OU), `!` (NON).
Les opérateurs bit à bit incluent `&` (ET), `|` (OU), `^` (XOR), `~` (NON), `<<` (décalage à gauche), `>>` (décalage à
droite).

Exemple :

```c++
int a = 5; // 0101 en binaire
int b = 3; // 0011 en binaire
int et = a & b; // et = 1 (0001 en binaire)
```

**Python** : Les opérateurs logiques sont and, or, not. Les opérateurs bit à bit sont &, |, ^, ~, <<, >>.

Exemple :

```python
a = 5  # 0101 en binaire
b = 3  # 0011 en binaire
et = a & b  # et = 1 (0001 en binaire)
```

## Boucles et Structures de Contrôle

### Délimitation des blocs de code

**C** : Utilise des accolades {} pour délimiter les blocs de code. Les instructions conditionnelles et les boucles sont
entourées d'accolades pour définir leur portée.

Exemple :

```c++
if (a > b) {
printf("a est plus grand que b\n");
}
```

**Python** : Utilise l'indentation pour délimiter les blocs de code. Les blocs de code doivent être correctement
indentés pour définir leur portée.

Exemple :

```python
if a > b:
    print("a est plus grand que b")
```

### Boucles

**C** : Utilise les boucles for, while, et do-while. La boucle for est souvent utilisée avec des indices.

Exemple :

```c++
for (int i = 0; i < 5; i++) {
printf("%d\n", i);
}
```

**Python** : Utilise les boucles for et while. La boucle for est souvent utilisée pour itérer sur des séquences (listes,
tuples, etc.).

Exemple :

```python
for i in range(5):
    print(i)
```

### Structures conditionnelles

**C** : Utilise les structures if, else if, else.

Exemple :

```c++
if (a > b) {
  printf("a est plus grand que b\n");
} else {
  printf("a n'est pas plus grand que b\n");
}
```

**Python** : Utilise if, elif, else.

Exemple :

```python
if a > b:
  print("a est plus grand que b")
else:
  print("a n'est pas plus grand que b")
```

## Conversion et Formatage

### Conversion en binaire

**C** : Utilise des boucles et des opérations bit à bit pour convertir un entier en binaire. Le formatage peut être
réalisé en utilisant des fonctions comme printf.

Exemple :

```c++
#include <stdio.h>

void afficher_binaire(int n) {
  int bits[32];
  int i = 0;
  while (n > 0) {
      bits[i++] = n % 2;
      n /= 2;
  }
  for (int j = i - 1; j >= 0; j--) {
      printf("%d", bits[j]);
  }
  printf("\n");
}
```
**Python** : Utilise la fonction intégrée bin() pour obtenir la représentation binaire d'un entier, ou des f-strings
pour un formatage plus flexible.

Exemple :

```python
nombre = 42
print(f"Représentation binaire : {bin(nombre)[2:]}")
```

La fonction bin() retourne une chaîne avec le préfixe '0b' pour indiquer que la chaîne est en binaire, donc [2:] est
utilisé pour retirer ce préfixe.