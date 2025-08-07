#pragma once
#ifndef ARBITRAGEENGINE_H
#define ARBITRAGEENGINE_H

#include <vector>
#include <string>
#include <mutex>
#include <unordered_map>
#include <atomic>
#include "Quote.h"

class ArbitrageEngine {
private:
    std::unordered_map<std::string, Quote> quotes;
    std::mutex mtx;
    const int expected;
    std::atomic<int> count;

    void performArbitrage(const std::vector<Quote>& sortedQuotes);

public:
    ArbitrageEngine(int expectedQuotes);
    void receiveQuote(const std::string& exch, const Quote& qt);
};

#endif
