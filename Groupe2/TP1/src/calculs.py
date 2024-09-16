def main():
    # Lecture de la première valeur
    num1 = int(input("Valeur 1 : \n"))

    # Lecture de l'opérateur
    op = input("Entrez un opérateur : ")

    # Pour les opérateurs autres que ~, demander une deuxième valeur
    if op != '~':
        num2 = int(input("Valeur 2 : \n"))

    # Exécution de l'opération en fonction de l'opérateur
    if op == '+':
        print(f"{num1} {op} {num2} = {num1 + num2}")
    elif op == '-':
        print(f"{num1} {op} {num2} = {num1 - num2}")
    elif op == '*':
        print(f"{num1} {op} {num2} = {num1 * num2}")
    elif op == '/':
        if num2 != 0:
            print(f"{num1} {op} {num2} = {num1 / num2}")
        else:
            print("Erreur : division par zéro")
    elif op == '%':
        if num2 != 0:
            print(f"{num1} {op} {num2} = {num1 % num2}")
        else:
            print("Erreur : division par zéro")
    elif op == '&':
        print(f"{num1} {op} {num2} = {num1 & num2}")
    elif op == '|':
        print(f"{num1} {op} {num2} = {num1 | num2}")
    elif op == '~':
        print(f"{op}{num1} = {~num1}")
    else:
        print("Opérateur invalide")


if __name__ == "__main__":
    main()
