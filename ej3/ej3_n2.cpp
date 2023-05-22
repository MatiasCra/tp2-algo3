#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <tuple>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

#define MAXDOUBLE numeric_limits<double>::max()

enum TipoArista {
    UTP, FO
};

int cant_oficinas;
int dist_tope_UTP;
int cant_modems;
int precio_UTP;
int precio_FO;
int comp_conexas;
vector<tuple<int, int>> nodos;
vector<vector<pair<double, TipoArista>>> adyacencia;

void leer_input() {
    // Leo test de stdin, cargo las dimensiones, la lista de adyacencia e inicializo los arrays.
    cin >> cant_oficinas >> dist_tope_UTP >> cant_modems >> precio_UTP >> precio_FO;
    nodos = vector<tuple<int, int>>(cant_oficinas);
    comp_conexas = cant_oficinas;

    for (int i = 0; i < cant_oficinas; ++i) {
        int coord_x, coord_y;
        cin >> coord_x >> coord_y;
        nodos[i] = tuple<int, int>(coord_x, coord_y);
    }
}

void obtener_aristas() {
    // Agrego aristas entre todos los nodos
    adyacencia = vector<vector<pair<double, TipoArista>>>(
            cant_oficinas, vector<pair<double, TipoArista>>(
                    cant_oficinas, make_pair(MAXDOUBLE, FO)
            )
    );

    for (int i = 0; i < cant_oficinas; ++i) {
        for (int j = i + 1; j < cant_oficinas; ++j) {
            double dist = sqrt(
                    pow(get<0>(nodos[i]) - get<0>(nodos[j]), 2) + pow(get<1>(nodos[i]) - get<1>(nodos[j]), 2));

            if (dist <= dist_tope_UTP) {
                adyacencia[j][i] = adyacencia[i][j] = make_pair(dist * precio_UTP, UTP);
            } else {
                adyacencia[j][i] = adyacencia[i][j] = make_pair(dist * precio_FO, FO);
            }
        }
    }
}

pair<int, int> arista_minima(vector<double> &min_coste, vector<bool> &es_representante) {
    /*
     * Busco la arista mínima de un arbol del bosque a otro.
     * */

    // Eligo min entre la min de cada árbol
    int idx = 0;
    while (not es_representante[idx]) ++idx;
    for (int i = idx + 1; i < cant_oficinas; ++i) {
        if (not es_representante[i]) continue;
        if (min_coste[i] < min_coste[idx]) idx = i;
    }

    // La min es una arista del árbol con representante idx, de coste min_coste[idx]. Busco a qué otro árbol conecta
    double coste = min_coste[idx];
    int objetivo = 0;
    for (int i = 0; i < cant_oficinas; ++i) {
        if (not es_representante[i]) continue;
        if (adyacencia[idx][i].first == coste) {
            objetivo = i;
            break;
        }
    }

    return {idx, objetivo};
}

void
contraer(pair<int, int> &siguiente_arista, vector<double> &min_coste, vector<bool> &es_representante) {
    /*
     * Contraigo a un vértice por árbol del bosque (centro todas las aristas de un árbol en su representate).
     */

    int u = siguiente_arista.first, v = siguiente_arista.second;
    es_representante[v] = false;  // árbol de representante v pasa al árbol de representante u
    min_coste[u] = MAXDOUBLE;
    // Actualizo aristas del árbol de u para incluir aristas del árbol de v, también la árista mínima que va del árbol a
    // otro
    for (int i = 0; i < cant_oficinas; ++i) {
        if (not es_representante[i] or i == u) continue;
        adyacencia[i][u] = adyacencia[u][i] = min(adyacencia[u][i], adyacencia[v][i]);
        min_coste[u] = min(min_coste[u], adyacencia[u][i].first);
    }
}


int main() {
    int casos_de_test;
    cin >> casos_de_test;

    for (int i = 1; i <= casos_de_test; ++i) {
        leer_input();
        obtener_aristas();
        double costo_UTP = 0;
        double costo_FO = 0;

        // Kruskal en O(n^2)
        vector<bool> es_representante(cant_oficinas, true);  // Un representante por árbol del bosque
        vector<double> min_coste(cant_oficinas, MAXDOUBLE);  // Min coste de un árbol a otro
        for (int j = 0; j < cant_oficinas; ++j) {
            for (int k = j + 1; k < cant_oficinas; ++k) {
                min_coste[j] = min(min_coste[j], adyacencia[j][k].first);
                min_coste[k] = min(min_coste[k], adyacencia[k][j].first);
            }
        }

        // Elijo aristas. Paro cuando tenga los W árboles en los que irán los modems
        for (int j = 0; j < cant_oficinas - cant_modems; ++j) {
            pair<int, int> siguiente_arista = arista_minima(min_coste, es_representante);
            TipoArista tipo = adyacencia[siguiente_arista.first][siguiente_arista.second].second;
            double coste = adyacencia[siguiente_arista.first][siguiente_arista.second].first;
            if (tipo == UTP)
                costo_UTP += coste;
            else if (tipo == FO)
                costo_FO += coste;

            contraer(siguiente_arista, min_coste, es_representante);
        }

        cout << fixed;
        cout << setprecision(3) << "Caso #" << i << ": " << costo_UTP << " " << costo_FO << endl;
    }

    return 0;
}