class Solution {
public:
    int maxProduct(vector<int>& nums) {
         int max1 = 0, max2 = 0;

        for (int x : nums) {
            int val = x - 1;

            if (val > max1) {
                max2 = max1;
                max1 = val;
            } 
            else if (val > max2) {
                max2 = val;
            }
        }

        return max1 * max2;
    }
};