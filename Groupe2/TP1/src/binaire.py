def afficher_binaire(n):
    # Gérer le cas où n est nul
    if n == 0:
        print("0")
        return

    bits = []

    # Rajouter les bits dans le tableau
    while n > 0:
        bits.append(n % 2)
        n = n // 2

    # Afficher les bits dans l'ordre inverse
    print("Représentation binaire : ", end="")
    for bit in reversed(bits):
        print(bit, end="")
    print()


def main():
    # Lecture de la valeur de l'utilisateur
    nombre = int(input("Entrez un nombre entier : "))
    afficher_binaire(nombre)


if __name__ == "__main__":
    main()
