from cs50 import get_float
from math import floor

def main():
    change = get_float("How much change doth thou need: ")
    while not (change >= 0):
        change = get_float("How much change doth thou need: ")
    
    change = floor(change * 100)
    
    coins = change // 25
    
    coins += (change % 25) // 10
    
    coins += ((change % 25) % 10) // 5
    
    coins += ((change % 25) % 10) % 5
    
    print(int(coins))

if __name__ == "__main__":
    main()