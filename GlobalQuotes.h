#pragma once
#ifndef GLOBALSTOCK_H
#define GLOBALSTOCK_H

#include <vector>
#include <atomic>
#include <mutex>
#include <cstdint>
#include <string>
#include <optional>
#include <unordered_map>
#include "Quote.h"

class GlobalStock {
private:
    std::unordered_map<std::string, Quote> quotes;
    std::mutex mtx;
    const int expected;
    std::atomic<int> count;

public:
    GlobalStock(int ecnt = 10);
    void receiveQuote(const std::string& exch, const Quote& qt);
};

#endif