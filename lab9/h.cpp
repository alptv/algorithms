#include <utility>
#include <queue>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
 
using  namespace std;
 
 
struct AhoCorasick {
    struct node {
        node *parent;
        node* suffixLink;
        vector<node*> children;
        int isTerminal = -1;
        int count = 0;
 
        explicit node(node *parent = nullptr, vector<node*> children = vector<node*>(26, nullptr), node *suff = nullptr)
                : parent(parent), children(move(children)), suffixLink(suff), isTerminal(-1), count(0) {}
 
    };
 
    node* root;
    stack<node*> st;
    int patternsCount = 0;
 
    AhoCorasick() {
        root = new node();
        patternsCount = 0;
    }
 
    int getIndex(char c) {
        return (int) c - 'a';
    }
 
    void addPattern(string &p) {
        node * currentNode = root;
        for (int i = 0; i < p.size(); i++) {
            char c = p[i];
            if (currentNode->children[getIndex(c)] == nullptr) {
                currentNode->children[getIndex(c)] = new node(currentNode);
                currentNode->children[getIndex(c)]->parent = currentNode;
                currentNode = currentNode->children[getIndex(c)];
            } else {
                currentNode = currentNode -> children[getIndex(c)];
            }
            if (i == p.size() - 1) {
                currentNode->isTerminal = patternsCount;
            }
        }
        patternsCount++;
    }
 
    void link(node* v, int charIndex) {
        node * p = v -> parent;
        p = p -> suffixLink;
        while(p != nullptr && p -> children[charIndex] == nullptr) {
            p = p -> suffixLink;
        }
        if (p == nullptr) {
            v -> suffixLink = root;
        } else {
            v -> suffixLink = p -> children[charIndex];
        }
    }
 
    void buildLinks() {
        queue <node*> q;
        q.push(root);
 
        while (!q.empty()) {
            node *v = q.front();
            st.push(v);
            q.pop();
            for (int i = 0; i <  v->children.size(); i++) {
                node* child = v -> children[i];
                if (child != nullptr) {
                    q.push(child);
                    link(child, i);
                }
            }
        }
    }
 
    int has(string &p) {
        node * currentNode = root;
        int ans;
        for (char c : p) {
            if (currentNode->children[getIndex(c)] == nullptr) {
                return -1;
            } else {
                currentNode = currentNode -> children[getIndex(c)];
                ans = currentNode->isTerminal;
            }
        }
        return ans;
    }
 
    void contains(string &s) {
        node * currentNode = root;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (currentNode -> children[getIndex(s[i])] != nullptr) {
                currentNode = currentNode -> children[getIndex(s[i])];
            } else {
                node *p = currentNode -> suffixLink;
                while (p != nullptr && p -> children[getIndex(s[i])] == nullptr) {
                    p = p -> suffixLink;
                }
                if (p == nullptr) {
                    currentNode = root;
                } else {
                    currentNode = p -> children[getIndex(s[i])];
                }
            }
            currentNode->count++;
        }
    }
 
    vector<int> calc() {
        vector<int> c(patternsCount);
        while (!st.empty()) {
            node *v = st.top();
            st.pop();
            if (v->isTerminal != -1) {
                c[v->isTerminal] += v -> count;
            }
            if (v -> suffixLink) {
                v -> suffixLink -> count += v->count;
            }
        }
        return c;
    }
 
};
 
 
int main() {
   freopen("search5.out", "w", stdout);
    freopen("search5.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    AhoCorasick a;
    string s;
    map<int,int> eq;
    for (int i = 0,j = 0; i < n; i++) {
        cin >> s;
        int x = a.has(s);
        if (x == -1) {
            a.addPattern(s);
            eq[i] = j;
            j++;
        } else {
            eq[i] = x;
        }
    }
    cin >> s;
    a.buildLinks();
    a.contains(s);
    auto x = a.calc();
    for (int i = 0; i < n; i++) {
        cout << x[eq[i]] << '\n';
    }
}