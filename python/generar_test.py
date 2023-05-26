import numpy as np
import sys

# Set the seed for reproducibility (optional)
np.random.seed(41)

# Generate random points
try:
    num_points = int(sys.argv[1])
    coord_range = int(sys.argv[2])
except (ValueError, IndexError):
    print(
        "Uso incorrecto. Pasar por parámetro la cantidad de puntos objetivo y el máximo número de una coordenada."
    )
    print(
        "No necesariamente se generará la cantidad solicitada, solo se mostraran los puntos únicos."
    )
    print("Ejemplo:")
    print("python ./generar_tests.py 100 20")

x = np.random.randint(low=0, high=coord_range, size=num_points)
y = np.random.randint(low=0, high=coord_range, size=num_points)
points = np.column_stack((x, y))
unique_points = np.unique(points, axis=0)

n = len(unique_points)
modems = np.random.randint(1, num_points // 2)
max_utp = np.random.randint(1, num_points // 10)
utp = 1
fo = 2
print(1, n, max_utp, modems, utp, fo)
for cx, cy in unique_points:
    print(cx, cy)
