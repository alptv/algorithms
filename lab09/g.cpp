#include <utility>
#include <queue>
#include <iostream>
#include <vector>
#include <map>

using  namespace std;


struct AhoCorasick {
    struct node {
        node *parent;
        node* suffixLink;
        vector<node*> children;
        node* near;
        int isTerminal = -1;
        bool used;

        explicit node(node *parent = nullptr, vector<node*> children = vector<node*>(26, nullptr), node *suff = nullptr)
                : parent(parent), children(move(children)), suffixLink(suff), isTerminal(-1), near(nullptr), used(false) {}

    };

    node* root;
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
            if (v -> suffixLink -> isTerminal != -1) {
                v -> near = v -> suffixLink;
            } else {
                v -> near = v -> suffixLink -> near;
            }
        }
    }

    void buildLinks() {
        queue <node*> q;
        q.push(root);
        while (!q.empty()) {
            node *v = q.front();
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

    vector<bool> contains(string &s) {
        vector<bool> containPattern(patternsCount, false);
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
            if (!currentNode->used) {
                currentNode -> used = true;
                if (currentNode->isTerminal != -1) {
                    containPattern[currentNode->isTerminal] = true;
                }
                node *near = currentNode->near;
                while (near != nullptr) {
                    containPattern[near->isTerminal] = true;
                    near = near->near;
                }
            }
        }
        return  containPattern;
    }


};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("search4.out", "w", stdout);
    freopen("search4.in", "r", stdin);
    int n; cin >> n;
    AhoCorasick a;
    string s;
    map<int,int> eq; int j = 0;
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
    auto x = a.contains(s);
    for (int i = 0; i < n; i++) {
        if (x[eq[i]]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}