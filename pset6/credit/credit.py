from cs50 import get_int

def main():
    card_int = get_int("Card number: ")
    while not (card_int > 0):
        card_int = get_int("Card number: ")
    
    card = str(card_int)
    
    if len(card) < 13 or len(card) > 16 or len(card) == 14:
        print("INVALID")
        return
    
    checksum = 0
    
    for i in card[-2::-2]:
        twoi = 2 * int(i)
        if twoi > 9:
            checksum += int(str(twoi)[0]) + int(str(twoi)[1])
        else:
            checksum += 2 * int(i)
    
    for i in card[::-2]:
        checksum += int(i)

    if len(card) == 15:
        if checksum % 10 == 0 and (card[:2] == "34" or card[:2] == "37"):
            print("AMEX")
        else:
            print("INVALID")
    
    if len(card) == 16:
        if checksum % 10 == 0:
            if card[0] == "5" and card[1] in "12345":
                print("MASTERCARD")
            elif (card[0] == "4"):
                print("VISA")
            else:
                print("INVALID")
        else:
            print("INVALID")
    
    if len(card) == 13:
        if card[0] == "4" and checksum % 10 == 0:
            print("VISA")
        else:
            print("INVALID")
if __name__ == "__main__":
    main()