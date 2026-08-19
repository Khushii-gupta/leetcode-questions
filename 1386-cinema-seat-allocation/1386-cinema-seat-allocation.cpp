class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        // Mark reserved seats for each row
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            // We only care about seats 2 to 9
            if (col >= 2 && col <= 9) {
                mp[row] |= (1 << col);
            }
        }

        // Initially, every row can accommodate 2 families
        long long ans = 2LL * n;

        for (auto &[row, mask] : mp) {
            // Since this row has reservations, remove the default 2 families
            ans -= 2;

            // Check seats 2,3,4,5
            bool left = (mask & (1 << 2)) ||
                        (mask & (1 << 3)) ||
                        (mask & (1 << 4)) ||
                        (mask & (1 << 5));

            // Check seats 6,7,8,9
            bool right = (mask & (1 << 6)) ||
                         (mask & (1 << 7)) ||
                         (mask & (1 << 8)) ||
                         (mask & (1 << 9));

            // Check seats 4,5,6,7
            bool middle = (mask & (1 << 4)) ||
                          (mask & (1 << 5)) ||
                          (mask & (1 << 6)) ||
                          (mask & (1 << 7));

            if (!left && !right) {
                // Both outer groups are available
                ans += 2;
            }
            else if (!left || !right || !middle) {
                // At least one group is available
                ans += 1;
            }
        }

        return (int)ans;
    }
};