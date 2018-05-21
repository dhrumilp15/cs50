//Encrypts according to the vigenere cipher

//Get libraries
#include <cs50.h> //get_string
#include <ctype.h> //isalpha isupper islower
#include <stdio.h> //printf
#include <string.h> //strlen

int main(int argc, string argv[])
{
    string key = argv[1]; //Getting the second element of the string array

    //There has to be 1 alphabetical command line argument
    if (argc == 2)
    {
        for (int i = 0; i < strlen(key); i++) //Iterate through the string
        {
            if (!(isalpha(key[i]))) //Check if each letter is not alphabetical
            {
                printf("Non grand baguette");
                return 1; //Return error
            }
        }
    }
    else //otherwise return error
    {
        printf("Non grand baguette");
        return 1;
    }

    string plaintext = get_string("plaintext: "); // Get plaintext
    printf("ciphertext: "); //Print ciphertext now - loops will print out a character at a time

    int j = 0; // counter - 'i' will increment with spaces and j will increment when a letter is enciphered

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]) && isupper(key[j % strlen(key)])) // uppercase plaintext and uppercase key
        {
            printf("%c", (((plaintext[i] - ((int)'A')) + key[j % strlen(key)] - 'A') % 26) + ((int)'A'));
            j++;
        }
        else if (isupper(plaintext[i]) && islower(key[j % strlen(key)])) // uppercase plaintext and lowercase key
        {
            printf("%c", (((plaintext[i] - ((int)'A')) + key[j % strlen(key)] - 'a') % 26) + ((int)'A'));
            j++;
        }
        else if (islower(plaintext[i]) && islower(key[j % strlen(key)])) // lowercase plaintext and lowercase key
        {
            printf("%c", (((plaintext[i] - ((int)'a')) + key[j % strlen(key)] -  'a') % 26) + ((int)'a'));
            j++;
        }
        else if (islower(plaintext[i]) && isupper(key[j % strlen(key)])) // lowercase plaintext and uppercase key
        {
            printf("%c", (((plaintext[i] - ((int)'a')) + key[j % strlen(key)] - 'A') % 26) + ((int)'a'));
            j++;
        }
        else // if the letter isn't alphabetic then just print it out
        {
            printf("%c", plaintext[i]);
        } // Finishing this block increments i by 1

    }
    printf("\n");
    return 0;
}
