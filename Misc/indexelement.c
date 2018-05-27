//Outputs an array of length given as a commandline argument (w/out cs50.h)

//Get libraries
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //Only want 1 command line argument
    if (!(argc == 2))
    {
        return 1;
    }

    int length = 0;
    //The given length must be an integer and greater than 0
    if (atoi(argv[1]) > 0)
    {
        length = atoi(argv[1]);
    }
    else
    {
        return 1;
    }

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
