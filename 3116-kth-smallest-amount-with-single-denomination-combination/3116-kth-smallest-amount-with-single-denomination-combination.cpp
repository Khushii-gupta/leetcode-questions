class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        // Remove coins that are multiples of another smaller coin
        sort(coins.begin(), coins.end());

        vector<int> v;
        for (int c : coins) {
            bool redundant = false;

            for (int x : v) {
                if (c % x == 0) {
                    redundant = true;
                    break;
                }
            }

            if (!redundant)
                v.push_back(c);
        }

        coins = v;

        int n = coins.size();

        // Calculate LCM safely
        auto lcm_limit = [](long long a, long long b, long long limit) {
            long long g = std::gcd(a, b);

            // Avoid overflow
            if (a / g > limit / b)
                return limit + 1;

            return (a / g) * b;
        };

        // Count how many numbers <= x are divisible by
        // at least one coin.
        auto count = [&](long long x) {
            long long total = 0;

            for (int mask = 1; mask < (1 << n); mask++) {
                long long lcm = 1;
                int bits = 0;
                bool tooLarge = false;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        bits++;

                        lcm = lcm_limit(lcm, coins[i], x);

                        if (lcm > x) {
                            tooLarge = true;
                            break;
                        }
                    }
                }

                if (tooLarge)
                    continue;

                long long cnt = x / lcm;

                if (bits % 2 == 1)
                    total += cnt;
                else
                    total -= cnt;
            }

            return total;
        };

        // Binary search for the smallest x
        // such that there are at least k valid amounts <= x.
        long long low = 1;
        long long high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (count(mid) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};