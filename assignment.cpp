#include <iostream>     
#include <iomanip>      
#include <string>       
#include <fstream>     


using namespace std;

// Enum to represent risk levels in a readable way
// Internally stored as integers: Low = 0, Medium = 1, High = 2
enum RiskLevel { Low, Medium, High };

// Struct that represents ONE stock trade
// This groups related data together
struct Trade {
    string symbol;      // Stock symbol (ex: AAPL)
    int shares;         // Number of shares
    double price;       // Price per share
    RiskLevel risk;     // Risk level using the enum
};

// Class that manages the entire stock application
class StockApp {
private:
    // Maximum number of trades allowed
    static const int MAX_TRADES = 5;

    // Array to store trades
    Trade trades[MAX_TRADES];

    // Keeps track of how many trades are currently stored
    int numTrades;

public:
    // Constructor initializes number of trades to zero
    StockApp() {
        numTrades = 0;
    }

    // Displays a simple program banner
    void displayBanner() {
        cout << "=== Welcome to Simple Stocks Tracker ===\n";
    }

    // Adds a new trade with full input validation
    void addTrade() {

        // Prevent adding more trades than allowed
        if (numTrades >= MAX_TRADES) {
            cout << "Max trades reached!\n";
            return;
        }

        Trade t;  // Temporary Trade object to store input

        // Clears leftover newline from previous input
        cin.ignore();

        // ----- SYMBOL INPUT -----
        cout << "Enter stock symbol: ";
        getline(cin, t.symbol);

        // Validate that the symbol is not empty
        while (t.symbol.empty()) {
            cout << "Symbol cannot be empty. Enter again: ";
            getline(cin, t.symbol);
        }

        // ----- SHARES INPUT -----
        cout << "Enter number of shares: ";
        cin >> t.shares;

        // Validate: must be an integer AND greater than zero
        while (cin.fail() || t.shares <= 0) {
            cin.clear();                 // Reset input stream error state
            cin.ignore(1000, '\n');      // Remove invalid input
            cout << "Invalid. Enter a positive integer: ";
            cin >> t.shares;
        }

        // ----- PRICE INPUT -----
        cout << "Enter price per share: ";
        cin >> t.price;

        // Validate: must be a number AND greater than zero
        while (cin.fail() || t.price <= 0) {
            cin.clear();                 // Clear fail state
            cin.ignore(1000, '\n');      // Remove bad input
            cout << "Invalid. Enter a positive number: ";
            cin >> t.price;
        }

        // ----- RISK LEVEL INPUT -----
        int r;
        cout << "Select risk (1=Low, 2=Medium, 3=High): ";
        cin >> r;

        // Validate menu-style input
        while (cin.fail() || r < 1 || r > 3) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid. Enter 1,2,3: ";
            cin >> r;
        }

        // Convert integer choice into enum value
        t.risk = static_cast<RiskLevel>(r - 1);

        // Store the trade in the array and increase count
        trades[numTrades++] = t;

        cout << "Trade added!\n";
    }

    // Displays a formatted summary of all trades
    void displaySummary() {

        // If no trades exist, exit early
        if (numTrades == 0) {
            cout << "No trades to display.\n";
            return;
        }

        double total = 0.0;  // Total portfolio value

        // Display table headers
        cout << "\nSymbol  Shares  Price   Risk\n";
        cout << "----------------------------\n";

        // Loop through all stored trades
        for (int i = 0; i < numTrades; i++) {

            // Display each trade with formatting
            cout << left << setw(7) << trades[i].symbol
                << setw(7) << trades[i].shares
                << setw(8) << fixed << setprecision(2) << trades[i].price;

            // Convert enum value into readable text
            switch (trades[i].risk) {
            case Low:    cout << "Low"; break;
            case Medium: cout << "Med"; break;
            case High:   cout << "High"; break;
            }
            cout << endl;

            // Calculate total portfolio value
            total += trades[i].shares * trades[i].price;
        }

        // Display final total
        cout << "\nTotal Portfolio Value: $"
            << fixed << setprecision(2) << total << endl;
    }

    // Saves a very simple report to a text file
    // Only saves symbol, shares, and price
    void saveReportToFileSimple() {

        // Create and open output file
        ofstream file("report.txt");

        // Verify file opened successfully
        if (!file) {
            cout << "Error opening file.\n";
            return;
        }

        // Write each trade to the file
        for (int i = 0; i < numTrades; i++) {
            file << trades[i].symbol << " "
                << trades[i].shares << " "
                << trades[i].price << endl;
        }


        file.close();

        cout << "Report saved to report.txt\n";
    }

    // Displays menu and handles user choices
    void showMenu() {
        int choice;

        do {
            // Display menu options
            cout << "\nMenu:\n"
                << "1. Add Trade\n"
                << "2. View Summary\n"
                << "3. Save Report\n"
                << "4. Exit\n"
                << "Choice: ";

            cin >> choice;

            // Validate menu input
            while (cin.fail() || choice < 1 || choice > 4) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid. Enter 1-4: ";
                cin >> choice;
            }

            // Execute user choice
            switch (choice) {
            case 1: addTrade(); break;
            case 2: displaySummary(); break;
            case 3: saveReportToFileSimple(); break;
            case 4: cout << "Exiting...\n"; break;
            }

        } while (choice != 4);  // Loop until user chooses Exit
    }
};

// Program entry point
int main() {

    // Create StockApp object
    StockApp app;

    // Display welcome banner
    app.displayBanner();

    // Start menu loop
    app.showMenu();

    return 0;
}
