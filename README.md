# High-Frequency Limit Order Book (C++)

![C++](https://img.shields.io/badge/language-C%2B%2B17-blue)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![Latency](https://img.shields.io/badge/latency-1.21_us-firebrick)

A low-latency Limit Order Book (LOB) implementation designed for high-frequency trading simulations.

## Live Demo
https://github.com/Manav0559/HFT-OrderBook-CPP/assets/https://github.com/user-attachments/assets/fd49aa0a-f0cf-49a5-9b80-f080e0380dbd


## Performance Benchmarks
Tested on MacBook Air (Apple Silicon):
* **Average Latency:** 1.21 microseconds/order
* **Throughput:** ~800000 orders/se

## Features
* **Matching Engine:** Standard Price-Time priority (FIFO) matching logic.
* **Data Structures:** `std::map` (Red-Black Tree) for ordered price levels; `std::vector` for order queues.
* **Live Feed:** Integrated Python adapter to stream real-time Binance BTC/USDT market depth.
* **Optimization:** Uses fixed-point arithmetic (integers) to avoid floating-point errors and latency.

## How to Run

**1. Live Trading Simulation:**
This script fetches data from Binance and updates the book in real-time.
```bash
chmod +x run_live.sh
./run_live.sh
