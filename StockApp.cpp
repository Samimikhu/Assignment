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

bool StockApp::addTradeTest(const Trade& t) {
    if (numTrades >= MAX_TRADES) return false;
    if (t.shares <= 0 || t.price <= 0) return false;
    trades[numTrades++] = t;
    return true;
}

int StockApp::getNumTrades() const {
    return numTrades;
}

double StockApp::getTotalPortfolioValue() const {
    double total = 0.0;
    for (int i = 0; i < numTrades; i++) {
        total += trades[i].shares * trades[i].price;
    }
    return total;
}

RiskLevel StockApp::getRiskAt(int index) const {
    if (index < 0 || index >= numTrades) return Low;
    return trades[index].risk;
}