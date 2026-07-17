class Solution {
public:
    static bool comparator(pair<char, int> &a, pair<char, int> &b) {
        return a.second > b.second;
    }

    string frequencySort(string s) {
        unordered_map<char, int> mp;

        for (char ch : s) {
            mp[ch]++;
        }

        vector<pair<char, int>> freq;
        for (auto &it : mp) {
            freq.push_back(it);
        }
        sort(freq.begin(), freq.end(), comparator);
        string ans = "";
        for (auto &it : freq) {
            ans.append(it.second, it.first);
        }

        return ans;
    }
};