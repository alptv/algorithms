#include <iostream>

using namespace std;

struct node {
    int x;
    int y;
    int size;
    //  bool isReversed;
    bool isLine;
    node *left, *right, *parent;

    node(int _x) {
        x = _x;
        y = rand();
        size = 1;
        //   isReversed = false;
        isLine = true;
        left = right = parent = nullptr;
    }
};

int max(int a, int b) {
    if (a > b) return a;
    return b;
}
int min(int a, int b) {
    if (a < b) return a;
    return b;
}

void print(node *v) {
    if (!v) return;
    print(v->left);
    cout << v ->x << " ";
    //if (v->parent) cout << v->parent->x << endl;
    // else cout << " NONE" << endl;
    print(v->right);
}


pair<node*,bool> cities[100005];

/*
bool XOR(bool a, bool b) {
return a != b;
}
*/

/*void push(node *v) {
    if (!v || !v->isReversed) return;
    if (v->left)
        v->left->isReversed = XOR(v->left->isReversed, true) ;
    if (v->right)
        v->right->isReversed   =  XOR(v->right->isReversed, true) ;
    node* l = v ->left;
    node *r = v->right;
    v->left = r;
    v ->right=l;
    v->isReversed = false;
}*/

int trueSize(node* v) {
    if (!v) return 0;
    return v->size;
}
/*
bool trueRev(node *v) {
    if (!v) return true;
    return v -> isReversed;
}*/

void upd(node *v) {
    if (v) v -> size = trueSize(v -> left) + trueSize(v -> right) + 1;
    // v -> isReversed = trueRev(v ->left) && trueRev(v -> right);
}

node * merge(node* v1, node *v2){
    if (!v1) return v2;
    if (!v2) return v1;
    // push(v1);
    // push(v2);
    if (v1 -> y > v2->y) {
        v1 -> right = merge(v1 -> right, v2);
        if (v1->right)v1 -> right ->parent = v1;
        upd(v1->right);
        upd(v1->left);
        upd(v2->right);
        upd(v2->left);
        upd(v1);
        return  v1;
    } else {
        v2 -> left = merge(v1, v2 -> left);
        if (v2->left) v2 -> left ->parent = v2;
        upd(v1->right);
        upd(v1->left);
        upd(v2->right);
        upd(v2->left);
        upd(v2);
        return v2;
    }
}

pair <node*, node*> split (node *v, int key) {
    if (!v) return make_pair(nullptr, nullptr);
    // push(v);
    if (trueSize(v -> left) + 1 < key) {
        pair<node*, node*> cur = split ( v -> right, key - trueSize(v -> left) - 1);
        v->right = cur.first;
        if (cur.first) cur.first->parent = v;
        if (cur.second) cur.second->parent = nullptr;
        upd(v);
        return make_pair(v, cur.second);
    }
    else {
        pair <node*, node*> cur = split(v ->left, key);
        v->left = cur.second;
        if(cur.second) cur.second->parent = v;
        if (cur.first) cur.first->parent = nullptr;
        upd(v);
        return make_pair(cur.first,  v);
    }
}

int getIndex(node* v) {
    int ans = trueSize(v->left);
    node* t = v ->parent;
    node* prev = v;

    while (t) {
        if (t -> right && t->right == prev) {
            ans += trueSize(t->left) + 1;
        }
        prev = t;
        t = t -> parent;
    }
    return ans + 1;
}

node* getRoot(node *v) {
    node* t = v -> parent;
    node* ans = v;

    while (t) {
        ans = t;
        t = t -> parent;
    }
    return ans;
}
int getLast(node *v) {

    int ans = trueSize(v->left)+1;
    node* t = v->right;
    while (t) {
        ans +=trueSize(t->left) + 1;
        t = t->right;
    }
    return ans;
}



void deleteRoad(int a, int b) {
    auto cityA = cities[a];
    auto cityB = cities[b];
    int aInd = getIndex(cityA.first);
    int bInd = getIndex(cityB.first);
    node* root = getRoot(cityA.first);

    if (root -> isLine) {
        split(getRoot(root), min(aInd,bInd) + 1);
    } else {
        int check = getLast(root);
        if (min(aInd,bInd) == 1 && max(aInd,bInd) == check) {
            root -> isLine = true;
            return;
        }
        pair<node*, node*> t = split(root, min(aInd,bInd) + 1);
        if (t.second) t.second -> isLine = true;
        if (t.first) t.first -> isLine = true;
        node* cur = merge(t.second, t.first);
        cur ->isLine = true;
    }
}

void reverse(node* v) {
    if (!v) return;
    node* l = v->left;
    node* r = v->right;
    v->right = l;
    v->left=r;
    reverse(v->left);
    reverse(v->right);
}

void insRoad(int a, int b) {
    if (a == b) return;
    node* rootA = getRoot(cities[a].first);
    node* rootB = getRoot(cities[b].first);
    if (rootA == rootB) {
        rootA->isLine = false;
    } else {
        int aN = getIndex(cities[a].first);
        int bN = getIndex(cities[b].first);
        if (aN == 1 && bN == 1) {

            // rootA->isReversed = true;
            reverse(rootA);
            merge(rootA, rootB);
        }
        if (aN == 1 && bN != 1) {
            merge(rootB, rootA);
        }
        if (aN != 1 && bN == 1) {
            merge(rootA, rootB);
        }
        if (aN != 1 && bN != 1) {
            reverse(rootA);
            //rootA ->isReversed = true;
            merge(rootB, rootA);
        }
    }
}


void getAns(int a, int b) {
    node* rootA = getRoot(cities[a].first);
    node* rootB = getRoot(cities[b].first);
    if (rootA != rootB) {
        cout << - 1 << endl;
        return;
    }
    else {
        if (rootA -> isLine) {

            cout << abs(getIndex(cities[b].first) - getIndex(cities[a].first)) - 1 << endl;
        }
        else {
            int last = getLast(rootA);
            // cout << last << " LAST\n";
            int x1 = getIndex(cities[b].first);
            int x2 = getIndex(cities[a].first);
            int f = min(x1,x2);
            int s = max(x1,x2);
            cout << min((s - f - 1), (last - s + f - 1)) << endl;
        }
    }

}



int main() {
    int n, m, q;
    char c;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        cities[i + 1] = make_pair(new node(i + 1), true);
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        insRoad(a, b);
    }
    for (int i = 0; i < q; i++){
        cin >> c;
        int a,b;
        if (c == '?') {
            cin >> a >> b;
            if (a == b) {
                cout << 0 << endl;
            } else {
                getAns(a, b);
            }
        }
        if (c == '+'){
            cin >> a >> b;
            insRoad(a, b);
        }
        if (c == '-') {
            cin >> a >> b;
            if (a != b) {
                deleteRoad(a, b);
            }
        }
    }
}