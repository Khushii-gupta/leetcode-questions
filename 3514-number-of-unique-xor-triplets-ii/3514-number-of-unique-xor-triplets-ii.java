class Solution {
    public int uniqueXorTriplets(int[] nums) {
        int MAX = 2048; // nums[i] <= 1500, so XOR values are < 2048

        boolean[] present = new boolean[MAX];

        // Only distinct values matter because indices can repeat (i <= j <= k)
        for (int x : nums) {
            present[x] = true;
        }

        // All possible XORs of two elements
        boolean[] pairXor = new boolean[MAX];

        for (int a = 0; a < MAX; a++) {
            if (!present[a]) continue;

            for (int b = 0; b < MAX; b++) {
                if (present[b]) {
                    pairXor[a ^ b] = true;
                }
            }
        }

        // All possible XORs of three elements
        boolean[] tripletXor = new boolean[MAX];

        for (int x = 0; x < MAX; x++) {
            if (!pairXor[x]) continue;

            for (int y = 0; y < MAX; y++) {
                if (present[y]) {
                    tripletXor[x ^ y] = true;
                }
            }
        }

        int answer = 0;
        for (boolean possible : tripletXor) {
            if (possible) answer++;
        }

        return answer;
    }
}