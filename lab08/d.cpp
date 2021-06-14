#include <iostream>
#include <vector>


using namespace std;

const int INF = (int)1e9;

struct edge {
    int s;
    int e;
    int w;

    edge(int s_, int e_, int w_) {
        s = s_;
        e = e_;
        w = w_;
    }

};

int d[10005][105];

int min(int a, int b) {
    return a > b ? b : a;
}




vector <edge> edges;


int main() {
    int n, m, K, s;
    cin >> n >> m >> K >> s;
    s--;
    for (int i = 0; i < m; i++) {
        int st, e, w;
        cin >> st >> e >> w;
        st--; e--;
        edges.emplace_back(st, e , w);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= K; j++) {
            d[i][j] = INF;
        }
    }
    d[s][0] = 0;


    for (int k = 1; k <= K; k++) {
        for (auto e : edges) {
            if (d[e.s][k - 1] == INF) continue;
            d[e.e][k] = min(d[e.e][k], d[e.s][k - 1] + e.w);
        }
    }
    for (int i = 0; i < n; i++) {
        if (d[i][K] == INF) {
            cout << -1 << " ";
        } else {
            cout << d[i][K] << ' ';
        }
    }


}