#client
# Start demo_api in background first

import requests
from pprint import pprint # Bei größeren Dicts sollte man pprint(...) statt print(...) verwenden


def main():
  base_api_url = "http://127.0.0.1:8000"
  
  response = requests.get(base_api_url)
  response_json = response.json()
  current_guess = response_json['Game']
  print(f"Game: '{run_game}'")
  

if __name__ == '__main__':
  main()
