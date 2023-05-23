#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <tuple>
#include <iomanip>
#include <cmath>
#include <chrono>
#include "dsus.h"

using namespace std;

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
vector<tuple<double, int, int, TipoArista>> aristas;  // Costo, arista_1, arista_2, UTP o FO

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
    for (int i = 0; i < cant_oficinas; ++i) {
        for (int j = i + 1; j < cant_oficinas; ++j) {
            double dist = sqrt(
                    pow(get<0>(nodos[i]) - get<0>(nodos[j]), 2) + pow(get<1>(nodos[i]) - get<1>(nodos[j]), 2));

            if (dist <= dist_tope_UTP) {
                aristas.emplace_back(dist * precio_UTP, i, j, UTP);
            } else {
                aristas.emplace_back(dist * precio_FO, i, j, FO);
            }
        }
    }
}

enum TipoDSU {SIN_PC = 0, SIN_UBR = 1, SIN_NADA = 2, CON_TODO = 3};

int main(int argc, char *argv[]) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    int tipo_dsu = atoi(argv[1]);

    int casos_de_test;
    cin >> casos_de_test;

    for (int i = 1; i <= casos_de_test; ++i) {
        leer_input();
        aristas.clear();

        auto t1 = high_resolution_clock::now();

        obtener_aristas();
        sort(aristas.begin(), aristas.end());
        double costo_UTP = 0;
        double costo_FO = 0;

        if (tipo_dsu == CON_TODO) {

            DSU dsu(cant_oficinas);

            for (tuple<double, int, int, TipoArista> arista: aristas) {
                double c = get<0>(arista);
                int u = get<1>(arista);
                int v = get<2>(arista);
                TipoArista tipo = get<3>(arista);

                if (dsu.find(u) != dsu.find(v)) {
                    dsu.unite(u, v);
                    if (tipo == FO) {
                        costo_FO += c;
                    } else {
                        costo_UTP += c;
                    }

                    comp_conexas--;
                    if (comp_conexas == cant_modems) {
                        break;
                    }
                }
            }

            auto t2 = high_resolution_clock::now();

            duration<double, std::milli> ms_double = t2 - t1;
            cout << fixed << setprecision(10) << ms_double.count() / 1000 << endl;

        } else if (tipo_dsu == SIN_PC) {

            DSUSinPC dsu(cant_oficinas);

            for (tuple<double, int, int, TipoArista> arista: aristas) {
                double c = get<0>(arista);
                int u = get<1>(arista);
                int v = get<2>(arista);
                TipoArista tipo = get<3>(arista);

                if (dsu.find(u) != dsu.find(v)) {
                    dsu.unite(u, v);
                    if (tipo == FO) {
                        costo_FO += c;
                    } else {
                        costo_UTP += c;
                    }

                    comp_conexas--;
                    if (comp_conexas == cant_modems) {
                        break;
                    }
                }
            }

            auto t2 = high_resolution_clock::now();

            duration<double, std::milli> ms_double = t2 - t1;
            cout << fixed << setprecision(10) << ms_double.count() / 1000 << endl;
        } else if (tipo_dsu == SIN_UBR) {

            DSUSinUbR dsu(cant_oficinas);

            for (tuple<double, int, int, TipoArista> arista: aristas) {
                double c = get<0>(arista);
                int u = get<1>(arista);
                int v = get<2>(arista);
                TipoArista tipo = get<3>(arista);

                if (dsu.find(u) != dsu.find(v)) {
                    dsu.unite(u, v);
                    if (tipo == FO) {
                        costo_FO += c;
                    } else {
                        costo_UTP += c;
                    }

                    comp_conexas--;
                    if (comp_conexas == cant_modems) {
                        break;
                    }
                }
            }

            auto t2 = high_resolution_clock::now();

            duration<double, std::milli> ms_double = t2 - t1;
            cout << fixed << setprecision(10) << ms_double.count() / 1000 << endl;
        } else if (tipo_dsu == SIN_NADA) {

            DSUSinOptimizar dsu(cant_oficinas);

            for (tuple<double, int, int, TipoArista> arista: aristas) {
                double c = get<0>(arista);
                int u = get<1>(arista);
                int v = get<2>(arista);
                TipoArista tipo = get<3>(arista);

                if (dsu.find(u) != dsu.find(v)) {
                    dsu.unite(u, v);
                    if (tipo == FO) {
                        costo_FO += c;
                    } else {
                        costo_UTP += c;
                    }

                    comp_conexas--;
                    if (comp_conexas == cant_modems) {
                        break;
                    }
                }
            }

            auto t2 = high_resolution_clock::now();

            duration<double, std::milli> ms_double = t2 - t1;
            cout << fixed << setprecision(10) << ms_double.count() / 1000 << endl;
        }

        cout << setprecision(3) << "Caso #" << i << ": " << costo_UTP << " " << costo_FO << endl;
    }

    return 0;
}