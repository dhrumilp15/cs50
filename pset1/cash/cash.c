//Executes a greedy alg for counting coins

//Get Libraries
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) //Start
{
    int coins = 0;
    int pennies;
    float change;

    do
    {
        change = get_float("How much change doth thou needeth: ");
    }
    while (change <= 0); //Continually ask for change until the client/customer gives a real value. No debt

    while (change >= 0.25) // If total amount of change is more than or equal to 24 cents, decrease 25 cents
    {
        coins++;
        change = change - 0.25;
    }

    while (change >= 0.10) // If total amount of change is more than or equal to 9 cents, decrease 10 cents
    {
        coins++;
        change = change - 0.10;
    }

    while (change >= 0.05) // If total amount of change is more than or equal to 4 cents, decrease 5 cents
    {
        coins++;
        change = change - 0.05;
    }

    if (change <= 0.04) // Add the rest of the change to the coins as they must be lower than or equal to 4 cents
    {
        pennies = round(change * 100); //Turn the cents into coins by *100 and round to take care of imprecision
        coins = coins + pennies;
    }

    printf("%d\n", coins); //Print coins

    return 0;
}
