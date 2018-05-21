//Prints out a half-pyramid with the top-level holding two hashes

//Get libraries
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height; // Initialize helight of half-pyramid as an integer

    do
    {
        height = get_int("Height of Half-Pyramid: ");
    }
    while ((height < 0) || (height > 23)); // Ensure that the user gives a value between 0 and 23 inclusive

    for (int i = 0; i < height; i++) // Int i is a counter to go up to height, printing as i increases
    {

        for (int j = 0; j < (height - (i + 1)); j++) // Int j will increase inside of i to print spaces
        {
            printf(" ");
        }

        for (int k = 0; k < (i + 1); k++) // Int k will increase inside of i to print hashes
        {
            printf("#");
        }
        printf("\n"); // Get a new line
    }
}
