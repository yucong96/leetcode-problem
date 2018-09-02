class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for (int i=0; i<nums.size(); i++) {
            if (nums[i] < 0 || nums[i] > nums.size()) {
                nums[i] = 0;
            }
        }
        for (int i=0; i<nums.size(); i++) {
            if (nums[i] <= 0) {
                continue;
            }
            int curr_num = nums[i];
            while (true) {
                if (nums[curr_num-1] <= 0) {
                    nums[curr_num-1]--;
                    break;
                }
                int tmp = nums[curr_num-1];
                nums[curr_num-1] = -1;
                curr_num = tmp;
            }
        }
        for (int i=0; i<nums.size(); i++) {
            if (nums[i] == 0) {
                return i+1;
            }
        }
        return nums.size()+1;
    }
};
