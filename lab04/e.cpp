#include <iostream>
#include <string>
#include "vector"
#include "string"
using namespace std;


struct Node {
    int one;
    int two;
    int three;
    int four;

    Node() {
        one = 1;
        two = 0;
        three = 0;
        four = 1;
    }
};

int ost(int a, int mod) {
    if (a < mod) return a;
    else return a % mod;
}

const Node zero;


Node t[900000];
Node input[300000];



Node mov(Node a, Node b, int r) {
    if (a.one == 1 && a.two == 0 && a.three == 0 && a.four == 1) {
        return b;
    }
    if (b.one == 1 && b.two == 0 && b.three == 0 && b.four == 1) {
        return a;
    }
    int x = ost(ost(a.one*b.one, r)  + ost(a.two * b.three,r),r);
    int y = ost(ost(a.one * b.two,r) + ost(a.two * b.four,r),r);
    int z = ost(ost(a.three*b.one,r) + ost(a.four*b.three,r),r);
    int d = ost(ost(a.three * b.two,r) + ost(a.four*b.four, r),r);
    Node res;
    res.one = x; res.two = y; res.three = z; res.four = d;
    return res;

}

void build(int l, int r, int v, int mod) {
    if (l == r) {
        t[v] = input[r];
        return;
    }
    int m = (l+r)/2;
    build(l,m,2*v+1,mod);
    build(m+1,r,2*v+2,mod);
    t[v] = mov(t[2 * v +1] ,t[2*v+2], mod);
}

Node get(int L, int R,int l , int r, int v, int mod) {
    if (l > R || r < L) {
        return zero ;
    }
    if (l >= L && r <= R) {
        return t[v];
    }
    int m = (l + r) / 2;
    Node a = get(L, R, l , m, 2 * v + 1, mod);
    Node b = get(L, R, m + 1 , r, 2 * v + 2, mod);
    return mov(a,b, mod);

}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
    int n, mod,m;
    scanf("%d",&mod);
    scanf("%d",&n);
    scanf("%d",&m);
    for (int i = 0; i < n; i++) {
        int a,b,c,d;
        scanf("%d",&a);
        scanf("%d",&b);
        scanf("%d",&c);
        scanf("%d",&d);
        a = ost(a,mod);
        b = ost(b,mod);
        c = ost(c,mod);
        d = ost(d,mod);
        Node res;
        res.one = a; res.two = b; res.three = c; res.four = d;
        input[i] = res;
    }
    
   build(0,n - 1,0,mod);

    for (int i = 0; i < m; i++) {
        int L, R;
        scanf("%d",&L);
        scanf("%d",&R);
        Node ans = get(L - 1,R - 1,0,n-1,0,mod);
        printf("%d", ans.one);
        printf("%s", " ");
        printf("%d", ans.two);
        printf("%c", '\n');
        printf("%d", ans.three);
        printf("%s", " ");
        printf("%d", ans.four);
        printf("%c", '\n');
        printf("%c", '\n');
    }
}