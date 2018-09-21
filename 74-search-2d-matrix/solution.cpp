class Solution {
private:
    int search_row(vector<vector<int>>& matrix, int start, int end, int target) {
        if (start == end) {
            return start;
        }
        int mid = (start + end + 1) / 2;
        if (target > matrix[mid][0]) {
            return search_row(matrix, mid, end, target);
        }
        if (target < matrix[mid][0]) {
            return search_row(matrix, start, mid-1, target);
        }
        return -1;
    }
    bool search_col(vector<vector<int>>& matrix, int row, int start, int end, int target) {
        if (start == end && matrix[row][start] == target) {
            return true;
        }
        if (start == end && matrix[row][start] != target) {
            return false;
        }
        int mid = (start + end + 1) / 2;
        if (target > matrix[row][mid]) {
            return search_col(matrix, row, mid, end, target);
        }
        if (target < matrix[row][mid]) {
            return search_col(matrix, row, start, mid-1, target);
        }
        return true;
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() <= 0 || matrix[0].size() <= 0) {
            return false;
        }
        int row = search_row(matrix, 0, matrix.size()-1, target);
        if (row == -1) return true;
        return search_col(matrix, row, 0, matrix[0].size()-1, target);
    }
};