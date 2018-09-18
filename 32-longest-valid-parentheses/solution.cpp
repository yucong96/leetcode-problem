class Solution {
public:
  int longestValidParentheses(string s) {
    stack<int> st;
    for (int i=0, sz=s.size(); i<sz; i++) {
      if (s[i] == '(') {
	st.push(1);
	continue;
      }
      if (s[i] == ')') {
	int temp_valid = 0;
	while (!st.empty() && st.top()<0) {
	  temp_valid += st.top();
	  st.pop();
	}
	if (st.empty()) {
	  if (temp_valid < 0) {
	    st.push(temp_valid);
	  }
	  st.push(2);
	  continue;
	}
	if (st.top() == 1) {
	  temp_valid -= 2;
	  st.pop();
	  st.push(temp_valid);
	  continue;
	}
	if (st.top() == 2) {
	  if (temp_valid < 0) {
	    st.push(temp_valid);
	  }
	  st.push(2);
	  continue;
	}
      }
    }
    int max_valid = 0;
    int valid = 0;
    while (!st.empty()) {
      int val = st.top();
      if (val < 0) {
	valid -= val;
      } else {
	if (valid > max_valid) {
	  max_valid = valid;
	}
	valid = 0;
      }
      st.pop();
    }
    if (valid > max_valid) {
      max_valid = valid;
    }
    return max_valid;
  }
};
