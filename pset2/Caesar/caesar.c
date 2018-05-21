//Enciphers text user provides with a key given as a commandline argument

//Get libraries
#include <cs50.h> //get_string
#include <ctype.h> //islower and isupper
#include <stdio.h> //printf()
#include <stdlib.h> //atoi()
#include <string.h> //strlen

int main(int argc, string argv[])
{

    int key = 0; // Initialize some variable that will hold the value of the key in the main()

    if (argc == 2) // If # of command line args is 2 (What we want)
    {
        key = atoi(argv[1]); //Turn the value in the second value of the array to a number
    }
    else // if less or more than 2 then there is a mistake.
    {
        printf("Mais non non big mistak\n");
        return 1;
    }
    string plaintext = get_string("plaintext: "); // Prompt user for plaintext

    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++) //Iterate over the string
    {
        if (isupper(plaintext[i])) //If the letter is a capital
        {
            printf("%c", (((plaintext[i] - ((int)'A')) + key) % 26) + ((int)'A')); //Add to capital letter
        }

        else if (islower(plaintext[i]))  //Add to lowercase letter
        {
            printf("%c", (((plaintext[i] - ((int)'a')) + key) % 26) + ((int)'a'));
        }

        else // If it's not alphabetic then just print whatever the character is
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}
