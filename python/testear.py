import sys
import subprocess
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import numpy as np

BASE_DIR = Path(__file__).resolve().parent.parent

archivo_tests = Path(sys.argv[1]).resolve()
VECES_TESTEAR = int(sys.argv[2])


def correr_test(archivo_testear: Path) -> tuple[float, ...]:
    output = (
        subprocess.run(
            f"{BASE_DIR}/cmake-build-debug/ej3_benchmark 0 < {archivo_testear}",
            shell=True,
            capture_output=True,
            check=True,
        )
        .stdout.decode()
        .strip()
        .split("\n")
    )
    return tuple(float(x) for i, x in enumerate(output) if i % 2 == 0)


tiempos = []
with ThreadPoolExecutor() as executor:
    features = [
        executor.submit(correr_test, archivo_tests) for i in range(VECES_TESTEAR)
    ]


for feature in features:
    tiempo = feature.result()
    tiempos.append(tiempo)

print(np.sum(tiempos))
