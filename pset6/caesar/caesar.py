from cs50 import get_string
import sys

def main():
    if len(sys.argv) == 2:
        key = int(sys.argv[1])
    else:
        print("Non you grand baguette")
        sys.exit(1)
        return
    
    plaintext = get_string("plaintext: ")
    
    print("ciphertext: ",end="")
    
    for i in plaintext:
        if i.isupper():
            print( chr((ord(i) - 65 + key) % 26 + 65), end="")
        elif i.islower():
            print( chr((ord(i) - 97 + key) % 26 + 97), end="")
        else:
            print(i,end="")
    print()
if __name__ == "__main__":
    main()
            