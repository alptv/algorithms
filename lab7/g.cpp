#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

vector <vector <int>> g_in;
vector <vector <int>> g_out;

vector <int> tin;
bool used[2005];

int comp[2005];

map <string, int> friends;
vector <string> numbFriends;

void timeIn(int v) {
    used[v] = true;
    for (int u : g_out[v]) {
        if (!used[u])
            timeIn(u);
    }
    tin.push_back(v);
}

void dfs(int v, int c) {
    comp[v] = c;
    for (int u : g_in[v]) {
        if (comp[u] == 0)
            dfs(u, c);
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    string x;
    string y;
    g_in.assign(2*n, {});
    g_out.assign(2*n, {});
    string s;
    for (int i = 0; i < 2*n; i+=2) {
        cin >> s;
        friends[s] = i;
        numbFriends.push_back(s);
        numbFriends.emplace_back("");
    }

    for (int i = 0; i < m; i++) {
        cin >> x >> y >> y;
        char type1 ,type2;
        type1 = x[0];
        type2 = y[0];
        x = x.substr(1);
        y = y.substr(1);
        int ind1 = friends[x];
        int ind2 = friends[y];
        if (type1 == '+' && type2 == '+') {
            g_out[ind1].push_back(ind2);
            g_out[ind2 + 1].push_back(ind1 + 1);
            g_in[ind2].push_back(ind1);
            g_in[ind1 + 1].push_back(ind2 + 1);
        }
        if (type1 == '-' && type2 == '-') {
            g_out[ind1 + 1].push_back(ind2 + 1);
            g_out[ind2].push_back(ind1);
            g_in[ind2 + 1].push_back(ind1 + 1);
            g_in[ind1].push_back(ind2);
        }

        if (type1 == '+' && type2 == '-') {
            g_out[ind1].push_back(ind2 + 1);
            g_out[ind2].push_back(ind1 + 1);
            g_in[ind2 + 1].push_back(ind1);
            g_in[ind1 + 1].push_back(ind2);
        }
        if (type1 == '-' && type2 == '+') {
            g_out[ind1 + 1].push_back(ind2);
            g_out[ind2 + 1].push_back(ind1);
            g_in[ind1].push_back(ind2 + 1);
            g_in[ind2].push_back(ind1 + 1);
        }
    }

    for (int i = 0; i < 2*n; i++) {
        if (!used[i]) {
            timeIn(i);
        }
    }
    int c = 0;
    for (int i = 2*n-1; i >= 0; i--){
        if (comp[tin[i]] == 0) {
            dfs(tin[i], ++c);
        }
    }
    for (int i = 0; i < 2*n; i+=2) {
        if (comp[i] == comp[i + 1]) {
            cout << -1;
            return 0;
        }
    }
    int count = 0;
    vector <int> ans(2*n, 0);
    for (int i = 0; i < 2*n; i+=2) {
        if (comp[i] < comp[i + 1]) {
            ans[i] = 0;
        } else {
            count++;
            ans[i] = 1;
        }
    }
    cout << count << "\n";
    for (int i = 0; i < 2*n; i+= 2) {
        if (ans[i] == 1) {
            cout << numbFriends[i] << '\n';
        }
    }
}
 