#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <assert.h>
using namespace std;

class Solution {
private:
  bool is_match_bound(string s, string p, unsigned int si, unsigned int pi) {
    if (si == s.length() && pi == p.length()) {
      return true;
    }
    if (si >= s.length() && pi+1 < p.length() && p[pi+1] == '*') {
      return is_match_bound(s, p, si, pi+2);
    } 
    if ((pi >= p.length() && si < s.length()) || (si >= s.length() && pi < p.length())) {
      return false;
    }
    
    if (pi+1 == p.length() || (pi+1 < p.length() && p[pi+1] != '*')) {
      if (p[pi] == '.' || p[pi] == s[si]) {
	return is_match_bound(s, p, si+1, pi+1);
      } else {
	return false;
      } 
    } else { // follow by *
      if (p[pi] != s[si] && p[pi] != '.') {
	return is_match_bound(s, p, si, pi+2);
      } else { // p[pi] == s[si] || p[pi] == '.'
	return is_match_bound(s, p, si, pi+2) || is_match_bound(s, p, si+1, pi);
      }
    } 
  }
public:
  bool isMatch(string s, string p) {
    return is_match_bound(s, p, 0, 0);
  }
};

string stringToString(string input) {
  assert(input.length() >= 2);
  string result;
  for (int i = 1; i < input.length() -1; i++) {
    char currentChar = input[i];
    if (input[i] == '\\') {
      char nextChar = input[i+1];
      switch (nextChar) {
      case '\"': result.push_back('\"'); break;
      case '/' : result.push_back('/'); break;
      case '\\': result.push_back('\\'); break;
      case 'b' : result.push_back('\b'); break;
      case 'f' : result.push_back('\f'); break;
      case 'r' : result.push_back('\r'); break;
      case 'n' : result.push_back('\n'); break;
      case 't' : result.push_back('\t'); break;
      default: break;
      }
      i++;
    } else {
      result.push_back(currentChar);
    }
  }
  return result;
}

string boolToString(bool input) {
  return input ? "True" : "False";
}

int main() {
  string line;
  while (getline(cin, line)) {
    string s = stringToString(line);
    getline(cin, line);
    string p = stringToString(line);
        
    bool ret = Solution().isMatch(s, p);

    string out = boolToString(ret);
    cout << out << endl;
  }
  return 0;
}
