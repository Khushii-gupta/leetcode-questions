class Solution {
public:
    struct Node {
        int len;
        int pref;
        int suff;
        int best;
        char leftChar;
        char rightChar;

        Node() {
            len = pref = suff = best = 0;
            leftChar = rightChar = '#';
        }
    };

    vector<Node> seg;
    string s;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;

        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        // Initially, best is inside either child
        res.best = max(a.best, b.best);

        // Prefix
        res.pref = a.pref;

        if (a.pref == a.len && a.rightChar == b.leftChar) {
            res.pref = a.len + b.pref;
        }

        // Suffix
        res.suff = b.suff;

        if (b.suff == b.len && a.rightChar == b.leftChar) {
            res.suff = b.len + a.suff;
        }

        // Middle substring crossing the boundary
        if (a.rightChar == b.leftChar) {
            res.best = max(res.best, a.suff + b.pref);
        }

        return res;
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            seg[idx].len = 1;
            seg[idx].pref = 1;
            seg[idx].suff = 1;
            seg[idx].best = 1;
            seg[idx].leftChar = s[l];
            seg[idx].rightChar = s[l];
            return;
        }

        int mid = (l + r) / 2;

        build(2 * idx, l, mid);
        build(2 * idx + 1, mid + 1, r);

        seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
    }

    void update(int idx, int l, int r, int pos, char c) {
        if (l == r) {
            seg[idx].leftChar = c;
            seg[idx].rightChar = c;
            seg[idx].len = 1;
            seg[idx].pref = 1;
            seg[idx].suff = 1;
            seg[idx].best = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid) {
            update(2 * idx, l, mid, pos, c);
        } else {
            update(2 * idx + 1, mid + 1, r, pos, c);
        }

        seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
    }

    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {
        this->s = s;

        int n = s.size();

        seg.resize(4 * n + 5);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryCharacters.size(); i++) {
            int pos = queryIndices[i];
            char c = queryCharacters[i];

            // Update the original string too
            s[pos] = c;
            this->s = s;

            update(1, 0, n - 1, pos, c);

            ans.push_back(seg[1].best);
        }

        return ans;
    }
};