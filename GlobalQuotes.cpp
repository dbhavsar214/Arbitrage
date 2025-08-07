#include "GlobalQuotes.h"
#include <algorithm>
#include <iostream>

GlobalStock::GlobalStock(int ecnt)
    : expected(ecnt), count(0) {
}

void GlobalStock::receiveQuote(const std::string& exch, const Quote& qt) {
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
            count = 0;
        }

        std::cout << "All quotes received. Performing arbitrage on sorted data:\n";
        for (const auto& q : sortedQuotes) {
            std::cout << q.exch << ": " << q.price << "\n";
        }
    }
}