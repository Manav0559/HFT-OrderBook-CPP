#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../include/OrderBook.hpp"
#include "../include/Order.hpp"

// Utility to parse CSV lines
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    LimitOrderBook book;
    
    // Ensure this matches your local file structure
    std::string filename = "market_data.csv"; 
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << ".\n";
        return 1;
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        auto row = split(line, ',');
        if (row.size() < 4) continue;

        try {
            Order::OrderId id = std::stoull(row[0]);
            Side side = (std::stoi(row[1]) == 0) ? Side::Buy : Side::Sell;
            Order::Price price = std::stoi(row[2]);
            Order::Quantity qty = std::stoi(row[3]);

            Order order(id, side, price, qty, OrderType::GoodTillCancel);
            book.addOrder(order);
        } catch (...) {
            continue; // Skip malformed lines
        }
    }

    book.printBook();
    return 0;
}