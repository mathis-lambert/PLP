import math

rayon: float = int(input("Rayon du cercle (cm) : "))
aire: float = math.pi * rayon * rayon
perimeter: float = 2 * math.pi * rayon
print(f"L'aire du cercle : {aire} cm2 \nLe périmètre du cercle : {perimeter} cm")
