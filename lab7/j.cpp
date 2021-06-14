#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

struct edge {
    int s , t ,weight;
    edge(int s_, int t_, int weight_) {
        s = s_;
        t = t_;
        weight = weight_;
    }
};


int dsu[MAXN];
int rang[MAXN];

vector<edge> edges;

int find(int x) {
    if (dsu[x] == x) return x;
    int newP  = find(dsu[x]);
    dsu[x] = newP;
    return dsu[x];
}

void join(int x, int y) {
    x = find(x);
    y = find(y);
    if (rang[x] < rang[y]) {
        dsu[x] = y;
        return;
    }
    if (rang[x] > rang[y]) {
        dsu[y] = x;
        return;
    }
    dsu[x] = y;
    rang[y]++;
}

void init(int n) {
    for (int i = 0;i < n; i++) dsu[i] = i;
}


int main() {
    int n, m;
    cin >> n >> m;
    init(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        edges.emplace_back(x, y, w);
    }
    long long w = 0;
    sort(edges.begin(), edges.end(), [](edge a, edge b) { return a.weight < b.weight; });
    for (int i = 0; i < m; i++) {
        int u = edges[i].s;
        int v =  edges[i].t;
        if (find(u) != find(v)) {
            join(u, v);
            w += edges[i].weight;
        }
    }
    cout << w;
}