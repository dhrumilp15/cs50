// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //Divide 8 by denominator and multiply result by numerator to give duration
    int numtr = atoi(&fraction[0]);

    int dentr = atoi(&fraction[2]);

    int duration = (8 / dentr) * numtr;

    return duration;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    double n = 0.0; //This will be the exponent in the general formula: 440 * 2^(n/12)
    int octave = note[strlen(note) - 1] - '0'; //To convert the string to an integer

    if (strlen(note) == 3) //For accidentals
    {
        if (note[1] == '#')
        {
            n +=  1.0;
        }
        else if (note[1] == 'b')
        {
            n -= 1.0;
        }
    }

    n += 12.0 * (octave - 4.0); //Multiplied by 12 since an ovtave is 12 semitones

    switch (note[0]) //Cases for the 7 letters
    {
        case 'A':
            n += 0.0;
            break;

        case 'B':
            n += 2.0;
            break;

        case 'C':
            n -= 9.0;
            break;

        case 'D':
            n -= 7.0;
            break;

        case 'E':
            n -= 5.0;
            break;

        case 'F':
            n -= 4.0;
            break;

        case 'G':
            n -= 2.0;
            break;
        default:
            return 0;
    }

    float exponent = n / 12;

    float freq = round(pow(2.0, exponent) * 440);

    return freq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
