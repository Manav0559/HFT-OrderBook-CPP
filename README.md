# Limit Order Book (C++) — learning project

> **Status: superseded by [itch-lob-engine](https://github.com/Manav0559/itch-lob-engine)** —
> a NASDAQ ITCH 5.0 order-book reconstruction engine with byte-exact protocol
> decoders, an order-id book, unit tests, and Linux + macOS CI. New work
> happens there; this repo stays up as the honest starting point it was.

A small limit order book and price-time matcher written while learning the
domain: `std::map` price levels, FIFO order queues within a level, partial
fills. A Python helper fetches a Binance depth snapshot to CSV and the C++
binary rebuilds and prints the book from it.

## Honest scope

- **Add-only matcher** — no cancel, no modify, no order-id lookup
- **Snapshot replay, not a feed** — `run_live.sh` re-fetches a REST depth
  snapshot once per second and re-runs the binary; depth levels never cross,
  so the matching path is exercised by synthetic input, not live data
- **No benchmarks** — this repo publishes no performance numbers because it
  contains no benchmark code; the successor repo ships a committed,
  reproducible harness instead

## Build

```bash
cmake -B build && cmake --build build
./build/hft_engine   # replays market_data.csv (generate via fetch_data.py)
```

## What its successor does differently

Real exchange binary protocol (ITCH 5.0) instead of CSV snapshots, an order-id
locator for O(1) cancel/replace, empty-level cleanup under test, CI on a
case-sensitive filesystem, and performance claims only from committed
benchmarks. That migration — including the bugs this version taught me —
is the point of keeping both public.
