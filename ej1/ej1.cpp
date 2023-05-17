#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>

using namespace std;

enum Estados {
    NO_LO_VI, EMPECE_A_VER, TERMINE_DE_VER
};

int n = 0;
int m = 0;

vector<list<int>> aristas;
vector<int> backConExtremoInferiorEn;
vector<int> backConExtremoSuperiorEn;
vector<list<int>> treeEdges;
vector<Estados> estado;
vector<int> memo_cubren;
vector<int> previo;
int contador_por_comp_conexas = 0;
vector<vector<long long>> memo_CB;

void leer_input() {
    // Leo test de stdin, cargo las dimensiones, la lista de adyacencia e inicializo los arrays.
    cin >> n >> m;

    // Inicializo estructuras.
    aristas = vector<list<int>>(n);
    backConExtremoInferiorEn = vector<int>(n, 0);
    backConExtremoSuperiorEn = vector<int>(n, 0);
    estado = vector<Estados>(n, NO_LO_VI);
    memo_cubren = vector<int>(n, -1);
    previo = vector<int>(n, -1);
    treeEdges = vector<list<int>>(n);
    memo_CB = vector<vector<long long>>(n + 1, vector<long long>(2 + 1, 0));

    // Leo aristas.
    for (int i = 0; i < m; ++i) {
        int ady_1, ady_2;
        cin >> ady_1 >> ady_2;
        aristas[ady_1 - 1].push_back(ady_2 - 1);
        aristas[ady_2 - 1].push_back(ady_1 - 1);
    }

}

void dfs_edges(int v, int p = -1) {
    estado[v] = EMPECE_A_VER;
    for (int u: aristas[v]) {
        if (estado[u] == NO_LO_VI) {
            treeEdges[v].push_back(u);
            treeEdges[u].push_back(v);
            previo[u] = v;
            dfs_edges(u, v);
        } else if (u != p && estado[u] == EMPECE_A_VER) {
            backConExtremoInferiorEn[v]++;
            backConExtremoSuperiorEn[u]++;
        }
    }
    estado[v] = TERMINE_DE_VER;
}

int cubren(int v, int p = -1) {
    if (memo_cubren[v] != -1) return memo_cubren[v];
    int res = 0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];
    for (int hijo: treeEdges[v]) {
        if (hijo != p) {
            res += cubren(hijo, v);
        }
    }
    memo_cubren[v] = res;
    return res;
}

void dfs(int v) {
    estado[v] = TERMINE_DE_VER;
    contador_por_comp_conexas++;
    for (int u: aristas[v]) {
        if (estado[u] != TERMINE_DE_VER) {
            dfs(u);
        }
    }
}

long long calcular_CB(int w, int k) {
    for (int i = 0; i <= w; ++i) {
        for (int j = 0; j <= min(i, k); ++j) {
            if (j == 0 || j == i) {
                memo_CB[i][j] = 1;
            } else {
                memo_CB[i][j] = memo_CB[i - 1][j - 1] + memo_CB[i - 1][j];
            }
        }
    }
    return memo_CB[w][k];
}

int main() {
    leer_input();  // Cargo input e inicializo estructuras

    // Me guardo las back-edges
    for (int i = 0; i < n; ++i) {
        if (estado[i] == NO_LO_VI) {
            dfs_edges(i);
        }
    }

    // Me armo el vector de cubren
    for (int i = 0; i < n; ++i) {
        if (memo_cubren[i] == -1) {
            cubren(i);
        }
    }

    // Por cada arista me fijo si es puente, si es puente la remuevo. Uso los treeEdges que tienen menos aristas (los
    // puentes son treeEdges).
    for (int v = 0; v < n; ++v) {
        for (auto it = treeEdges[v].begin(); it != treeEdges[v].end(); ++it) {
            int u = *it;
            if ((not cubren(u) and previo[u] == v) or (not cubren(v) and previo[v] == u)) {
                it = prev(treeEdges[v].erase(it));
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        estado[i] = NO_LO_VI;
    }

    // Vuevlo a correr dfs por cc cuento la cantidad de nodos por cc y hago la sumatoria de los numeros combinatorios
    // (#cc ,2)
    long long numerador_resultado = 0;
    long long denominador_resultado = calcular_CB(n, 2);;
    swap(treeEdges, aristas);  // Para que dfs use los treeEdges. Swapeo de direccion en O(1).
    for (int i = 0; i < n; ++i) {
        if (estado[i] == NO_LO_VI) {
            dfs(i);
            numerador_resultado += calcular_CB(contador_por_comp_conexas, 2);
            contador_por_comp_conexas = 0;
        }
    }
    cout << fixed;
    cout << setprecision(5) << 1 - ((float) numerador_resultado / (float) denominador_resultado) << endl;
    return 0;
}