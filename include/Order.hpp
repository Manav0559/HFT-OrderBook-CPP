#pragma once
#include <cstdint>
#include <ctime>

enum class OrderType { GoodTillCancel, FillAndKill };
enum class Side { Buy, Sell };

struct Order {
    using Price = int32_t;
    using Quantity = uint32_t;
    using OrderId = uint64_t;

    OrderId orderId;
    Side side;
    Price price;
    Quantity quantity;
    OrderType type;
    std::time_t timestamp;

    Order(OrderId id, Side s, Price p, Quantity q, OrderType t)
        : orderId(id), side(s), price(p), quantity(q), type(t) {
        timestamp = std::time(nullptr);
    }
};