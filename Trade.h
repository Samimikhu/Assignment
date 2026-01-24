#pragma once

#include <string>

enum RiskLevel {
    Low,
    Medium,
    High
};

struct Trade {
    std::string symbol;
    int shares;
    double price;
    RiskLevel risk;
};