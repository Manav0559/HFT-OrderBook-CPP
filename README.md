# High-Frequency Limit Order Book (C++)

A low-latency Limit Order Book (LOB) implementation in C++ designed for high-frequency trading simulations. This engine supports real-time order matching (Price-Time priority) and ingests live market data from Binance.

## Features
* **Matching Engine:** Implements Standard Price-Time priority matching.
* **Data Structures:** Uses `std::map` for ordered price levels (O(log n) insertions).
* **Market Data:** Includes a Python adapter (`fetch_data.py`) to stream real-time BTC/USDT depth from Binance.
* **Simulation:** Shell script automation (`run_live.sh`) to mimic a live trading terminal.

## Architecture
* `OrderBook.hpp`: The core engine logic managing Bids and Asks.
* `Order.hpp`: Fixed-width integer definitions for Price/Quantity (avoiding floating-point errors).
* `main.cpp`: The entry point that parses CSV data and executes trades.

## How to Run
**Prerequisites:** Mac/Linux, C++17 compiler (Clang/GCC), Python 3.

1.  **Clone the repository**
    ```bash
    git clone [https://github.com/Manav0559/HFT-OrderBook-CPP.git](https://github.com/Manav0559/HFT-OrderBook-CPP.git)
    cd HFT-OrderBook-CPP
    ```

2.  **Run the Live Simulation**
    This script compiles the engine, fetches data, and updates the book every second.
    ```bash
    chmod +x run_live.sh
    ./run_live.sh
    ```

## Future Improvements
* Replace `std::map` with a flat vector or memory pool for better cache locality.
* Implement TCP/IP socket listeners for direct exchange connectivity.