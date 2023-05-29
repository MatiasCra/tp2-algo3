import matplotlib.pyplot as plt
import numpy as np
import sys

labels = [
    "DSU con Union By Rank",
    "DSU con Path Compression",
    "DSU sin Optimizar",
    "DSU con Union By Rank y Path Compression",
    "Denso",
]

M_DSU_UBR, M_DSU_PC, M_DSU, M_DSU_UBR_PC, M_DENSO = 0, 1, 2, 3, 4

# Read data from the file
test_sizes = []
test_runtimes = []

with open(sys.argv[1], "r") as file:
    lines = file.readlines()
    num_lines = len(lines)
    i = 0

    while i < num_lines:
        size = int(lines[i].strip())
        test_sizes.append(size)
        runtimes = [float(line.strip()) for line in lines[i + 1 : i + 6]]
        test_runtimes.append(runtimes)
        i += 6

# Convert runtimes to a numpy array
test_runtimes = np.array(test_runtimes)
test_sizes = np.array(test_sizes, dtype=float)

# Create a line plot for each version of the program
line_styles = ['--', ':', '-', '-.']
for i in range(test_runtimes.shape[1]):
    plt.plot(np.log(test_sizes), np.log(test_runtimes[:, i]), label=labels[i], linestyle=line_styles[i % len(line_styles)])

# Customize the plot
plt.xlabel("Log de cantidad de oficinas")
plt.ylabel("Log de tiempo de ejecución")
plt.title("Tiempo de ejecución con distintas implementaciones de Kruskal (escala logarítmica)")
plt.legend()

# Display or save the plot
plt.show()
