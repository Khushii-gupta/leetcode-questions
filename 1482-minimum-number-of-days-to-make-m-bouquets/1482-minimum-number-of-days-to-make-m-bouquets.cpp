class Solution {
public:
    bool possible(vector<int> &bloomDay, int m, int k, int day){
        int n = bloomDay.size();
        int cnt = 0;
        int bouquets = 0;

        for(int i = 0; i < n; i++){
            if(bloomDay[i] <= day){
                cnt++;
                if(cnt == k){
                    bouquets++;
                    cnt = 0;
                }
            }
            else{
                cnt = 0;
            }
        }
        return bouquets >= m;
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        long long total = 1LL * k * m;
        int maxBloom = *max_element(bloomDay.begin(), bloomDay.end());
        int minBloom = *min_element(bloomDay.begin(), bloomDay.end());

        int low = minBloom, high = maxBloom, ans = -1;

        while(low <= high){
            int mid = low + (high - low) / 2;
            if(possible(bloomDay, m, k, mid) == true){
                ans = mid;
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        return ans;
    }
};