taille = int(input("Entrez la taille du triangle (strictement inférieure à 10) : "))

if taille >= 10:
    print("La taille doit être strictement inférieure à 10.")
    exit(1)

# avec for
for i in range(1, taille + 1):
    for j in range(1, i + 1):
        if j == 1 or j == i or i == taille:
            print('*', end=' ')
        else:
            print('#', end=' ')
    print()

# avec while
i = 1
while i <= taille:
    j = 1
    while j <= i:
        if (i + j) % 2 == 0:
            print('*', end=' ')
        else:
            print('#', end=' ')
        j += 1
    print()
    i += 1
