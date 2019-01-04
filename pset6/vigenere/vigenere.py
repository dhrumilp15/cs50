from cs50 import get_string
import sys

def main():
    if len(sys.argv) == 2:
        key = sys.argv[1]
        for i in key:
            if not i.isalpha():
                print("Non you grand baguette")
                sys.exit(1)
                return
    else:
        print("Non you grand baguette")
        sys.exit(1)
        return
    
    plaintext = get_string("plaintext: ")
    print("ciphertext: ", end="")
    
    j = 0
    
    for i in plaintext:
        if i.isupper() and key[j % len(key)].isupper():
            print(chr((ord(i) - 65 + ord(key[j % len(key)]) - 65) % 26 + 65), end="")
            j+= 1
        
        elif i.isupper() and key[j % len(key)].islower():
            print(chr((ord(i) - 65 + ord(key[j % len(key)]) - 97) % 26 + 65), end="")
            j+= 1
        
        elif i.islower() and key[j % len(key)].islower():
            print(chr((ord(i) - 97 + ord(key[j % len(key)]) - 97) % 26 + 97), end="")
            j += 1
        
        elif i.islower() and key[j % len(key)].isupper():
            print(chr((ord(i) - 97 + ord(key[j % len(key)]) - 65) % 26 + 97), end="")
            j += 1
        
        else:
            print(i, end="")
        
    print()

if __name__ == "__main__":
    main()