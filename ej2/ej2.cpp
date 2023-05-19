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
bool es_raiz;

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

void dfs(int v, int marcar = 1, bool transpuesta = false) {
    /*
     * Recorro por dfs el grafo recursivamente, marco los visitados con un color (número).
     * Si se indica, pusheo los nodos a un stack al terminar de procesarlos.
     */
    color[v] = marcar;

    for (int u: aristas[v]) {
        if (not color[u])
            dfs(u, marcar, transpuesta);
        else if (transpuesta and color[u] != color[v])
            es_raiz = false;
    }

    if (not transpuesta)
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
    color = vector<int>(n, 0);  // Reseteo colores
    aristas = std::move(aristas_invertidas);  // Reemplazo dirección, O(1)

    // Asigno un color distinto a cada componente fuertemente conexa.
    list<int> res;  // Respuesta
    int componente = 0;  // color de la componente, incrementa en 1 antes de cada dfs
    // Recorro en el orden topológico que dá el stack de procesados
    while (!procesados.empty()) {
        int v = procesados.top();
        procesados.pop();

        // Si todavía no visite su cfc...
        if (color[v] == 0) {
            // Asumo que es raiz
            es_raiz = true;
            // Recorro la cfc. Si encuentro una arista a un vertice de otra cfc, no es raiz (la arista va al revés en D)
            dfs(v, ++componente, true);
            if (es_raiz)
                res.push_back(v);
        }

    }

    // Output
    cout << res.size() << endl;
    for (auto v = prev(res.end()); v != res.end(); --v)
        cout << *v + 1 << " ";
    cout << endl;

    return 0;
}