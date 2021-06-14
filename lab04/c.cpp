#include <iostream>
#include <string>
using namespace std;

long long t[4 * 100001];
long long tAdd[4 * 100001];
long long tSet[4 * 100001];
long long const inf = 1000000000000000002;

long long min(long long a, long long b) {
    return a > b ? b : a;
}

long long trueValue(long long v) {
    if (tSet[v] == inf ) {
       return t[v] + tAdd[v];
    }
    return tSet[v] + tAdd[v];
}

void build(long long l, long long r , long long v, long long a[]) {
    if (l == r) {
        t[v] = a[r];
        return;
    }
    int m = (l+r)/2;
    build(l, m , 2 * v + 1, a);
    build(m + 1, r , 2 * v + 2, a);
    t[v] = min(t[2 * v + 1] , t[2 * v + 2]);

}

void push(long long v, long long l,long long r) {
        if (l == r) {
        t[v] = trueValue(v);
        return;
    }
 
    t[v]= trueValue(v);
   
    if (tSet[v] == inf) {
    tAdd[2 * v + 1] += tAdd[v];
    tAdd[2 * v + 2] += tAdd[v];
    } else {
         tSet[2 * v + 1] = tSet[v];
    tSet[2 * v + 2] = tSet[v];
        tAdd[2 * v + 1] = tAdd[v];
    tAdd[2 * v + 2] = tAdd[v];
    }
    tAdd[v] = 0;
    tSet[v] = inf;

}


long long get(long long L, long long R,long long l , long long r, long long v) {
     if (l > R || r < L) {
            return inf;
        }
        if (l >= L && r <= R) {
            return trueValue(v);
        }
        int m = (l + r) / 2;
        push(v,l,r);
        long long a = get(L, R, l , m, 2 * v + 1);
        long long b = get(L, R, m + 1 , r, 2 * v + 2);
        return min(a,b);

}

void set(long long L, long long R,long long l , long long r, long long v, long long x) {
       if (l > R || r < L) {
            return;
        }
        if (l >= L && r <= R) {
            tSet[v] = x;
            tAdd[v] = 0;
            return;
        }
        int m = (l + r) / 2;
        push(v,l,r);
        set(L, R, l , m, 2 * v + 1,x);
        set(L, R, m + 1 , r, 2 * v + 2,x);
        t[v] = min(trueValue(2*v+1), trueValue(2*v+2));
}

void add(long long L, long long R,long long l , long long r, long long v, long long x) {
       if (l > R || r < L) {
            return;
        }
        if (l >= L && r <= R) {
            tAdd[v]+= x;
            return;
        }
        int m = (l + r) / 2;
        push(v,l,r);
        add(L, R, l , m, 2 * v + 1,x);
        add(L, R, m + 1 , r, 2 * v + 2,x);
        t[v] = min(trueValue(2*v+1),trueValue(2*v+2));
}





    int main() {
        int n;
        long long a[5000001];
        cin >> n;
        for (int i = 0; i < n; i++){
        cin >> a[i];
        }
         for (int i = 0; i < 4*100001; i++){
            tSet[i] = inf; tAdd[i] = 0;
        }
        build(0, n - 1, 0, a);
     
        string s;

        while(cin >> s) {

            long long x;
            long long y;
            long long z;
            cin >> x;
            cin >> y;
            if (s!="min") {
                cin >> z;
            }
            if (s == "set") {
                set(x -1, y- 1, 0 , n- 1,0, z);
                continue;
            }
            if (s== "add") {
                add(x -1, y- 1, 0 , n- 1,0,z );
                continue;
            }
            cout << get(x-1,y-1,0,n-1,0) << '\n';

        }
        return 0;
    }
 