# Bibliothèques

* stdio.h
* stdlib.h
* string.h
* ctype.h
* math.h
* parseur.h
* lexer.h
* evaluation.h
* time.h

# Références

* [Abstract syntax tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree)
* [Interpreter (computing)](https://en.wikipedia.org/wiki/Interpreter_(computing))
* [Parser](https://en.wikipedia.org/wiki/Parser)
* [Lexical analysis](https://en.wikipedia.org/wiki/Lexical_analysis)
* [Interpreter pattern](https://en.wikipedia.org/wiki/Interpreter_pattern)
* [malloc](https://koor.fr/C/cstdlib/malloc.wp)
* [free](https://koor.fr/C/cstdlib/free.wp)
* [atoi](https://koor.fr/C/cstdlib/atoi.wp)
* [Structures](https://zestedesavoir.com/tutoriels/755/le-langage-c-1/1043_aggregats-memoire-et-fichiers/4279_structures/)
* [Pointeurs](https://zestedesavoir.com/tutoriels/755/le-langage-c-1/1043_aggregats-memoire-et-fichiers/4277_les-pointeurs/)
* [isdigit](https://koor.fr/C/cctype/isdigit.wp)
* [atof](https://koor.fr/C/cstdlib/atof.wp)
* [strcmp](https://koor.fr/C/cstring/strcmp.wp)
* [strchr](https://koor.fr/C/cstring/strchr.wp)
* [Stack Overflow (Pour les bugs)](https://stackoverflow.com/)
* [ChatGPT (pour les bugs si réponse non trouvée sur StackOverflow)](https://chatgpt.com/)

# Difficulté

* 7/10 beaucoup plus de travail de recherche et de programmation que les TPs précédents.

# Commentaires

## Exercice 3.1

- Qu'est-ce qui se passe lorsque vous tapez une commande inconnue?
    - Quand on tape une commande inconnue, le programme affiche un message d'erreur.
- Comment l'interpréteur traite les espaces dans les commandes?
    - L'interpréteur traite les espaces comme des séparateurs entre les arguments de la commande. Par exemple, si on
      tape `echo Bonjour, monde!`, l'interpréteur considère `echo` comme la commande et `Bonjour,` et `monde!` comme des
      arguments.
- Qu'est-ce qui se passe lorsque vous utilisez la commande echo avec des arguments?
    - La commande `echo` affiche les arguments saisis par l'utilisateur. Par exemple, si on tape `echo Bonjour, monde!`,
      l'interpréteur affiche `Bonjour, monde!`.
- Comment pourriez-vous modifier le code pour ajouter de nouvelles commandes?
    - Pour traiter des nouvelles commandes il faudrait ajouter des fonctions pour chaque nouvelle commande et les
      appeler dans la fonction `main()` en fonction de la commande saisie par l'utilisateur.

## Exercice 3.2

Code testé et fonctionnel.

## Exercice 3.3

Code testé et fonctionnel.

