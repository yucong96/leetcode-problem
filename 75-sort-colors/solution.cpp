class Solution {
public:
    void sortColors(vector<int>& nums) {
        int sz = nums.size();
        int index_1 = 0, index_2 = sz-1, num_1 = 0;
        int i = 0;
        while(1) {
            if (i >= index_2 && nums[i]!=0) {
                break;
            }
            if (nums[i] == 0) {
                if(num_1 == 0) {
                    i++;
                    continue;
                } else {
                    nums[i] = 1;
                    nums[index_1++] = 0;
                    i++;
                }
            } else if (nums[i] == 1) {
                if (num_1 == 0) {
                    index_1 = i;
                }
                num_1++;
                i++;
            } else { // nums[i] == 2 
                while (1) {
                    if (nums[index_2] != 2) {
                        nums[i] = nums[index_2];
                        nums[index_2] = 2;
                        index_2--;
                        break;
                    }
                    if (i >= index_2) {
                        break;
                    }
                    index_2--;
                }
            }
            
        }
    }
};