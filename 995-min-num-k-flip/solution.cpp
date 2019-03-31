class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        vector<bool> flip_end_flag(A.size()+1, false);
        int flip_begin = 0;
        int flip_end = 0;
        int count = 0;
        for (int i=0, sz=A.size(); i<sz; i++) {
            if (flip_end_flag[i]) {
                flip_end++;
            }
            if ((A[i]+flip_begin-flip_end)%2==1) {
                continue;
            }
            flip_begin++;
            if (i+K > A.size()) return -1;
            flip_end_flag[i+K] = true;
        }
        return flip_begin;
    }
};