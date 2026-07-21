class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        string t = "1" + s + "1";

        int ones = 0;
        for (char ch : s) {
            if (ch == '1') ones++;
        }

        int ans = ones;

        int n = t.size();
        int i = 0;

        while (i < n) {
            if (t[i] == '1') {
                int start = i;

                // Find the end of current block of 1s
                while (i < n && t[i] == '1') i++;

                int oneEnd = i;

                // This 1-block must be surrounded by 0s
                if (start > 0 && oneEnd < n &&
                    t[start - 1] == '0' && t[oneEnd] == '0') {

                    int leftZero = 0, j = start - 1;
                    while (j >= 0 && t[j] == '0') {
                        leftZero++;
                        j--;
                    }

                    int rightZero = 0;
                    j = oneEnd;
                    while (j < n && t[j] == '0') {
                        rightZero++;
                        j++;
                    }

                    ans = max(ans, ones + leftZero + rightZero);
                }
            } else {
                i++;
            }
        }
        return ans;
    }
};