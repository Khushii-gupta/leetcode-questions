class Solution {
public:
    int noDays(vector<int>& weights, int capacity){
        int n = weights.size();
        int day = 1;
        int load = 0;
        for(int i = 0; i < n; i++){
            if(load + weights[i] > capacity){
                day = day + 1;
            load = weights[i];
            }
            else{
                load += weights[i];
            }
        }
        return day;
    }

    int shipWithinDays(vector<int>& weights, int days) {
        int sum = 0;
        int n = weights.size();
        int low = *max_element(weights.begin(), weights.end());
        for(int i = 0; i < n; i++){
            sum += weights[i];
        }
        int high = sum;

        while(low <= high){
            int mid = low + (high - low) / 2;
            int numDays = noDays(weights, mid);
            if(numDays <= days){
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        return low;
    }
};