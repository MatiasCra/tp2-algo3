import sys
import subprocess
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import numpy as np

BASE_DIR = Path(__file__).resolve().parent.parent

archivos_tests = [Path(sys.argv[i]).resolve() for i in range(2, len(sys.argv))]
VECES_TESTEAR = int(sys.argv[1])

def leer_tamano(archivo_testear: Path):
    with open(archivo_testear) as archivo:
        while (l := archivo.readline()) == "\n":
            pass

        l = l.strip().replace("\n", "").split()
        if len(l) > 1:
            n = int(l[1])

        else:
            while (l := archivo.readline()) == "\n":
                pass

            n = int(l.strip().split()[0])

    return n


def correr_test(metodo: int, archivo_testear: Path) -> tuple[float, ...]:
    output = (
        subprocess.run(
            f"{BASE_DIR}/cmake-build-debug/ej3_benchmark {metodo} < {archivo_testear}",
            shell=True,
            capture_output=True,
            check=True,
        )
        .stdout.decode()
        .strip()
        .split("\n")
    )
    return tuple(float(x) for i, x in enumerate(output) if i % 2 == 0)


for archivo_tests in archivos_tests:
    tiempos_medidos = [[], [], [], [], []]

    for i in range(5):
        for _ in range(VECES_TESTEAR):
            tiempos_medidos[i].append(correr_test(i, archivo_tests))
    
    # tiempos = [np.mean([feature.result() for feature in features[j]]) for j in range(5)]
    tiempos = [np.mean(tiempos_medidos[i]) for i in range(5)]

    print(leer_tamano(archivo_tests))
    for tiempo in tiempos:
        print(tiempo)
