//Brute Force alg to decrypt hashes encrypted with crypt() for up to 5 characters

//Get Libraries - 2 directly below needed for crypt()
#define _XOPEN_SOURCE
#include <unistd.h>

#define alphabet 52

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    //Included in specification
    if (!(argc == 2))
    {
        printf("Usage: ./crack hash");
        return 1;
    }

    string uhash = argv[1]; // to store it to avoid continuously checking for the second argument later on
    string salt = "50"; //cs"50"

    //Creates a string (1-dimensional array of characters) to hold the upper- and lowercase alphabet
    char letters[alphabet];

    //Capital letter initialization
    int i = (int) 'A';

    //Capital letter generation
    for (int j = 0; j < 26; j++)
    {
        letters[j] = i;
        i++;
    }

    //Lowercase letter initialization
    int j = (int) 'a';

    //Lowercase letter generation
    for (int k = 26; k < alphabet; k++)
    {
        letters[k] = j;
        j++;
    }

    //Create the password
    char pass[5];
    pass[4] = '\0';

    //character = c, 1c
    for (int l = 0; l < alphabet; l++)
    {
        pass[0] = letters[l];

        if (strcmp(crypt(pass, salt), uhash) == 0)
        {
            printf("%s\n", pass);
            return 0; // To ensure that the program doesn't continue running after getting the password
        }

        //2c
        for (int m = 0; m < alphabet; m++)
        {
            pass[1] = letters[m];

            if (strcmp(crypt(pass, salt), uhash) == 0)
            {
                printf("%s\n", pass);
                return 0;
            }

            //3c
            for (int n = 0; n < alphabet; n++)
            {
                pass[2] = letters[n];

                if (strcmp(crypt(pass, salt), uhash) == 0)
                {
                    printf("%s\n", pass);
                    return 0;
                }

                //4c
                for (int o = 0; o < alphabet; o++)
                {
                    pass[3] = letters[n];

                    if (strcmp(crypt(pass, salt), uhash) == 0)
                    {
                        printf("%s\n", pass);
                        return 0;
                    }

                    //5c
                    for (int p = 0; p < alphabet; p++)
                    {
                        pass[4] = letters[n];

                        if (strcmp(crypt(pass, salt), uhash) == 0)
                        {
                            printf("%s\n", pass);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
