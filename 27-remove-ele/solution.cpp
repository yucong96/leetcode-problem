class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int index = 0, length = nums.size();
        while (index < length) {
            if (nums[index] == val) {
                do {
                    nums[index] = nums[length-1];
                    length--;
                } while (nums[index] == val && index < length);
            }
            index++;
        }
        return length;
    }
};
