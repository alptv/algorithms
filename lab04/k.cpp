#include <iostream>
#include <string>
using namespace std;

int t[4 * 100005];


int get(int L, int R,int l , int r, int v) {
    if (l > R || r < L) {
        return 0;
    }
    if (l >= L && r <= R) {
        return t[v];
    }
    int m = (l + r) / 2;
    int a = get(L, R, l , m, 2 * v + 1);
    int b = get(L, R, m + 1 , r, 2 * v + 2);
    return a + b;

}

void set(int i, int x, int v, int l, int r) {
    if (l == r) {
        t[v] = x;
        return;
    }
    int m = (l+r) / 2;
    if (i <= m) {
        set(i,x, 2 * v + 1, l, m);
    } else {
        set(i,x,2 * v + 2,m + 1,r);
    }
    t[v] = t[2 * v + 1] + t[2 * v + 2];
}

int findZeroInAll(int l, int r, int v, int k) {
    if (t[v] == r - l  + 1) {
        return -1;
    }
    if (l == r) {
        return r;
    }
    int m = (l + r)/2;
    if (k <= (m - l + 1 - t[2*v + 1])) {
        findZeroInAll(l,m, 2*v+1,k);
    } else {
        findZeroInAll(m+1,r,2*v+2,k - ((m - l + 1 - t[2*v + 1])));
    }
}

int findLeft(int L, int R,int n) {
    int count = get(L, R,0,n-1,0);
    if (count == R - L + 1) return -1;
    return findZeroInAll(0,n - 1,0,1);
}

int findRight(int L, int R, int n) {
    if (get(L,R,0,n-1,0) == R - L  + 1) {
        return  -1;
    }
    int count = get(0, L-1,0,n - 1,0);
    count = L - count;
    count++;
    return findZeroInAll(0,n-1,0,count);
}

int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
    int n,m;
    scanf("%d%d", &n, &m);
    string s;
    for (int i = 0; i < m; i++) {
        cin >> s;
        if (s == "exit") {
            int t;
            scanf("%d", &t);
            set(t- 1,0,0,0,n-1);
        } else {
            int a,c;
            scanf("%d", &a);
            c = get(a-1,a-1,0,n-1,0);
            if (c == 1) {
                c = findRight(a,n-1,n);
                if (c != -1) {
                    printf("%d",c+1);
                     set(c,1,0,0,n-1);
                    printf("%s", "\n");
                } else {
                    c= findLeft(0,a-2,n);
                    set(c,1,0,0,n-1);
                    printf("%d",c+1);
                    printf("%s", "\n");
                }
            } else {
                set(a-1,1,0,0,n-1);
                printf("%d", a);
                printf("%s", "\n");
                
            }

        }
    }
}