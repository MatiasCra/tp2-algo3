#ifndef TP2_ALGO3_DSUS_H
#define TP2_ALGO3_DSUS_H

#include <vector>

using namespace std;

struct DSU {

    DSU(int n) {
        padre = vector<int>(n);
        for (int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v) {
        if (v == padre[v]) return v;
        return find(padre[v]);
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        padre[v] = u;
    }

    vector<int> padre;
};

struct DSU_PC {

    DSU_PC(int n) {
        padre = vector<int>(n);
        for (int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v) {
        if (v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        padre[v] = u;
    }

    vector<int> padre;
};

struct DSU_UBR {

    DSU_UBR(int n) {
        padre = rank = vector<int>(n);
        for (int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v) {
        if (v == padre[v]) return v;
        return find(padre[v]);
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (rank[u] < rank[v]) swap(u, v);
        padre[v] = u;
        rank[u] = max(rank[u], rank[v] + 1);
    }

    vector<int> padre;
    vector<int> rank;
};

struct DSU_PC_UBR {

    DSU_PC_UBR(int n) {
        padre = rank = vector<int>(n);
        for (int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v) {
        if (v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (rank[u] < rank[v]) swap(u, v);
        padre[v] = padre[u];
        rank[u] = max(rank[u], rank[v] + 1);
    }

    vector<int> padre;
    vector<int> rank;
};

#endif
