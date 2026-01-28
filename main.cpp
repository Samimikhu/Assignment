#include "StockApp.h"


#ifndef RUN_TESTS

int main() {
    StockApp app;
    app.displayBanner();
    app.showMenu();
    return 0;
}

#else

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// ---------------- A) CALCULATIONS (4 TESTS) ----------------

TEST_CASE("Total portfolio value with multiple trades") {
    StockApp app;
    app.addTradeTest({"AAPL", 10, 100.0, Low});
    app.addTradeTest({"MSFT", 5, 200.0, Medium});

    CHECK(app.getTotalPortfolioValue() == doctest::Approx(2000.0));
}

TEST_CASE("Total portfolio value with single trade") {
    StockApp app;
    app.addTradeTest({"GOOG", 2, 500.0, High});

    CHECK(app.getTotalPortfolioValue() == 1000.0);
}

TEST_CASE("Total portfolio value with no trades") {
    StockApp app;
    CHECK(app.getTotalPortfolioValue() == 0.0);
}

TEST_CASE("Invalid trade not included in total") {
    StockApp app;
    app.addTradeTest({"BAD", -5, 10.0, Low});

    CHECK(app.getTotalPortfolioValue() == 0.0);
}

// ---------------- B) ENUM DECISION LOGIC (3 TESTS) ----------------

TEST_CASE("Low risk stored correctly") {
    StockApp app;
    app.addTradeTest({"SAFE", 1, 10.0, Low});

    CHECK(app.getRiskAt(0) == Low);
}

TEST_CASE("Medium risk stored correctly") {
    StockApp app;
    app.addTradeTest({"MID", 1, 10.0, Medium});

    CHECK(app.getRiskAt(0) == Medium);
}

TEST_CASE("Invalid index returns default risk") {
    StockApp app;
    CHECK(app.getRiskAt(0) == Medium);
}

// ---------------- C) STRUCT / ARRAY PROCESSING (3 TESTS) ----------------

TEST_CASE("Trade count increases when adding trades") {
    StockApp app;
    app.addTradeTest({"A", 1, 1.0, Low});
    app.addTradeTest({"B", 1, 1.0, Low});

    CHECK(app.getNumTrades() == 2);
}

TEST_CASE("Maximum trades enforced") {
    StockApp app;
    for (int i = 0; i < 5; i++) {
        app.addTradeTest({"X", 1, 1.0, Low});
    }

    CHECK(app.addTradeTest({"OVER", 1, 1.0, Low}) == false);
}

TEST_CASE("Empty trade list has zero count") {
    StockApp app;
    CHECK(app.getNumTrades() == 0);
}

// ---------------- D) CLASS METHODS (2 TESTS) ----------------

TEST_CASE("addTradeTest returns true for valid trade") {
    StockApp app;
    CHECK(app.addTradeTest({"OK", 1, 10.0, Low}) == true);
}

TEST_CASE("addTradeTest rejects negative values") {
    StockApp app;
    CHECK(app.addTradeTest({"BAD", -1, 10.0, Low}) == false);
}

#endif
