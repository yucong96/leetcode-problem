class Solution {
private:
  int find_min_in_range(vector<int>& nums, int left, int right) {
    if (left == right) {
      return nums[left];
    }
    if (left + 1 == right) {
      return nums[left] < nums[right] ? nums[left] : nums[right];
    }
    int mid = (left+right)/2;
    if (nums[left] > nums[mid]) {
      return find_min_in_range(nums, left, mid);
    }
    if (nums[mid] > nums[right]) {
      return find_min_in_range(nums, mid, right);
    }
    return nums[left];
  }
public:
  int findMin(vector<int>& nums) {
    return find_min_in_range(nums, 0, nums.size()-1);
  }
};
