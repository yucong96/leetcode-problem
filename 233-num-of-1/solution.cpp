class Solution {
public:
    int countDigitOne(int n) {
        
        if (n<=0) {
            return 0;
        }
        
        vector<int> num;
        int tmp = n;
        while (tmp!=0) {
            num.push_back(tmp%10);
            tmp /= 10;
        }
        
        int sz = num.size();
        vector<int> ten_fact;
        ten_fact.resize(sz);
        for (int i=0; i<sz; i++) {
            if (i==0) {
                ten_fact[i] = 1;
            } else {
                ten_fact[i] = ten_fact[i-1] * 10;
            }
        }
        
        int sum = 0;
        for (int i=sz-1; i>=0; i--) {
            if (num[i] == 0) continue;
            if (i == 0) {
                sum += 1;
                continue;
            }
            if (num[i] == 1) {
                sum += ten_fact[i-1] * (i) + (n-ten_fact[i]*num[i]) + 1;
            } else {
                sum += ten_fact[i-1] * (i) * num[i] + ten_fact[i];
            }
            n -= ten_fact[i]*num[i];
        }
        
        return sum;
    }
};