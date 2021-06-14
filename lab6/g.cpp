#include <iostream>
#include <vector>

using namespace std;

#define size sizeMy

struct SegmentTree {
    long long *t;
    long long *add;
    int size;

    SegmentTree(int n) {
        t = new long long[4 * n];
        fill(t, t + 4 * n, 0);
        add = new long long[4 * n];
        fill(add, add + 4 * n, 0);
        size = n;
    }

    void upd(int v, int L, int R, int l, int r, int val) {
        if (r < L || l > R)
            return;
        if (r <= R && l >= L) {
            add[v] += val;
            return;
        }
        int m = (l + r) >> 1;
        if (add[v] != 0) {
            t[v] += (r - l + 1)* add[v];
            if (l != r) {
                add[2 * v + 1] += add[v];
                add[2 * v + 2] += add[v];
            }
            add[v] = 0;
        }
        upd(2 * v + 1, L, R, l, m, val);
        upd(2 * v + 2, L, R, m + 1, r, val) ;
    }

    long long get(int v, int l, int r, int ind) {
        if (l == r) {
            return t[v] + add[v];
        }
        int m = (l + r) >> 1;
        if (add[v] != 0) {
            t[v] += (r - l + 1) * add[v];
            add[2 * v + 1] += add[v];
            add[2 * v + 2] += add[v];
            add[v] = 0;
        }
        if (ind <= m) {
            return get(2 * v + 1,l, m, ind);
        } else {
            return get(2 * v + 2,m + 1, r, ind);
        }
    }

    void modify(int l, int r, int val) {
        upd(0, l, r, 0, size - 1, val);
    }

    long long getValue(int ind) { return get(0, 0, size - 1, ind); }
};

const int MAXN = (int)3e5 + 5;
int const LOG = 20;
int TREE_SIZE;
vector<int> tree[MAXN];
int binaryUp[MAXN][25];
int depth[MAXN];
int head[MAXN]; 
int index[MAXN];
int wayNumber[MAXN];
int size[MAXN];
int wayLength[MAXN];
int waysCount = 0;
SegmentTree *ways[MAXN];


void buildHLD(int v, int parent) {
    size[v] = 1;
    binaryUp[v][0] = parent;
    int solid = -1;
    for (int child : tree[v]) {
        if (binaryUp[v][0] == child) {
            continue;
        }
        depth[child] = depth[v] + 1;
        buildHLD(child, v);
        size[v] += size[child];
        if (solid == -1 || size[solid] < size[child]) {
            solid = child;
        }
    }
    if (solid == -1) {
        wayNumber[v] = waysCount++;
    } else {
        wayNumber[v] = wayNumber[solid];
    }
    index[v] = wayLength[wayNumber[v]]++;
    head[wayNumber[v]] = v;
}


void buildBinaryUp() {
    for (int i  = 1; i <= LOG; i++) {
        for (int v = 0; v < TREE_SIZE; v++) {
            binaryUp[v][i] = binaryUp[binaryUp[v][i - 1]][i - 1];
        }
    }
}
int getLCA(int v1, int v2) {
    if (depth[v1] < depth[v2]) {
        int temp = v1;
        v1 = v2;
        v2 = temp;
    }
    for (int i = LOG; i >= 0; i--){
        if (depth[v1] - depth[v2] >= (1 << i)) {
            v1 = binaryUp[v1][i];
        }
    }
    if (v1 == v2) {
        return v1;
    }
    for (int i = LOG; i >= 0; i--) {
        if (binaryUp[v1][i] == binaryUp[v2][i]) {
            continue;
        }
        v1 = binaryUp[v1][i];
        v2 = binaryUp[v2][i];
    }
    return binaryUp[v1][0];
}

void buildSegmentTrees(){
    for (int i = 0; i < waysCount; i++) {
        ways[i] = new SegmentTree(wayLength[i]);
    }
}

void updateLCA(int v, int lca, int val) {
    while(wayNumber[v] != wayNumber[lca]) {
        ways[wayNumber[v]]->modify(index[v], index[head[wayNumber[v]]], val);
        v = binaryUp[head[wayNumber[v]]][0];
    }
    if (v == lca) return;
    ways[wayNumber[lca]]->modify(index[v], index[lca] - 1, val);
}
void update(int v1, int v2, int val) {
    int lca = getLCA(v1, v2);
    updateLCA(v1, lca, val);
    updateLCA(v2, lca, val);
    ways[wayNumber[lca]]->modify(index[lca],index[lca],val);
}


int main() {
     scanf("%d", &TREE_SIZE);
    int x, y;
    for (int i = 0; i < TREE_SIZE - 1; i++) {
        scanf("%d%d", &x, &y);
        tree[x - 1].push_back(y - 1);
        tree[y - 1].push_back(x - 1);
    }
    buildHLD(0, 0);
    buildBinaryUp();
    buildSegmentTrees();
    int m; scanf("%d", &m);
    char c;
    int v, u ,d;
    for (int i = 0; i < m; i++) {
        cin >> c;
        if (c == '+') {
            scanf("%d%d%d", &v, &u, &d);
            update(v - 1, u - 1, d);
        } else {
            scanf("%d", &v);
            printf("%lld\n", ways[wayNumber[v - 1]]->getValue(index[v - 1]));
        }
    }

}