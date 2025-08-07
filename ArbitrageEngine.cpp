#include "ArbitrageEngine.h"
#include <algorithm>
#include <iostream>

ArbitrageEngine::ArbitrageEngine(int expectedQuotes)
    : expected(expectedQuotes), count(0) {
}

void ArbitrageEngine::receiveQuote(const std::string& exch, const Quote& qt) {
    bool ready = false;
    {
        std::lock_guard<std::mutex> lock(mtx);
        quotes[exch] = qt;
        if (++count == expected) {
            ready = true;
        }
    }

    if (ready) {
        std::vector<Quote> sortedQuotes;
        {
            std::lock_guard<std::mutex> lock(mtx);
            for (const auto& [ex, q] : quotes) {
                sortedQuotes.push_back(q);
            }
            std::sort(sortedQuotes.begin(), sortedQuotes.end());
            count = 0;  // reset for next batch
        }

        performArbitrage(sortedQuotes);
    }
}

void ArbitrageEngine::performArbitrage(const std::vector<Quote>& sortedQuotes) {
    std::cout << "Performing arbitrage on sorted quotes:\n";
    for (const auto& q : sortedQuotes) {
        std::cout << q.exch << ": " << q.price << "\n";
    }

    // Basic arbitrage example:
    // Buy at the lowest price exchange, sell at the highest price exchange if profitable
    if (sortedQuotes.size() < 2) return;

    const Quote& buy = sortedQuotes.front();
    const Quote& sell = sortedQuotes.back();

    if (sell.price > buy.price) {
        double profit = sell.price - buy.price;
        std::cout << "Arbitrage opportunity: Buy at " << buy.exch << " (" << buy.price
            << "), Sell at " << sell.exch << " (" << sell.price
            << "), Profit: " << profit << "\n";
    }
    else {
        std::cout << "No arbitrage opportunity this round.\n";
    }
}
