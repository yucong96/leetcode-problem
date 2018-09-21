class Solution {
public:
    int maxProfit(vector<int>& prices) {
        
        int size = prices.size();
        vector<int> profit_in_left_n; {
            profit_in_left_n.resize(size, 0);
        }
        vector<int> profit_in_right_n; {
            profit_in_right_n.resize(size, 0);
        }
        
        int buy_price;
        int history_best = 0;
        for (int i=0; i<size; i++) {
            if (i==0) {
                buy_price = prices[i];
                continue;
            }
            if (prices[i] > buy_price && prices[i] - buy_price > history_best) {
                history_best = prices[i] - buy_price;
            } else if (prices[i] < buy_price) {
                buy_price = prices[i];
            }
            profit_in_left_n[i] = history_best;
        }
        
        int sell_price;
        history_best = 0;
        for (int i=size-1; i>=0; i--) {
            if (i==size-1) {
                sell_price = prices[i];
                continue;
            }
            if (prices[i] < sell_price && sell_price - prices[i] > history_best) {
                history_best = sell_price - prices[i];
            } else if (prices[i] > sell_price) {
                sell_price = prices[i];
            }
            profit_in_right_n[i] = history_best;
        }
        
        int best_sum = 0;
        for (int i=0; i<size; i++) {
            int sum;
            if (i==size-1) sum = profit_in_left_n[i];
            else sum = profit_in_left_n[i] + profit_in_right_n[i+1];
            if (sum > best_sum) {
                best_sum = sum;
            }
        }
        return best_sum;
    }
};