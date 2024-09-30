def search_phrase_in_file(filename, phrase):
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            lines = file.readlines()

        print("\nRésultats de la recherche :")
        found = False

        # Rechercher la phrase dans chaque ligne
        for i, line in enumerate(lines, start=1):
            count = line.count(phrase)
            if count > 0:
                print(f"Ligne {i} => {count} occurrence(s)")
                found = True

        if not found:
            print("Aucune occurrence trouvée.")

    except FileNotFoundError:
        print("Erreur : fichier non trouvé.")


if __name__ == "__main__":
    # Demander le nom du fichier et la phrase à rechercher
    filename = input("Entrez le nom du fichier : ")
    phrase = input("Entrez la phrase que vous souhaitez rechercher : ")

    # Exécuter la recherche
    search_phrase_in_file(filename, phrase)
