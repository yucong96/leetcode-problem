#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
private:
  int index_in_array(vector<int>& arr, int value) {
    return index_in_array_bound(arr, value, 0, arr.size());
  }
  int index_in_array_bound(vector<int>& arr, int value, int left, int right) {
    if (left == right) {
      return left;
    }
    int mid = (left+right)/2;
    if (value > arr[mid]) {
      return index_in_array_bound(arr, value, mid+1, right);
    } else {
      return index_in_array_bound(arr, value, left, mid);
    }
  }
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int nums1_left = 0, nums1_right = nums1.size();
    int nums2_left = 0, nums2_right = nums2.size(); 
    int total = nums1.size() + nums2.size();
    int left = 0;
    while (left != total / 2) {
      //cout << nums1_left << " " << nums1_right << " " << nums2_left << " " << nums2_right << " " << left << endl;
      if (nums1_left != nums1_right) {
	int nums1_mid = (nums1_left+nums1_right)/2;
	int nums2_mid = index_in_array_bound(nums2, nums1[nums1_mid], nums2_left, nums2_right);
	int mid = nums1_mid + nums2_mid;
	if (mid < total/2) {
	  nums1_left = nums1_mid+1;
	  nums2_left = nums2_mid;
	  left = mid + 1;
	} else {
	  nums1_right = nums1_mid;
	  nums2_right = nums2_mid;
	}
      } else {
	nums2_left = total/2 - nums1_left;
	left = total/2;
      }
    }

    //cout << nums1_left << " " << nums1_right << " " << nums2_left << " " << nums2_right << " " << left << endl;
    if (total % 2 == 1) {
      if (nums1_left >= nums1.size()) {
	return nums2[nums2_left];
      } else if (nums2_left >= nums2.size()) {
	return nums1[nums1_left];
      } else if(nums1[nums1_left] < nums2[nums2_left]) {
	return nums1[nums1_left];
      } else {
	return nums2[nums2_left];
      }
    } else {
      int min, max;
      if (nums1_left-1 <= -1) {
	min = nums2[nums2_left-1];
      } else if (nums2_left-1 <= -1) {
	min = nums1[nums1_left-1];
      } else if (nums1[nums1_left-1] > nums2[nums2_left-1]) {
	min = nums1[nums1_left-1];
      } else {
	min = nums2[nums2_left-1];
      } 
      if (nums1_left >= nums1.size()) {
	max = nums2[nums2_left];
      } else if (nums2_left >= nums2.size()) {
	max = nums1[nums1_left]; 
      } else if (nums1[nums1_left] < nums2[nums2_left]) {
	max = nums1[nums1_left];
      } else {
	max = nums2[nums2_left];
      }
      return 1.0*(min+max)/2;
    }
  }
};

void trimLeftTrailingSpaces(string &input) {
  input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
      }));
}

void trimRightTrailingSpaces(string &input) {
  input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
      }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
  vector<int> output;
  trimLeftTrailingSpaces(input);
  trimRightTrailingSpaces(input);
  input = input.substr(1, input.length() - 2);
  stringstream ss;
  ss.str(input);
  string item;
  char delim = ',';
  while (getline(ss, item, delim)) {
    output.push_back(stoi(item));
  }
  return output;
}

int main() {
  string line;
  while (getline(cin, line)) {
    vector<int> nums1 = stringToIntegerVector(line);
    getline(cin, line);
    vector<int> nums2 = stringToIntegerVector(line);

    double ret = Solution().findMedianSortedArrays(nums1, nums2);
    
    string out = to_string(ret);
    cout << out << endl;
  }
  return 0;
}

