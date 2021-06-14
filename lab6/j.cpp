#include <iostream>
#include <vector>

using namespace std;



const int MAXN = 200010;

int ANS[MAXN];

int n;


int sizes[MAXN];

bool isDeleted[MAXN];

vector <int> tree[MAXN];

void calcSize(int root, int p = 0) {
    sizes[root] = 1;
    for (int v : tree[root]) {
        if (v == p || isDeleted[v]) {
            continue;
        }
        calcSize(v, root);
        sizes[root] += sizes[v];
    }
}


int findCentroid(int root, int sz, int p) {
    for (int v : tree[root]) {
        if (!isDeleted[v] && p != v && (2 * sizes[v] > sz)) {
            return findCentroid(v, sz, root);
        }
    }
    return root;
}


void solve(int root = 1, int p = 0) {
    calcSize(root);
    int c = findCentroid(root, sizes[root], 0);
    isDeleted[c] = true;
    ANS[c] = p;
    for (int v : tree[c]) {
        if (isDeleted[v]) {
            continue;
        }
        solve(v, c);
    }
}


int main() {
    cin >> n;
    int x, y;
    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    solve();
    for (int i = 1; i <= n; i++) {
        cout << ANS[i] << " ";
    }
}