print("Nombres divisibles par 4 mais pas par 6:")
for i in range(1, 1001):
    if i % 4 == 0 and i % 6 != 0:
        print(i, end=", ")

print("\nNombres pairs et divisibles par 8:")
for i in range(1, 1001):
    if i % 2 == 0 and i % 8 == 0:
        print(i, end=", ")

print("\nNombres divisibles par 5 ou 7 mais pas par 10:")
for i in range(1, 1001):
    if (i % 5 == 0 or i % 7 == 0) and i % 10 != 0:
        print(i, end=", ")
