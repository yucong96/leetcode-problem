class Solution {
private:
    void traverse(vector<vector<int>> &adjacent, vector<bool> &flag, vector<int> &num, int idx, int depth, int max_depth, int &count) {
        if (depth == max_depth) {
            count++;
            return;
        }
        vector<int> visited_num;
        for (int i=0, sz=adjacent[idx].size(); i<sz; i++) {
            int next = adjacent[idx][i];
            if (flag[next] == true) {
                bool visited = false;
                for (int j=0; j<visited_num.size(); j++) {
                    if (num[next] == visited_num[j]) {
                        visited = true;
                        break;
                    }
                }
                if (!visited) {
                    visited_num.push_back(num[next]);
                    flag[next] = false;
                    traverse(adjacent, flag, num, next, depth+1, max_depth, count);
                    flag[next] = true;
                }
            }
        }
    }
public:
    int numSquarefulPerms(vector<int>& A) {
        int N = A.size();
        if (N<1) return 0;
        
        vector<vector<int>> adjacent;
        for (int i=0; i<N; i++) {
            vector<int> v;
            for (int j=0; j<N; j++) {
                if (j==i) continue;
                long root = sqrt(A[i]+A[j]);
                if (root*root == A[i] + A[j]) {
                    v.push_back(j);
                }
            }
            adjacent.push_back(v);
        }
        
        vector<bool> flag; {
            for (int i=0; i<N; i++) {
                flag.push_back(true);
            }
        }
        int count = 0;
        vector<int> visited_num;
        for (int i=0; i<N; i++) {
            bool visited = false;
            for (int j=0; j<visited_num.size(); j++) {
                if (visited_num[j] == A[i]) {
                    visited = true;
                    break;
                }
            }
            if (!visited) {
                visited_num.push_back(A[i]);
                flag[i] = false;
                traverse(adjacent, flag, A, i, 1, N, count);
                flag[i] = true;
            }
        }
        return count;
    }
};