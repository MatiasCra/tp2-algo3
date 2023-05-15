#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

vector<list<int>> aristas;
vector<list<int>> aristas_invertidas;
vector<int> color;
stack<int> procesados;
int m = 0;
int n = 0;

void leer_input() {
    /*
     * Leo test de stdin, cargo las dimensiones, la lista de adyacencia y la lista invertida.
     */
    cin >> n >> m;
    aristas = vector<list<int>>(n);
    aristas_invertidas = vector<list<int>>(n);
    for (int i = 0; i < m; ++i) {
        int desde, hasta;
        cin >> desde >> hasta;
        aristas[desde - 1].push_back(hasta - 1);
        aristas_invertidas[hasta - 1].push_back(desde - 1);
    }
}

void dfs(int v, int marcar = 1, bool pushear = true) {
    /*
     * Recorro por dfs el grafo recursivamente, marco los visitados con un color (número).
     * Si se indica, pusheo los nodos a un stack al terminar de procesarlos.
     */
    color[v] = marcar;

    for (int u: aristas[v]) {
        if (not color[u])
            dfs(u, marcar, pushear);
    }

    if (pushear)
        procesados.push(v);
}

int main() {
    leer_input();

    // Recorro el grafo llenando el stack.
    color = vector<int>(n, 0);  // 0 = sin color, 1 = con color (visitado)
    for (int i = 0; i < n; ++i) {
        if (not color[i])
            dfs(i);
    }

    // Recorro D transpesto
    color = vector<int>(n, 0);          // Reseteo colores
    swap(aristas, aristas_invertidas);  // swapeo direcciones, O(1)

    // Asigno un color distinto a cada componente fuertemente conexa.
    int componente = 0;  // color de la componente, incrementa en 1 antes de cada dfs
    while (!procesados.empty()) {
        int v = procesados.top();
        procesados.pop();
        if (color[v] == 0) {
            dfs(v, ++componente, false);
        }
    }
    swap(aristas, aristas_invertidas);  // Recupero aristas originales

    // Busco las raices del grafo de cfc (las cfc que no tienen entradas de otras cfc). Esas son en las que tengo que
    // tirar una pieza.
    vector<bool> es_raiz(componente, true);
    for (int desde = 0; desde < n; ++desde) {
        for (int hasta: aristas[desde]) {
            if (color[desde] != color[hasta])
                es_raiz[color[hasta] - 1] = false;
        }
    }

    // Agrego una pieza por cfc raiz.
    list<int> res;
    vector<bool> cfc_en_res(componente, false);
    for (int v = 0; v < n; ++v) {
        if (es_raiz[color[v] - 1] and not cfc_en_res[color[v] - 1]) {
            res.push_back(v);
            cfc_en_res[color[v] - 1] = true;
        }
    }

    // Output
    cout << res.size() << endl;
    for (int v: res)
        cout << v + 1 << " ";
    cout << endl;

    return 0;
}