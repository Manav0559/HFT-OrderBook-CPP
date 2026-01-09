#!/bin/bash

# Part 1: Compile the C++ Code ONE time
# We do this first to make sure we are running the latest version of your engine.
echo "Compiling C++ Engine..."
cd build
clang++ -std=c++17 ../src/main.cpp -I../include -o hft_engine

# Go back to the main folder to find the Python script
cd ..

# Part 2: The Infinite Loop
echo "Starting Live Trading Dashboard (Press Ctrl+C to stop)..."

while true; do
    # A. Run the Python script to get FRESH prices from Binance
    # This overwrites 'market_data.csv' with new numbers.
    python3 fetch_data.py > /dev/null 2>&1  # (The > /dev/null hides the python output so it looks cleaner)
    
    # B. Clear the terminal screen
    # This makes it look like a refreshing dashboard instead of a scrolling log.
    clear
    
    # C. Run the C++ Engine
    # It reads the new CSV file and prints the order book.
    ./build/hft_engine
    
    # D. Wait for 1 second
    # We pause so we don't spam Binance and get banned.
    sleep 1
done