class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l=0, r=nums.size()-1;

        while (l <= r) {
        int m = l + (r - l) / 2;
        
        if (nums[m] == target)
            return m;
        // Check if x is present at mid
        if (nums[l] <= nums[m])
        {
            if (nums[l]<=target && nums[m]<target)
                r = m-1;
            else
                l =m+1;
        }
        else 
        {
            if (nums[m]<target && target<=nums[r])
                l =m+1;
            else 
                r =m-1;
        }
        }

 
        // If we reach here, then element was not present
        return -1;
        }
};
