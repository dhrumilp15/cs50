//Validates VISA, MRCD, AMEX credit card numbers

//Get Libraries
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) //Start
{
    long long card; // Card number

    int count = 0; //Number of digits in card
    int checksum = 0; // Output of Luhn's alg

    do
    {
        card = get_long_long("What's your card number: ");
    }
    while (card < 0); // Use card number as long as it's below 0

    long long numbers = card; // Check how many digits in card number

    while (numbers > 0)
    {
        numbers /= 10;
        count++;
    }

    //printf("%d \n", count); // Checkpoint to see if everything so far works correctly

    if (count < 13 || count > 16 || count == 14) // Print invalid if the number of digits is invalid
    {
        printf("INVALID\n");
    }

    int digits[count]; //Array that will hold single-digit values of the card number Initializing array size here

    for (int i = 0; i < count; i++) // Put digits of card number inside array
    {
        digits[i] = card % 10;
        card /= 10;
        //printf("%d", digits[i]);
    }
    //printf("\n");

    for (int j = 1; j < count; j += 2) // Count double every other digit
    {
        if ((2 * digits[j]) > 9)
        {
            checksum += (((2 * digits[j]) % 10) + 1);
        }
        else
        {
            checksum += (2 * digits[j]);
        }
        //printf("%d", digits[j]);
    }

    for (int k = 0; k < count; k += 2) //Count the remaining digits
    {
        checksum += digits[k];
    }

    //printf("%d\n", checksum);

    if (count == 15) // AMEX
    {
        if ((digits[14] == 3 && (digits[13] == 4 || digits[13] == 7)))
        {
            if (checksum % 10 == 0)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }

    if (count == 16) //MASTERCARD or VISA
    {
        if (checksum % 10 == 0)
        {
            if (digits[15] == 5 && (digits[14] == 1 || digits[14] == 2 || digits[14] == 3 || digits[14] == 4 || digits[14] == 5))
            {
                printf("MASTERCARD\n");
            }
            else if (digits[15] == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }

        }
        else
        {
            printf("INVALID\n");
        }
    }

    if (count == 13) //VISA
    {
        if (digits[12] == 4)
        {
            if (checksum % 10 == 0)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }

    return 0;
}
