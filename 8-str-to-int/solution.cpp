class Solution {
public:
    int myAtoi(string str) {
        int sz = str.size();
        int num = 0;
        bool is_start = true;
        int is_pos = 1;
        for (int i=0; i<sz; i++) {
            if (is_start) {
                if (str[i] == ' ') continue;
                if ((str[i] < '0' || str[i] > '9') && str[i] != '-' && str[i] != '+') return 0;
                if (str[i] == '-') {
                    is_pos = -1;
                    is_start = false;
                    continue;
                }
                if (str[i] == '+') {
                    is_pos = 1;
                    is_start = false;
                    continue;
                }
                if (str[i] >= '0' && str[i] <= '9') {
                    is_start = false;
                }
            }
            if (!is_start) {
                if (str[i] >= '0' && str[i] <= '9') {
                    int digit = str[i] - '0';
                    long tmp_num = (long)num*10 + digit;
                    if (tmp_num >= INT_MAX && is_pos == 1) {
                        return INT_MAX;
                    }
                    if (tmp_num >= (long)INT_MAX+1 && is_pos == -1) {
                        return INT_MIN;
                    }
                    num = tmp_num;
                } else {
                    break;
                }
            }
        }
        return num * is_pos;
    }
};