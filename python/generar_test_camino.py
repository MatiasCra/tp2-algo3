import sys

acum = 0
cantidad_oficinas = int(sys.argv[1])
print(1)
print(cantidad_oficinas, 1, 1, 1, 2)
for i in range(cantidad_oficinas):
    print(0, acum + i)
    acum += i
