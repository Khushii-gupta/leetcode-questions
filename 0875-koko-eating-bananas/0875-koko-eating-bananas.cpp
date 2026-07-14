class Solution {
public:
    long long calculateTotalHour(vector<int> &piles, int speed){
        long long totalH = 0;
        for(int bananas : piles){
            totalH += (long long)ceil((double)bananas / speed);
        }
        return totalH;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int maxPile = *max_element(piles.begin(), piles.end());
        int low = 1; 
        int high = maxPile;
        int ans = maxPile;

        while(low <= high){
            int mid = low + (high - low) / 2;
            long long totalHour = calculateTotalHour(piles, mid);
            if(totalHour <= h){
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