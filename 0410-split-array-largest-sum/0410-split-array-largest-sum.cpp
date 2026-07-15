class Solution {
public:
    bool possibleSplit(vector<int>& nums, long long ways, int k) {
    int count = 1;
    long long allWay = 0;

    for (int x : nums) {

        if (x > ways)
            return false;

        if (allWay + x > ways) {
            count++;
            allWay = x;
        }
        else {
            allWay += x;
        }

        if (count > k)
            return false;
    }
    return true;
    }

    int splitArray(vector<int>& nums, int k) {
        long long low = *min_element(nums.begin(), nums.end());
        int n = nums.size();
        long long sum = 0;
        for(int i = 0; i < n; i++){
            sum += nums[i];
        }
        long long high = sum;

        while(low <= high){
            long long mid = low + (high - low) / 2;
            if(possibleSplit(nums, mid, k)){
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        return (int)low;
    }
};