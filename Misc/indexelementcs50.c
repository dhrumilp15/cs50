//Outputs an array of length given by the user (w/cs50 library)

//Get libraries
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Init array length
    int length = 0;

    //Get array length from user - length > 0
    do
    {
        length = get_int("Positive Array Length: ");
    }
    while (length <= 0);

    //Init array
    int array[length];

    //Formatting to look like an array
    printf("{");
    for (int i = 0; i < length; i++)
    {
        array[i] = i;
        printf("%d", array[i]);
        //Print a comma unless at the last element
        if (i != length - 1)
        {
            printf(",");
        }
    }
    printf("}\n");
    return 0;
}
