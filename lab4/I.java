import java.io.*;
import java.util.InputMismatchException;


public class I {
    public static void main(String[] args) throws Exception {
        MyScanner in = new MyScanner(System.in);
        Print pr = new Print(System.out);
        int n = in.nextInt();
        int start, end, x, h;
        Tree tree = new Tree(n);
        String s;
        while (true) {
            s = in.next();
            if (s.equals("E")) break;
            if (s.equals("Q")) {
                h = in.nextInt();
                pr.printLine(tree.get(tree.root, h) + 1);
            } else {
                start = in.nextInt();
                end = in.nextInt();
                x = in.nextInt();
                tree.update(tree.root, start - 1, end - 1, x);
            }
        }
        pr.close();
    }
}
class Node {
    int max;
    int sum;
    int upd;
    int l, r;
    Node left, right;
    static final int inf = 10000005;

    Node(int m,int s,int upd, int l, int r) {
        this.max = m;
        this.sum = s;
        this.upd = upd;
        this.l = l;
        this.r = r;
    }
}

class Tree {
    Node root;

    Tree(int n) {
        root = new Node(0,0,Node.inf, 0 , n - 1);
    }

    void ext(Node t) {
        if (t.left == null)
            t.left = new Node(0,0,t.upd,t.l, (t.r+t.l)/2);
        if (t.right == null)
            t.right = new Node(0,0,t.upd,(t.r+t.l)/2 + 1,t.r);
    }

    Node trueVal(Node t) {
        if (t.upd == Node.inf)
            return t;
        return new Node(Math.max(0,(t.r - t.l + 1) * t.upd),(t.r - t.l + 1) * t.upd,Node.inf,t.l,t.r);
    }

    void push(Node t) {
        if (t.l == t.r) {
            t.sum = t.upd;
            t.upd = Node.inf;
            t.max = Math.max(0,t.sum);
            return;
        }
        t.left.upd = t.upd;
        t.right.upd = t.upd;
        t.max = Math.max((t.r - t.l + 1) * t.upd,0);
        t.sum = (t.r - t.l + 1) * t.upd;
        t.upd = Node.inf;
    }

    void update(Node t,int L ,int R, int x) {
        ext(t);
        if (t.l > R || t.r < L)
            return;
        if (t.l >= L && t.r <= R)
            t.upd = x;
        else {
            if (t.upd != Node.inf) push(t);
            if(!(t.left.l > R) && !(t.left.r < L)) update(t.left, L, R, x);
            if(!(t.right.l > R) && !(t.right.r < L)) update(t.right, L, R, x);
            t.sum = trueVal(t.right).sum + trueVal(t.left).sum;
            t.upd = Node.inf;
            t.max = Math.max(trueVal(t.left).max,trueVal(t.left).sum + trueVal(t.right).max);
        }
    }
    int get(Node t, int h) {
        ext(t);
        if (t.r == t.l) {
            if (trueVal(t).max > h) {
                return t.r-1;
            }
            else {
                return t.r;
            }
        }
        if (t.upd != Node.inf) push(t);
        if (trueVal(t.left).max > h) {
            return get(t.left, h);
        }
        else {
            return get(t.right, h - trueVal(t.left).sum);
        }
    }
}

 class MyScanner {
    private InputStream stream;
    private byte[] buf = new byte[1024];
    private int curChar;
    private int numChars;
    private SpaceCharFilter filter;

    public MyScanner(InputStream stream) {
        this.stream = stream;
    }

    public int read() {
        if (numChars == -1) {
            throw new InputMismatchException();
        }
        if (curChar >= numChars) {
            curChar = 0;
            try {
                numChars = stream.read(buf);
            } catch (IOException e) {
                throw new InputMismatchException();
            }
            if (numChars <= 0) {
                return -1;
            }
        }
        return buf[curChar++];
    }

    public int nextInt() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        int res = 0;
        do {
            if (c < '0' || c > '9') {
                throw new InputMismatchException();
            }
            res *= 10;
            res += c - '0';
            c = read();
        } while (!isSpaceChar(c));
        return res * sgn;
    }

    public String readString() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        StringBuilder res = new StringBuilder();
        do {
            res.appendCodePoint(c);
            c = read();
        } while (!isSpaceChar(c));
        return res.toString();
    }



    public boolean isSpaceChar(int c) {
        if (filter != null) {
            return filter.isSpaceChar(c);
        }
        return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
    }

    public String next() {
        return readString();
    }

    public interface SpaceCharFilter {
        public boolean isSpaceChar(int ch);
    }
}

 class Print {
    private final PrintWriter writer;

    public Print (OutputStream outputStream) {
        writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
    }


    public void print(Object... objects) {
        for (int i = 0; i < objects.length; i++) {
            if (i != 0) {
                writer.print(' ');
            }
            writer.print(objects[i]);
        }
        writer.flush();
    }

    public void printLine(Object... objects) {
        print(objects);
        writer.println();
        writer.flush();
    }

    public void close() {
        writer.close();
    }


}