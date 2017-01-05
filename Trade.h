#ifndef TRADE_H
#define TRADE_H


#include "vector.h"
using pep::vector;


class Trade {
protected:
    int buyTime;
    int sellTime;

public:
    Trade(const int buyTimeIn, const int sellTimeIn)
        : buyTime(buyTimeIn), sellTime(sellTimeIn) {
    }

    int getBuyTime() const {
        return buyTime;
    }

    int getSellTime() const {
        return sellTime;
    }

};

// TODO your code goes here:
    Trade bestBuySellTime(vector<int> & prices) {
        int buyTime = 0;
        int sellTime = 0;
        int profit = 0;
        int maxProfit = 0;
        for (int i1 = 0; i1 < prices.size(); i1++) { //to find buyTime
            for (int i2 = i1; i2 < prices.size(); i2++) { //to find sellTime
                profit = prices[i2] - prices[i1]; //calculating profit of every possible buy-sell combination
                if (profit > maxProfit) {
                    maxProfit = profit;
                    buyTime = i1;
                    sellTime = i2;
                }
            }
        }
        Trade idealTrade = Trade(buyTime, sellTime);
        return idealTrade;
    }
// Don't write any code below this line

#endif
