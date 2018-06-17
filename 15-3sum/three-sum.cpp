#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
private:
  void add(vector<int>& nums, int& v) {
    for (int i=1; ; i++) {
      if (v+i < nums.size() && nums[v+i] != nums[v] || v+i == nums.size()) {
	v = v+i;
	break;
      }
    }
  }
  void sub(vector<int>& nums, int& v) {
    for (int i=1; ; i++) {
      if (v-i >= 0 && nums[v-i] != nums[v] || v-i == -1) {
	v = v-i;
	break;
      }
    }
  }
public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    for (int i=0; i<nums.size(); add(nums, i)) {
      if (nums[i] > 0) break;
            int j = i+1;
	    int k = nums.size()-1;
	    while (1) {
	      if (j >= k) break;
	      int sum = nums[i] + nums[j] + nums[k];
	      if (sum == 0) {
		vector<int> result_vec;
		result_vec.push_back(nums[i]);
		result_vec.push_back(nums[j]);
		result_vec.push_back(nums[k]);
		result.push_back(result_vec);
		add(nums, j);
		sub(nums, k);
	      } else if (sum < 0) {
		add(nums, j);
	      } else {
		sub(nums, k);
	      }
	    }
    }
    return result;
  }
};

int main() {
  Solution s;
  vector<int> nums;
  nums.push_back(1);
  nums.push_back(-1);
  nums.push_back(-1);
  nums.push_back(0);
  vector<vector<int>> sum = s.threeSum(nums);
  for (int i=0; i<sum.size(); i++) {
    for (int j=0; j<3; j++) {
      cout << sum[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
