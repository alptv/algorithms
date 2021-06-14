import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


public class E {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int x, y;
        List <Integer>[] tree = new ArrayList[n];

        for (int i = 0; i < n - 1; i++) {
            x = in.nextInt() - 1;
            y = in.nextInt() - 1;
            if (tree[x] == null) {
                tree[x] = new ArrayList<>();
            }
            if (tree[y] == null) {
                tree[y] = new ArrayList<>();
            }
            tree[x].add(y);
            tree[y].add(x);
        }
        HeavyLightEdges hld = new HeavyLightEdges(tree);
        int m = in.nextInt();
        for (int i = 0; i < m; i++){
            x = in.nextInt() - 1;
            y = in.nextInt() - 1;
            hld.update(x, y);
        }
        System.out.println(hld.ANSWER());
    }
}



class SegmentTree {
    int[] t;
    boolean is_used[];
    final int size;

    SegmentTree(int n) {
        t = new int[4 * n];
        is_used = new boolean[4 * n];
        size = n;
        build(0, 0, n - 1);
    }
    void build(int v, int l, int r){
        if (l == r) {
            t[v] = 1;
            return;
        }
        int m = (l + r) >> 1;
        build(2*v+1, l, m);
        build(2*v+2,m+ 1, r);
        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }


    void push(int v, int l, int r) {
        if (is_used[v]) {
            is_used[2 * v + 1] = true;
            is_used[2 * v + 2] = true;
            is_used[v] = false;
            t[v] = 0;
        }
    }
    int count(int v, int l, int r) {
        if (is_used[v]) {
            return 0;
        }
        return t[v];
    }

    void upd(int v, int L, int R, int l, int r) {
        if (r < L || l > R)
            return;
        if (r <= R && l >= L) {
            is_used[v] = true;
            return;
        }
        push(v, l, r);
        int m = (l + r) >> 1;
        upd(2 * v + 1, L, R, l, m);
        upd(2 * v + 2, L, R, m + 1, r);
        t[v] = count(2 * v + 1, l, m) + count(2 * v + 2, m + 1, r);
    }

    int get(int v, int L, int R, int l, int r) {
        if (r < L || l > R)
            return 0;
        if (r <= R && l >= L) {
            return count(v, l, r);
        }
        push(v, l, r);
        int m = (l + r) >> 1;
        int a = get(2 * v + 1, L, R, l, m);
        int b = get(2 * v + 2, L, R, m + 1, r);
        return a + b;
    }

    void modify(int l, int r) {
        upd(0, l, r, 0, size - 1);
    }

    int sum(int l, int r) { return get(0, l, r, 0, size - 1); }
}

class HeavyLightEdges {
    final int ROOT = 0;
    final int LOG;
    final int TREE_SIZE;
    final List<Integer>[] tree;
    int[][] binaryUp;
    int[] depth;
    int[] head;
    int[] index; 
    int[] wayNumber; 
    int[] size;
    int[] wayLength;
    int waysCount;
    SegmentTree ways[];


    public HeavyLightEdges(final List<Integer>[] tree) {
        this.tree = tree;
        int sz = tree.length;
        this.TREE_SIZE = sz;
        this.LOG = (int)(Math.log(sz) / Math.log(2))  + 1;
        this.binaryUp = new int[sz][LOG + 1];
        this.depth = new int[sz];
        this.head = new int[sz];
        this.index = new int[sz];
        this.wayNumber = new int[sz];
        this.size = new int[sz];
        this.wayLength = new int[sz];
        this.waysCount = 0;
        buildHLD(ROOT, ROOT);
        buildBinaryUp();
        buildSegmentTrees();
    }

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
        ways = new SegmentTree[waysCount];
        for (int i = 0; i < waysCount; i++) {
            ways[i] = new SegmentTree(wayLength[i]);
        }
        ways[wayNumber[0]].modify(index[0], index[0]);
    }

    void updateLCA(int v, int lca) {
        while(wayNumber[v] != wayNumber[lca]) {
            ways[wayNumber[v]].modify(index[v], index[head[wayNumber[v]]]);
            v = binaryUp[head[wayNumber[v]]][0];
        }
        if (v == lca) return;
        ways[wayNumber[lca]].modify(index[v], index[lca] - 1);
    }
    void update(int v1, int v2) {
        int lca = getLCA(v1, v2);
        updateLCA(v1, lca);
        updateLCA(v2, lca);
    }

    int ANSWER() {
        int ans = 0;
        for (int i = 0; i < waysCount; i++) {
            ans += ways[i].sum(0, ways[i].size - 1);
        }
        return ans;
    }
}