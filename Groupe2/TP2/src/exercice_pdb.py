from typing import List


def double_values(t: List[int]) -> List[int]:
    for compteur in range(len(t)):
        t[compteur] *= 2

    return t


# Créer un tableau d'exemple
tableau: List[int] = [1, 2, 3, 4, 5]

# Appeler la fonction et stocker le résultat
result = double_values(tableau)

# Afficher le résultat final
print(result)
