class Solution {
public:
    static constexpr long long CAP = 1000001LL;

    long long binomCap(int n, int r) {
        r = min(r, n - r);

        long long res = 1;

        for (int i = 1; i <= r; i++) {
            long long num = n - r + i;
            long long den = i;

            long long g = gcd(num, den);
            num /= g;
            den /= g;

            g = gcd(res, den);
            res /= g;
            den /= g;

            if (res > CAP / num) return CAP;
            res *= num;

            res /= den;

            if (res >= CAP) return CAP;
        }

        return min(res, CAP);
    }

    long long countCap(const vector<int>& cnt) {
        int rem = 0;
        for (int x : cnt) rem += x;

        long long res = 1;

        for (int c : cnt) {
            if (c == 0) continue;

            long long ways = binomCap(rem, c);

            if (res > CAP / ways) return CAP;
            res *= ways;

            if (res >= CAP) return CAP;

            rem -= c;
        }

        return min(res, CAP);
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char ch : s) freq[ch - 'a']++;

        vector<int> half(26, 0);
        string mid = "";

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] % 2) mid.push_back(char('a' + i));
        }

        int m = 0;
        for (int x : half) m += x;

        vector<long double> logFact(m + 1, 0);
        for (int i = 1; i <= m; i++)
            logFact[i] = logFact[i - 1] + log((long double)i);

        long double logF = logFact[m];
        for (int c : half) logF -= logFact[c];

        long long total = countCap(half);
        if (total < k) return "";

        bool exactKnown = (total < CAP);
        long long exactF = total;

        string left;
        int rem = m;
        const long double LOG_CAP = log((long double)CAP);

        while (rem > 0) {
            for (int ch = 0; ch < 26; ch++) {
                if (half[ch] == 0) continue;

                long double logCandidate =
                    logF + log((long double)half[ch]) - log((long double)rem);

                bool candidateLarge = (logCandidate > LOG_CAP + 1e-12L);

                long long ways;

                if (candidateLarge) {
                    ways = CAP; // definitely > 1e6
                } else {
                    if (exactKnown) {
                        ways = (exactF * half[ch]) / rem;
                    } else {
                        half[ch]--;

                        ways = countCap(half);

                        half[ch]++;
                    }
                }

                if (k <= ways) {
                    left.push_back(char('a' + ch));

                    if (!candidateLarge) {
                        exactKnown = true;
                        exactF = ways;
                    } else {
                        exactKnown = false;
                    }

                    logF = logCandidate;

                    half[ch]--;
                    rem--;
                    break;
                } else {
                    k -= (int)ways;
                }
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};