#include <iostream>
#include "cmath"
#include <algorithm>

using namespace std;

const long long inf = (long long)10e10;
long long t[(int)(4e5) + 10];
long long tSet[(int)(4e5) + 10];


long long min (long long a, long long b) {
    return a > b ? b : a;
}

struct Node {
    int left;
    int right;
    int min;
};

bool operator < (Node a, Node b) {
    return a.min < b.min;
}

Node inp[(int)(1e5) + 10];

long long val(int v) {
    if (tSet[v] == inf) {
        return t[v];
    }
    return tSet[v];
}

void push(int v, int l,int r) {
    if (l == r) {
        if (tSet[v] == inf) return;
        t[v] = val(v);
        tSet[v] = inf;
        return;
    }
    if (tSet[v] == inf) return;
    t[v] = val(v);
    tSet[2*v+1] = tSet[v];
    tSet[2*v+2] = tSet[v];
    tSet[v] = inf;
}

long long get(int L, int R, int l, int r , int v) {
    if (L > r || R < l) {
        return inf;
    }
    if (l >= L && r <= R) {
        return val(v);
    }
    push(v,l,r);
    int m = (l + r) / 2;
    long long a = get(L,R,l,m,2*v+1);
    long long b = get(L,R,m+1,r,2*v+2);
    return min(a,b);
}

void set(int L, int R, int l, int r , int v, int x) {
    if (L > r || R < l) {
        return;
    }
    if (l >= L && r <= R) {
        tSet[v] = x;
        return;
    }
    push(v,l,r);
    int m = (l + r) /2;
    set(L,R,l,m,2*v+1,x);
    set(L,R,m+1,r,2*v+2,x);
    t[v] = min(val(2*v+1),val(2*v+2));
}

int main() {
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    int n,m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int l, r, q;
        scanf("%d%d%d", &l, &r, &q);
        Node a;
        a.left = l - 1;
        a.right = r - 1;
        a.min = q;
        inp[i] = a;
    }
    sort(inp,inp + m);
    for (int i = 0; i < m; i++) {
        set(inp[i].left,inp[i].right,0,n-1,0,inp[i].min);
    }
    for (int i = 0; i < m; i++) {
        long long a = get(inp[i].left,inp[i].right,0,n-1,0);
        if (a != inp[i].min) {
            cout << "inconsistent";

            return 0;
        }
    }
    cout << "consistent" << endl;
    for (int i = 0; i < n; i++) {
        cout << get(i,i,0,n-1,0) << " ";
    }
}