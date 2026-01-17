#pragma once
#include "Order.hpp"
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

class LimitOrderBook {
private:
    // Using std::map for automatic sorting of orders.
    // Complexity: Insertion and Deletion are O(log n).
    // Asks (Lowest price first)
    std::map<Order::Price, std::vector<Order>> asks;

    // Bids (Highest price first)
    std::map<Order::Price, std::vector<Order>, std::greater<Order::Price>> bids;

public:
    // Logic: Try to match first, store remaining liquidity.
    void addOrder(Order order) {
        if (order.side == Side::Buy) {
            matchBuyOrder(order);
        } else {
            matchSellOrder(order);
        }

        // If the order wasn't fully filled, add the remaining quantity to the book
        if (order.quantity > 0) {
            if (order.side == Side::Buy) {
                bids[order.price].push_back(order);
            } else {
                asks[order.price].push_back(order);
            }
        }
    }

    void matchBuyOrder(Order& order) {
        // Iterate through sellers starting from the cheapest price
        for (auto it = asks.begin(); it != asks.end(); ) {
            auto& price = it->first;
            auto& askOrders = it->second;

            // If the cheapest seller is too expensive, no trade is possible.
            if (price > order.price) break;

            // Match against liquidity at this price level
            for (auto orderIt = askOrders.begin(); orderIt != askOrders.end(); ) {
                Order& sellOrder = *orderIt;
                
                // Calculate trade size
                auto fillQty = std::min(order.quantity, sellOrder.quantity);
                std::cout << "[EXECUTION] Sold " << fillQty << " BTC @ " << price << "\n";

                order.quantity -= fillQty;
                sellOrder.quantity -= fillQty;

                // Cleanup: Remove filled orders from the book
                if (sellOrder.quantity == 0) {
                    orderIt = askOrders.erase(orderIt);
                } else {
                    ++orderIt;
                }

                if (order.quantity == 0) return; // Buy order fully filled
            }
            
            // Cleanup: Remove empty price levels to save memory
            if (askOrders.empty()) {
                it = asks.erase(it);
            } else {
                ++it;
            }
        }
    }

    void matchSellOrder(Order& order) {
        // Iterate through buyers starting from the highest bidder
        for (auto it = bids.begin(); it != bids.end(); ) {
            auto& price = it->first;
            auto& bidOrders = it->second;

            if (price < order.price) break; // Buyers are paying too little

            for (auto orderIt = bidOrders.begin(); orderIt != bidOrders.end(); ) {
                Order& buyOrder = *orderIt;
                
                auto fillQty = std::min(order.quantity, buyOrder.quantity);
                
                std::cout << "[EXECUTION] Bought " << fillQty << " BTC @ " << price << "\n";

                order.quantity -= fillQty;
                buyOrder.quantity -= fillQty;

                if (buyOrder.quantity == 0) {
                    orderIt = bidOrders.erase(orderIt);
                } else {
                    ++orderIt;
                }

                if (order.quantity == 0) return;
            }

            if (bidOrders.empty()) {
                it = bids.erase(it);
            } else {
                ++it;
            }
        }
    }

    void printBook() const {
        std::cout << "\n--- ORDER BOOK SNAPSHOT ---\n";
        std::cout << "ASKS (Sellers)\n";
        for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
             for (const auto& o : it->second) {
                 std::cout << "Price: " << it->first << " | Qty: " << o.quantity << "\n";
             }
        }
        std::cout << "\n";
        std::cout << "BIDS (Buyers)\n";
        for (const auto& [price, orders] : bids) {
            for (const auto& o : orders) {
                std::cout << "Price: " << price << " | Qty: " << o.quantity << "\n";
            }
        }
        std::cout << "\n";
    }
};
