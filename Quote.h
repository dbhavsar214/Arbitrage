#pragma once

#ifndef QUOTE_H
#define QUOTE_H

#include <string>

struct Quote {
    double price;
    std::string exch;

    bool operator<(const Quote& qt) const {
        return price < qt.price;
    }
};

#endif