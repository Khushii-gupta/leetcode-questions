class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> suf(n + 1, m);

        int j = m - 1;

        for (int i = n - 1; i >= 0; i--) {
            if (j >= 0 && word1[i] == word2[j]) {
                j--;
            }
            suf[i] = j + 1;
        }

        vector<int> ans;

        int j2 = 0;
        bool changed = false;

        for (int i = 0; i < n && j2 < m; i++) {

            // Exact match
            if (word1[i] == word2[j2]) {
                ans.push_back(i);
                j2++;
            }
            else {
                // We can change at most one character.
                if (changed)
                    continue;


                if (j2 + 1 + (m - suf[i + 1]) >= m) {
                    ans.push_back(i);
                    j2++;
                    changed = true;
                }
            }
        }

        if (ans.size() != m)
            return {};

        return ans;
    }
};