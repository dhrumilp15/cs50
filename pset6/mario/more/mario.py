from cs50 import get_int

def main():
    height = get_int("Height of Pyramid: ")
    if height == 0:
        return
    while not (height > 0 and height < 24):
        height = get_int("Height of Pyramid: ")
    
    for i in range(height):
        
        for j in range(height - (i + 1)):
            print(" ",end="")
        
        for j in range(i + 1):
            print("#",end="")
        
        print("  ",end="")
        
        for j in range(i + 1):
            print("#",end="")
        
        print()
    
if __name__ == "__main__":
    main()