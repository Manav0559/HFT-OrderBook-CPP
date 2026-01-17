import requests
import csv
import time

# 1. Connect to Binance Public API
url = "https://api.binance.com/api/v3/depth"
params = {"symbol": "BTCUSDT", "limit": 10}

print("Fetching data from Binance...")
response = requests.get(url, params=params)
data = response.json()

# 2. Open a CSV file to save the data
filename = "market_data.csv"
with open(filename, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["id", "side", "price", "quantity"])
    
    order_id = 1
    
    # 3. Write Bids (Buyers)
    for bid in data['bids']:
        price_float = float(bid[0])
        qty_float = float(bid[1])
        
        # Convert to Integer format for HFT (multiply by 100 to keep cents)
        price_int = int(price_float * 100) 
        qty_int = int(qty_float * 1000)
        
        writer.writerow([order_id, 0, price_int, qty_int]) 
        order_id += 1
        
    # 4. Write Asks (Sellers)
    for ask in data['asks']:
        price_float = float(ask[0])
        qty_float = float(ask[1])
        
        price_int = int(price_float * 100)
        qty_int = int(qty_float * 1000)
        
        writer.writerow([order_id, 1, price_int, qty_int])
        order_id += 1

print(f"Success! Data saved to {filename}")
