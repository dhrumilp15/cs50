//Checks if a triangle has valid side lengths
//One of the challenges in the shorts
//Get libraries
#include <stdio.h>
#include <cs50.h>

//Declare functions - "I'm going to create a function"
bool valid_triangle(float x, float y, float z);

int main(void)
{
    //Declare variables
    float x, y, z;

    //Three do-while loops so that the user doesn't have to input all three variables each time they enter invalid input
    do
    {
        x = get_float("X: ");

    }while(x < 0);

    do
    {
        y = get_float("Y: ");

    }while(y < 0);

    do
    {
        z = get_float("Z: ");

    }while(z < 0);

    bool isTriangle = valid_triangle(x, y, z); //Calling the function

    if (isTriangle) //Printing the result
    {
        printf("True\n");
    } else
    {
        printf("False\n");
    }
}

//Real computation --> if a + b > c, a,b, and c make a triangle
bool valid_triangle(float x, float y, float z)
{
    if (((x + y) > z) && ((x + z) > y) && ((z + y) > x)) //Go through each case
    {
        return true;
    }
        return false;
}
