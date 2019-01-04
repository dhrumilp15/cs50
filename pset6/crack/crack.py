from crypt import crypt
import sys

def main():
    if not len(sys.argv) == 2:
        print("Non you garnd baguette")
        sys.exit(1)
        return
    
    userhash = sys.argv[1]
    
    alphabet = []
    
    for i in range(65,91):
        alphabet.append(chr(i))
    
    for i in range(97,123):
        alphabet.append(chr(i))
    
    salt = "50"
    
    password = ""
    
    for i in alphabet:
        password += i
        
        if (crypt(password, salt) == userhash):
            print(password)
            return
        
        for j in alphabet:
            password += j
            
            if (crypt(password, salt) == userhash):
                print(password)
                return
            
            for k in alphabet:
                password += k
            
                if (crypt(password, salt) == userhash):
                    print(password)
                    return
                
                for l in alphabet:
                    password += l
                
                    if (crypt(password, salt) == userhash):
                        print(password)
                        return
                
                    for m in alphabet:
                        password += m
                    
                        if (crypt(password, salt) == userhash):
                            print(password)
                            return
        