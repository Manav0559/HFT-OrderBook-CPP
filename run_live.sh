#!/bin/bash

# Part 1: Compile the C++ Code ONE time
echo "Compiling C++ Engine..."
cd build
clang++ -std=c++17 ../src/main.cpp -I../include -o hft_engine

cd ..

# Part 2: The Infinite Loop
echo "Starting Live Trading Dashboard (Press Ctrl+C to stop)..."

while true; do
    # A. Run the Python script to get FRESH prices from Binance
    # This overwrites 'market_data.csv' with new numbers.
    python3 fetch_data.py > /dev/null 2>&1
    
    # B. Clear the terminal screen
    # This makes it look like a refreshing dashboard instead of a scrolling log.
    clear
    
    # C. Run the C++ Engine
    # It reads the new CSV file and prints the order book.
    ./build/hft_engine
    
    # D. Wait for 1 second
    sleep 1
done
