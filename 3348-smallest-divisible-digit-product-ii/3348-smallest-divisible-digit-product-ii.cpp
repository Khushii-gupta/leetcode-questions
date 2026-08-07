class Solution {
public:
    unordered_map<int, unordered_map<int, int>> kFactorCounts = {
        {0, {}},
        {1, {}},
        {2, {{2, 1}}},
        {3, {{3, 1}}},
        {4, {{2, 2}}},
        {5, {{5, 1}}},
        {6, {{2, 1}, {3, 1}}},
        {7, {{7, 1}}},
        {8, {{2, 3}}},
        {9, {{3, 2}}}
    };

    string smallestNumber(string num, long long t) {
        auto [primeCount, isDivisible] = getPrimeCount(t);

        if (!isDivisible)
            return "-1";

        auto factorCount = getFactorCount(primeCount);

        if (sumValues(factorCount) > num.length())
            return construct(factorCount);

        auto primeCountPrefix = getPrimeCountFromString(num);

        int firstZeroIndex = num.find('0');

        if (firstZeroIndex == string::npos) {
            firstZeroIndex = num.length();

            if (isSubset(primeCount, primeCountPrefix))
                return num;
        }

        for (int i = num.length() - 1; i >= 0; i--) {

            int d = num[i] - '0';

            primeCountPrefix = subtract(primeCountPrefix,
                                        kFactorCounts[d]);

            int spaceAfterThisDigit = num.length() - 1 - i;

            if (i > firstZeroIndex)
                continue;

            for (int biggerDigit = d + 1; biggerDigit < 10; biggerDigit++) {

                auto factorsAfterReplacement =
                    getFactorCount(
                        subtract(
                            subtract(primeCount, primeCountPrefix),
                            kFactorCounts[biggerDigit]));

                if (sumValues(factorsAfterReplacement)
                    <= spaceAfterThisDigit) {

                    int fillOnes =
                        spaceAfterThisDigit -
                        sumValues(factorsAfterReplacement);

                    return num.substr(0, i) +
                           to_string(biggerDigit) +
                           string(fillOnes, '1') +
                           construct(factorsAfterReplacement);
                }
            }
        }

        auto factorsAfterExtension = getFactorCount(primeCount);

        return string(num.length() + 1 -
                          sumValues(factorsAfterExtension),
                      '1') +
               construct(factorsAfterExtension);
    }

private:
    pair<unordered_map<int, int>, bool> getPrimeCount(long long t) {

        unordered_map<int, int> cnt{
            {2, 0},
            {3, 0},
            {5, 0},
            {7, 0}
        };

        for (int p : {2, 3, 5, 7}) {
            while (t % p == 0) {
                t /= p;
                cnt[p]++;
            }
        }

        return {cnt, t == 1};
    }

    unordered_map<int, int> getPrimeCountFromString(string num) {

        unordered_map<int, int> cnt{
            {2, 0},
            {3, 0},
            {5, 0},
            {7, 0}
        };

        for (char c : num) {
            int d = c - '0';

            for (auto &[prime, freq] : kFactorCounts[d])
                cnt[prime] += freq;
        }

        return cnt;
    }

    unordered_map<int, int> getFactorCount(
        unordered_map<int, int> count) {

        unordered_map<int, int> res;

        int count8 = count[2] / 3;
        int remaining2 = count[2] % 3;

        int count9 = count[3] / 2;
        int count3 = count[3] % 2;

        int count4 = remaining2 / 2;
        int count2 = remaining2 % 2;

        int count6 = 0;

        if (count2 == 1 && count3 == 1) {
            count2 = 0;
            count3 = 0;
            count6 = 1;
        }

        if (count3 == 1 && count4 == 1) {
            count2 = 1;
            count6 = 1;
            count3 = 0;
            count4 = 0;
        }

        res[2] = count2;
        res[3] = count3;
        res[4] = count4;
        res[5] = count[5];
        res[6] = count6;
        res[7] = count[7];
        res[8] = count8;
        res[9] = count9;

        return res;
    }

    string construct(unordered_map<int, int> factors) {

        string res;

        for (int digit = 2; digit <= 9; digit++)
            res += string(factors[digit], char('0' + digit));

        return res;
    }

    bool isSubset(unordered_map<int, int> a,
                  unordered_map<int, int> b) {

        for (auto &[key, val] : a) {
            if (b[key] < val)
                return false;
        }

        return true;
    }

    unordered_map<int, int> subtract(
        unordered_map<int, int> a,
        unordered_map<int, int> b) {

        unordered_map<int, int> res = a;

        for (auto &[k, v] : b)
            res[k] = max(0, res[k] - v);

        return res;
    }

    int sumValues(unordered_map<int, int> cnt) {

        int sum = 0;

        for (auto &[k, v] : cnt)
            sum += v;

        return sum;
    }
};