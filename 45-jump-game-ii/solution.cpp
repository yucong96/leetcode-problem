class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> score;
        score.resize(nums.size());
        score[nums.size()-1] = 0;
        for (int i=nums.size()-2; i>=0; i--) {
            int j_num = nums[i];
            if (i+j_num >= nums.size()-1) {
                score[i] = 1;
                continue;
            }
            int min_score = 1e7;
            for (int k=i+1; k<=i+j_num; ) {
                if (k+nums[k]<=i+j_num) {
                    if (min_score >= score[k]) {
                        min_score = score[k] - 1;
                    }
                    k += nums[k]+1;
                } else {
                    if (min_score > score[k]) {
                        min_score = score[k];
                    }
                    k += 1;
                }
                if (min_score == 1) break;
            }
            score[i] = min_score + 1;
        }
        return score[0];
    }
};
