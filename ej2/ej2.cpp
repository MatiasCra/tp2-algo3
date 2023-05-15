#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

vector<list<int>> aristas;
vector<list<int>> aristas_invertidas;
vector<int> color;
vector<int> padre;
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

void dfs(int v, int marcar = 1, bool pushear = true, bool guardar_padre = false) {
    /*
     * Recorro por dfs el grafo recursivamente, marco los visitados con un color (número).
     * Si se indica, pusheo los nodos a un stack al terminar de procesarlos.
     */
    color[v] = marcar;

    for (int u: aristas[v]) {
        if (not color[u])
            dfs(u, marcar, pushear, guardar_padre);

        if (guardar_padre)
            padre[u] = v;
    }

    if (pushear)
        procesados.push(v);
}

int main() {
    leer_input();

    // Recorro el grafo llenando el stack
    color = vector<int>(n, 0);  // 0/false = sin color, 1/true = con color (visitado)
    for (int i = 0; i < n; ++i) {
        if (not color[i])
            dfs(i);
    }

    // Recorro D transpesto
    color = vector<int>(n, 0);          // Reseteo colores
    swap(aristas, aristas_invertidas);  // swapeo direcciones, O(1)

    // Asigno un color distinto a cada componente fuertemente conexa
    int componente = 0;  // color, incrementa en 1 antes de cada dfs
    while (!procesados.empty()) {
        int v = procesados.top();
        procesados.pop();
        if (color[v] == 0) {
            // dfs desde v con aristas invertidas, marcando componente
            dfs(v, ++componente, false);
        }
    }

    // Creo grafo nuevo, colapsando cada cfc en un vertice
    swap(aristas, aristas_invertidas);  // Recupero aristas originales
    vector<list<int>> aristas_colapsado(componente);
    for (int desde = 0; desde < n; ++desde) {
        for (int hasta: aristas[desde]) {
            aristas_colapsado[color[desde] - 1].push_back(color[hasta] - 1);  // Puede haber repetidas
        }
    }

    vector<int> cfcs = color;
    color = vector<int>(componente, 0);
    padre = vector<int>(componente, 0);
    componente = 0;
    swap(aristas, aristas_colapsado);

    for (int v = 0; v < n; ++v) {
        if (color[cfcs[v] - 1] == 0) {
            dfs(cfcs[v] - 1, ++componente, false, true);
        }
    }

    list<int> res;
    swap(aristas, aristas_colapsado);  // Recupero aristas
    vector<bool> cfc_procesado(componente, false);
    for (int v = 0; v < n; ++v) {
        if (cfc_procesado[cfcs[v] - 1]) {
            continue;
        }

        if (padre[cfcs[v] - 1] == 0) {
            cfc_procesado[cfcs[v] - 1] = true;
            res.push_back(v);
        }
    }

    // Output
    cout << res.size() << endl;
    for (int v: res)
        cout << v + 1 << " ";
    cout << endl;

    return 0;
}