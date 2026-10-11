// Minimal regression tests for LimitOrderBook (no external framework).
#include <cstdlib>
#include <iostream>
#include "OrderBook.hpp"

static int failures = 0;

#define CHECK(cond)                                                        \
    do {                                                                   \
        if (!(cond)) {                                                     \
            std::cerr << "FAIL " << __FILE__ << ":" << __LINE__ << "  "    \
                      << #cond << "\n";                                    \
            ++failures;                                                    \
        }                                                                  \
    } while (0)

// An incoming buy that exactly consumes the last order at a level must
// remove that ask level from the book.
static void buy_fully_filled_erases_ask_level() {
    LimitOrderBook book;
    book.addOrder(Order(1, Side::Sell, 100, 5, OrderType::GoodTillCancel));
    book.addOrder(Order(2, Side::Sell, 101, 5, OrderType::GoodTillCancel));
    book.addOrder(Order(3, Side::Buy, 100, 5, OrderType::GoodTillCancel));
    CHECK(!book.hasAskLevel(100));
    CHECK(book.hasAskLevel(101));
    CHECK(book.askLevelCount() == 1);
    CHECK(book.bidLevelCount() == 0);
}

// Mirror case: an incoming sell that exactly consumes a bid level.
static void sell_fully_filled_erases_bid_level() {
    LimitOrderBook book;
    book.addOrder(Order(1, Side::Buy, 100, 5, OrderType::GoodTillCancel));
    book.addOrder(Order(2, Side::Buy, 99, 5, OrderType::GoodTillCancel));
    book.addOrder(Order(3, Side::Sell, 100, 5, OrderType::GoodTillCancel));
    CHECK(!book.hasBidLevel(100));
    CHECK(book.hasBidLevel(99));
    CHECK(book.bidLevelCount() == 1);
    CHECK(book.askLevelCount() == 0);
}

// A partial fill keeps the level; the remainder rests.
static void partial_fill_keeps_level() {
    LimitOrderBook book;
    book.addOrder(Order(1, Side::Sell, 100, 10, OrderType::GoodTillCancel));
    book.addOrder(Order(2, Side::Buy, 100, 4, OrderType::GoodTillCancel));
    CHECK(book.hasAskLevel(100));
    CHECK(book.bidLevelCount() == 0);
}

int main() {
    buy_fully_filled_erases_ask_level();
    sell_fully_filled_erases_bid_level();
    partial_fill_keeps_level();
    if (failures) {
        std::cerr << failures << " check(s) failed\n";
        return EXIT_FAILURE;
    }
    std::cout << "all orderbook tests passed\n";
    return EXIT_SUCCESS;
}
