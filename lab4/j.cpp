#include <iostream>
#include <string>

using namespace std;

int inf = (int)1e8;

int max(int a, int b) {
    return a > b ? a : b;
}

int min (int a, int b) {
    return a > b ? b : a;
}
struct Node {
    int high;
    int index;
    int upd;
};
Node t[4000000 + 5];
Node trueVal(int v){
    if (t[v].upd == inf) {
        return t[v];
    } else {
        Node b;
        b.high = max(t[v].high, t[v].upd);
        b.index = t[v].index;
        b.upd = inf;
        return b;
    }

}

void build(int l, int r, int v) {
    if (l == r) {
        t[v].high = 0;
        t[v].index = l;
        t[v].upd = inf;
        return;
    }
    int m = (l + r) / 2;
    build(l,m,2*v+1);
    build(m+1,r,2*v+2);
    if (t[2*v+1].high < t[2*v+2].high) t[v] = t[2*v+1];
    else t[v] = t[2*v+2];
}



void push(int v, int l,int r) {
    if (l == r) {
        if (t[v].upd == inf) return;
        t[v] = trueVal(v);
        return;
    }
    if (t[v].upd == inf) return;
    if (t[2 * v + 1].upd == inf) {
    t[2 * v + 1].upd = t[v].upd;
    } else { t[2 * v + 1].upd =max (t[v].upd, t[2 * v + 1].upd);}
    if (t[2 * v + 2].upd == inf) {
    t[2 * v + 2].upd = t[v].upd;
    } else { t[2 * v + 2].upd =max (t[v].upd, t[2 * v + 2].upd);}

    t[v] = trueVal(v);

}

Node get(int L, int R, int l, int r , int v) {
    if (L > r || R < l) {
        Node ans;
        ans.high = inf;
        ans.index = inf;
        ans.upd = inf;
        return ans;
    }
    if (l >= L && r <= R) {
        return trueVal(v);
    }
    push(v,l,r);
    int m = (l + r) / 2;
    Node a = get(L,R,l,m,2*v+1);
    Node b = get(L,R,m+1,r,2*v+2);
    if (a.high < b.high) return a;
    return b;
}

void set(int L, int R, int l, int r , int v, int x) {
    if (L > r || R < l) {
        return;
    }
    if (l >= L && r <= R) {
        if (t[v].upd == inf) { t[v].upd = x; return;}
        t[v].upd = max(t[v].upd, x);
        return;
    }
    push(v,l,r);
    int m = (l + r) /2;
    set(L,R,l,m,2*v+1,x);
    set(L,R,m+1,r,2*v+2,x);
    Node a = trueVal(2*v+1);
    Node b = trueVal(2 * v + 2);
    if (a.high < b.high) t[v] = a;
    else t[v] = b;
}


int main() {
    int n, m;
    cin >> n >> m;
    string s;
    build(0,n-1,0);
    for (int i = 0; i < m; i++) {
        cin >> s;
        if ( s == "defend") {
            int a, b,c;
            cin >> a >> b >> c;
            set(a - 1, b -1,0,n-1,0, c);
        } else {
            int a, b;

            cin >> a >> b;
            Node ans;
            ans = get (a - 1, b - 1,0,n-1, 0);
            cout << ans.high << " " << ans.index + 1 << "\n";
        }
    }

    return 0;
}