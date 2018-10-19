class Solution {
private:
    vector<vector<int>> horiz;
    vector<vector<int>> vert;
    void init_tables(int n_row, int n_col) {
        horiz.resize(n_row);
        vert.resize(n_row);
        for (int i=0; i<n_row; i++) {
            horiz[i].resize(n_col);
            vert[i].resize(n_col);
        }
    }
    void set_zero(int row_idx, int col_idx) {
        horiz[row_idx][col_idx] = 0;
        vert[row_idx][col_idx] = 0;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n_rows = matrix.size();
        if (n_rows == 0) return 0;
        int n_cols = matrix[0].size();
        if (n_cols == 0) return 0;
        int max_rec = 0;
        init_tables(n_rows, n_cols);
        for (int sum=0; sum<n_rows+n_cols-1; sum++) {
            for (int i=0; i<n_rows && i<=sum; i++) {
                int j=sum-i;
                if (j>=0 && j<n_cols) {
                    if (matrix[i][j] == '0') {
                        set_zero(i, j);
                        continue;
                    }
                    // matrix[i][j] == '1'
                    if (i==0 && j==0) {
                        horiz[i][j] = 1;
                        vert[i][j] = 1;
                    } else if (i==0) {
                        horiz[i][j] = 1;
                        vert[i][j] = vert[i][j-1] + 1;
                    } else if (j==0) {
                        vert[i][j] = 1;
                        horiz[i][j] = horiz[i-1][j] + 1;
                    } else { // i!=0 && j!=0
                        horiz[i][j] = horiz[i-1][j] + 1;
                        vert[i][j] = vert[i][j-1] + 1;
                    }
                    int min = 1e9;
                    if (horiz[i][j] > vert[i][j]) {
                        for (int k=0; k<=j; k++) {
                            if (horiz[i][j-k] < min) {
                                min = horiz[i][j-k];
                            }
                            if (min == 0) break;
                            int rec = min * (k+1);
                            if (rec > max_rec) {
                                max_rec = rec;
                            }
                        }
                    } else {
                        for (int k=0; k<=i; k++) {
                            if (vert[i-k][j] < min) {
                                min = vert[i-k][j];
                            }
                            if (min == 0) break;
                            int rec = min * (k+1);
                            if (rec > max_rec) {
                                max_rec = rec;
                            }
                        }
                    }
                }
            }
        }
        return max_rec;
    }
};