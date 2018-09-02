#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

bool get_board(string filename, vector<vector<char>>& board) {
  ifstream ifs;
  ifs.open(filename.c_str());
  if (!ifs.is_open()) {
    cerr << "Error: Open file failed." << endl;
    return false;
  }
  board.resize(9);
  for (int i=0; i<9; i++) {
    board[i].resize(9);
  }
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      ifs >> board[i][j];
    }
  }
  return true;
}

void print_board(const vector<vector<char>>& board) {
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void print_candidates(const vector<vector<char>>& board, const vector<vector<set<int>>>& candidates) {
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (board[i][j] == '.') {
	cout << "(" << i << " " << j << "): ";
	for (auto it=candidates[i][j].begin(); it!=candidates[i][j].end(); it++) {
	  cout << *it << " ";
	}
	cout << endl;
      }
    }
  }
}

class Solution {
private:
  
  set<int> get_candidate(const vector<vector<char>> board, const int row, const int col) {
    int num_dict[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i=0; i<9; i++) {
      if (board[row][i] != '.') {
	num_dict[board[row][i]-'1'] = 0;
      } 
    }
    for (int i=0; i<9; i++) {
      if (board[i][col] != '.') {
	num_dict[board[i][col]-'1'] = 0;
      }
    }
    int block_top = row/3;
    int block_left = col/3;
    for (int i=0; i<3; i++) {
      for (int j=0; j<3; j++) {
	if (board[3*block_top+i][3*block_left+j] != '.') {
	  num_dict[board[3*block_top+i][3*block_left+j]-'1'] = 0;
	}
      }
    }
    set<int> candidate;
    for (int i=0; i<9; i++) {
      if (num_dict[i] > 0) {
	candidate.insert(num_dict[i]);
      }
    }
    return candidate;
  }

  bool check_validation(const vector<vector<char>>& board, const vector<vector<set<int>>> candidates,
			int& candidate_row, int& candidate_col) {
    int min_candidate_num = 10;
    for (int i=0; i<9; i++) {
      for (int j=0; j<9; j++) {
	if (board[i][j] == '.') {
	  if (candidates[i][j].size() == 0) {
	    return false;
	  }
	  if (candidates[i][j].size() < min_candidate_num) {
	    candidate_row = i;
	    candidate_col = j;
	    min_candidate_num = candidates[i][j].size();
	  }
	}
      }
    }
    return true;
  }

  void update_board(vector<vector<char>>& board, const int row, const int col, const int val) {
    board[row][col] = val + '0';
  }

  void reverse_board(vector<vector<char>>& board, const int row, const int col) {
    board[row][col] = '.';
  }

  void update_candidates(vector<vector<char>>& board, vector<vector<set<int>>>& candidates,
			 const int row, const int col, const int val) {
    for (int i=0; i<9; i++) {
      if (board[row][i] == '.') {
	candidates[row][i].erase(val);
      }
    }
    for (int i=0; i<9; i++) {
      if (board[i][col] == '.') {
	candidates[i][col].erase(val);
      }
    }
    int block_top = row / 3;
    int block_left = col / 3;
    for (int i=0; i<3; i++) {
      for (int j=0; j<3; j++) {
	if (board[3*block_top+i][3*block_left+j] == '.') {
	  candidates[3*block_top+i][3*block_left+j].erase(val);
	}
      }
    }
  }

  void reverse_candidates(vector<vector<set<int>>>& candidates, const vector<vector<set<int>>>& old_candidates) {
    candidates = old_candidates;
  }
  
  bool solve_backtracking(vector<vector<char>>& board, vector<vector<set<int>>> candidates) {
    int row = -1, col = -1;
    if (!check_validation(board, candidates, row, col)) {
      return false;
    }
    if (row == -1 || col == -1) {
      return true;
    }
    vector<vector<set<int>>> old_candidates = candidates;
    for (auto it = old_candidates[row][col].begin(); it != old_candidates[row][col].end(); it++) {
      update_candidates(board, candidates, row, col, *it);
      update_board(board, row, col, *it);
      if (solve_backtracking(board, candidates)) {
	return true;
      } else {
	reverse_board(board, row, col);
	reverse_candidates(candidates, old_candidates);
      }
    }
    return false;
  }
  
public:
  void solveSudoku(vector<vector<char>>& board) {

    vector<vector<set<int>>> candidates; {
      candidates.resize(9);
      for (int i=0; i<9; i++) {
	candidates[i].resize(9);
      }
      for (int i=0; i<9; i++) {
	for (int j=0; j<9; j++) {
	  if (board[i][j] == '.') {
	    candidates[i][j] = get_candidate(board, i, j); 
	  }
	}
      }
    }

    if (!solve_backtracking(board, candidates)) {
      cout << "No answers." << endl;
    } else {
      cout << "Find answers." << endl;
    }
  }
};

int main(){
  vector<vector<char>> board;
  if (!get_board("problem4.txt", board)) {
    return 1;
  }

  Solution s;
  s.solveSudoku(board);

  print_board(board);
}
