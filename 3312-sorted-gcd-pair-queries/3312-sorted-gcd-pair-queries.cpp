class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<long long> freq(mx + 1, 0);

        for (int x : nums)
            freq[x]++;

        // cnt[d] = numbers divisible by d
        vector<long long> cnt(mx + 1, 0);

        for (int d = 1; d <= mx; d++) {
            for (int m = d; m <= mx; m += d)
                cnt[d] += freq[m];
        }

        // exact[d] = pairs having gcd exactly d
        vector<long long> exact(mx + 1, 0);

        for (int d = mx; d >= 1; d--) {
            long long pairs = cnt[d] * (cnt[d] - 1) / 2;

            for (int m = 2 * d; m <= mx; m += d)
                pairs -= exact[m];

            exact[d] = pairs;
        }

        // prefix counts
        vector<long long> pref(mx + 1, 0);

        for (int d = 1; d <= mx; d++)
            pref[d] = pref[d - 1] + exact[d];

        vector<int> ans;

        for (long long q : queries) {
            // q is 0-based index
            long long target = q + 1;

            int l = 1, r = mx;

            while (l < r) {
                int mid = (l + r) / 2;

                if (pref[mid] >= target)
                    r = mid;
                else
                    l = mid + 1;
            }

            ans.push_back(l);
        }

        return ans;
    }
};