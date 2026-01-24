#include "StockApp.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

StockApp::StockApp() : numTrades(0) {}

void StockApp::displayBanner() {
    cout << "=== Welcome to Simple Stock Tracker ===\n";
}

void StockApp::addTrade() {
    if (numTrades >= MAX_TRADES) {
        cout << "Max trades reached!\n";
        return;
    }

    Trade t;
    cin.ignore();

    cout << "Enter stock symbol: ";
    getline(cin, t.symbol);

    cout << "Enter number of shares: ";
    cin >> t.shares;
    while (cin.fail() || t.shares <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid. Enter positive integer: ";
        cin >> t.shares;
    }

    cout << "Enter price per share: ";
    cin >> t.price;
    while (cin.fail() || t.price <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid. Enter positive number: ";
        cin >> t.price;
    }

    int r;
    cout << "Select risk (1=Low, 2=Medium, 3=High): ";
    cin >> r;
    while (cin.fail() || r < 1 || r > 3) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid. Enter 1-3: ";
        cin >> r;
    }

    t.risk = static_cast<RiskLevel>(r - 1);
    trades[numTrades++] = t;
}

void StockApp::displaySummary() {
    double total = getTotalPortfolioValue();

    cout << "\nSymbol  Shares  Price   Risk\n";
    cout << "----------------------------\n";

    for (int i = 0; i < numTrades; i++) {
        cout << left << setw(7) << trades[i].symbol
            << setw(7) << trades[i].shares
            << setw(8) << fixed << setprecision(2) << trades[i].price;

        switch (trades[i].risk) {
        case Low: cout << "Low"; break;
        case Medium: cout << "Medium"; break;
        case High: cout << "High"; break;
        }
        cout << endl;
    }

    cout << "\nTotal Portfolio Value: $" << fixed << setprecision(2) << total << endl;
}

void StockApp::saveReportToFile() {
    ofstream file("report.txt");
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    for (int i = 0; i < numTrades; i++) {
        file << trades[i].symbol << " "
            << trades[i].shares << " "
            << trades[i].price << endl;
    }

    file.close();
    cout << "Report saved to report.txt\n";
}

void StockApp::showMenu() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Trade\n";
        cout << "2. View Summary\n";
        cout << "3. Save Report\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid. Enter 1-4: ";
            cin >> choice;
        }

        switch (choice) {
        case 1: addTrade(); break;
        case 2: displaySummary(); break;
        case 3: saveReportToFile(); break;
        case 4: cout << "Exiting...\n"; break;
        }

    } while (choice != 4);
}

// ---------- Test-friendly methods ----------

// Adds a trade for testing purposes, bypassing user input
bool StockApp::addTradeTest(const Trade& t) {
    // If the array is full, reject the trade
    if (numTrades >= MAX_TRADES) return false;

    // If shares or price are invalid, reject the trade
    if (t.shares <= 0 || t.price <= 0) return false;

    // Store the trade in the array and increment the trade count
    trades[numTrades++] = t;

    // Trade was successfully added
    return true;
}

// Returns the number of trades currently stored
int StockApp::getNumTrades() const {
    return numTrades;  // Simply return the current trade count
}

// Calculates total portfolio value for all trades
double StockApp::getTotalPortfolioValue() const {
    double total = 0.0;  // Start with 0

    // Loop through each trade and add its total value (shares * price)
    for (int i = 0; i < numTrades; i++) {
        total += trades[i].shares * trades[i].price;
    }

    // Return the total portfolio value
    return total;
}

// Returns the risk level of a trade at a given index
RiskLevel StockApp::getRiskAt(int index) const {
    // If the index is invalid (negative or beyond current trades), return default Low risk
    if (index < 0 || index >= numTrades) return Low;

    // Otherwise, return the stored risk for that trade
    return trades[index].risk;
}
