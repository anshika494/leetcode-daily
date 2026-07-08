class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct Node {
        long long val, sum;
        int len;
        Node(long long v = 0, long long s = 0, int l = 0)
            : val(v), sum(s), len(l) {}
    };

    vector<Node> seg;
    vector<long long> pow10;
    string str;

    Node merge(Node &a, Node &b) {
        return Node(
            (a.val * pow10[b.len] + b.val) % MOD,
            a.sum + b.sum,
            a.len + b.len
        );
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            int d = str[l] - '0';
            if (d == 0)
                seg[idx] = Node(0, 0, 0);
            else
                seg[idx] = Node(d, d, 1);
            return;
        }

        int mid = (l + r) / 2;
        build(idx * 2, l, mid);
        build(idx * 2 + 1, mid + 1, r);
        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[idx];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(idx * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(idx * 2 + 1, mid + 1, r, ql, qr);

        Node left = query(idx * 2, l, mid, ql, qr);
        Node right = query(idx * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        str = s;
        int n = s.size();

        pow10.assign(n + 1, 1);
        for (int i = 1; i <= n; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        seg.assign(4 * n + 5, Node());
        build(1, 0, n - 1);

        vector<int> ans;
        for (auto &q : queries) {
            Node cur = query(1, 0, n - 1, q[0], q[1]);
            ans.push_back((cur.val * cur.sum) % MOD);
        }

        return ans;
    }
};
