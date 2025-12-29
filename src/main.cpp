#include <iostream>
#include "../include/OrderBook.hpp"
#include "../include/Order.hpp"

int main() {
    LimitOrderBook book;

    // ID: 1, Buy, Price 100, Qty 10
    Order o1(1, Side::Buy, 100, 10, OrderType::GoodTillCancel);
    // ID: 2, Sell, Price 105, Qty 5
    Order o2(2, Side::Sell, 105, 5, OrderType::GoodTillCancel);

    book.addOrder(o1);
    book.addOrder(o2);

    book.printBook();
    return 0;
}