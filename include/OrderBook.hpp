#pragma once
#include "Order.hpp"
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

class LimitOrderBook {
private:
    std::map<Order::Price, std::vector<Order>> asks;
    std::map<Order::Price, std::vector<Order>, std::greater<Order::Price>> bids;

public:
    void addOrder(const Order& order) {
        if (order.side == Side::Buy) {
            bids[order.price].push_back(order);
        } else {
            asks[order.price].push_back(order);
        }
    }

    void printBook() const {
        std::cout << "--- ASKS (Sellers) ---\n";
        for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
             for (const auto& o : it->second) {
                 std::cout << "[ASK] Price: " << it->first << " Qty: " << o.quantity << "\n";
             }
        }
        std::cout << "--- BIDS (Buyers) ---\n";
        for (const auto& [price, orders] : bids) {
            for (const auto& o : orders) {
                std::cout << "[BID] Price: " << price << " Qty: " << o.quantity << "\n";
            }
        }
        std::cout << "---------------------\n";
    }
};