import numpy as np

with open("tiempos4.txt") as archivo:
    lineas = [l.replace("\n", "") for l in archivo.readlines()]

tiempos = [[], [], [], [], []]
for i, linea in enumerate(lineas):
    if i % 6 == 0:
        continue

    # print(i % 6 - 1, linea)
    tiempos[i % 6 - 1].append(float(linea))

print(lineas[0])
for i in range(5):
    print(np.mean(tiempos[i]))


