#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
enum Tipo_Arista {
    UTP, FO
};

int cant_oficinas;
int dist_tope_UTP;
int cant_modems;
int precio_UTP;
int precio_FO;
int comp_conexas;
vector<tuple<int,int>> nodos;
vector<tuple<double,int,int,Tipo_Arista>> aristas; //Costo, arista_1, arista_2, UTP o FO o MODEM

struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        comp_conexas--;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};


void leer_input() {
    // Leo test de stdin, cargo las dimensiones, la lista de adyacencia e inicializo los arrays.
    cin >> cant_oficinas >> dist_tope_UTP >> cant_modems >> precio_UTP >> precio_FO;
    nodos = vector<tuple<int,int>>(cant_oficinas);
    comp_conexas = cant_oficinas;
    for (int i = 0; i < cant_oficinas; ++i) {
        int coord_x, coord_y;
        cin >> coord_x >> coord_y;
        nodos[i] = make_tuple(coord_x, coord_y);
    }
}

void obtener_aristas(){
    //Agrego aristas entre todos los nodos
    for (int i = 0; i < cant_oficinas; ++i) {
        for (int j = i+1; j < cant_oficinas; ++j) {
            double dist = sqrt( pow(get<0>(nodos[i]) - get<0>(nodos[j]) ,2) + pow(get<1>(nodos[i]) - get<1>(nodos[j]) ,2));
            if (dist < dist_tope_UTP){
                aristas.emplace_back(dist * precio_UTP,i,j,UTP);
            } else {
                aristas.emplace_back(dist * precio_FO,i,j,FO);
            }
        }
    }
}


int main () {
    int casos_de_test;
    cin >> casos_de_test;

    for (int i = 1; i <= casos_de_test; ++i) {
        leer_input();
        obtener_aristas();
        sort(aristas.begin(), aristas.end());
        DSU dsu(cant_oficinas);
        double costo_UTP = 0;
        double costo_FO = 0;
        for (auto [c, u, v, tipo]: aristas) {
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
        cout << fixed;
        cout << "Caso #" << i << ": " << costo_UTP << " " << costo_FO << endl;
    }
    return 0;
}