#pragma once

#include "Trade.h"

class StockApp {
private:
    static const int MAX_TRADES = 5;
    Trade trades[MAX_TRADES];
    int numTrades;

public:
    StockApp();

    void displayBanner();
    void addTrade();
    void displaySummary();
    void saveReportToFile();
    void showMenu();

    // Test-friendly methods
    bool addTradeTest(const Trade& t);
    int getNumTrades() const;
    double getTotalPortfolioValue() const;
    RiskLevel getRiskAt(int index) const;
};