#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <tuple>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

#define INF numeric_limits<double>::max()

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
vector<vector<double>> adyacencia;

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
    adyacencia = vector<vector<double>>(cant_oficinas, vector<double>(cant_oficinas, 0));

    for (int i = 0; i < cant_oficinas; ++i) {
        for (int j = i + 1; j < cant_oficinas; ++j) {
            double dist = sqrt(
                    pow(get<0>(nodos[i]) - get<0>(nodos[j]), 2) + pow(get<1>(nodos[i]) - get<1>(nodos[j]), 2));

            if (dist <= dist_tope_UTP) {
                adyacencia[i][j] = dist * precio_UTP;
            } else {
                adyacencia[i][j] = dist * precio_FO;
            }
        }
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

        // TODO: Kruskal n**2


        cout << fixed;
        cout << setprecision(3) << "Caso #" << i << ": " << costo_UTP << " " << costo_FO << endl;
    }

    return 0;
}