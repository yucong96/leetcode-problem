class Solution {
public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int sz = gas.size();
    if (sz == 0) {
      return 0;
    }
    int min_remain = 1e7;
    int min_idx = 0;
    int remain = 0;
    for (int i=0; i<sz; i++) {
      remain += gas[i] - cost[i];
      if (remain < min_remain) {
	min_remain = remain;
	min_idx = i;
      }
    }
    if (remain < 0) {
      return -1;
    } else {
      return (min_idx+1) % sz;
    }
  }
};
