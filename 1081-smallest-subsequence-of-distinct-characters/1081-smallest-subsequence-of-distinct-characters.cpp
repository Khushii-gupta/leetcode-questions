class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> freq(26, 0);
        vector<bool> used(26, false);

        for (char ch : s) {
            freq[ch - 'a']++;
        }

        string ans;

        for (char ch : s) {
            int idx = ch - 'a';
            freq[idx]--;
            if (used[idx]) {
                continue;
            }

            while (!ans.empty() &&
                   ans.back() > ch &&
                   freq[ans.back() - 'a'] > 0) {

                used[ans.back() - 'a'] = false;
                ans.pop_back();
            }

            ans.push_back(ch);
            used[idx] = true;
        }

        return ans;
    }
};