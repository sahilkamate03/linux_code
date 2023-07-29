class Solution {
public:
    int pivot(vector<int>& nums)
    {
        int l=0; int r=nums.size()-1;
        while (l <= r) {
        int m = l + (r - l) / 2;
 
        // Check if x is present at mid
        if (nums[m] >nums[m+1])
            return m;
 
        // If x greater, ignore left half
        if (nums[r] <nums[m])
            l = m + 1;
 
        // If x is smaller, ignore right half
        else
            r = m - 1;
        }
        return -1;

    }
    int search(vector<int>& nums, int target) {
        return pivot(nums);
    }
};
