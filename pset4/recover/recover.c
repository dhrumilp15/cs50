#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    //Error - Checking
    if (!(argc == 2))
    {
        fprintf(stderr, " bad! Usage: ./recover card.raw\n");
        return 1;
    }

    //Get card.raw and error - checking
    char *rawfile = argv[1];

    FILE *rawptr = fopen(rawfile, "r");

    if (!rawptr)
    {
        fprintf(stderr, "baguette! couldn't open infile for reading\n");
        return 1;
    }

    //"buffer" has space for 512 spots that are 1 byte in size.
    unsigned char buffer[512];

    //Will be the jpeg file name
    int jpgnum = 0;

    //Boolean for whether a jpg has already been opened
    bool existingjpg = false;

    //pointer to the jpg
    FILE *img = NULL;

    while (fread(buffer, 1, 512, rawptr) == 512) //Will pick up 512 objects 1 byte in size
    {
        //If jpg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //string to hold file name
            char filename[8];

            sprintf(filename, "%03i.jpg", jpgnum);//Formats name to: "0xx.jpg"

            jpgnum++;

            //If a jpg has already been opened
            if (existingjpg)
            {
                fclose(img); //Close the opened jpg
            }

            img = fopen(filename, "w"); //Set pointer to new jpg

            existingjpg = true; //Preemptively set existingjpg to true
        }

        //If a jpg has already been opened and it's not the start of another one
        if (existingjpg)
        {
            fwrite(&buffer, 512, 1, img);//Write the buffer into the file.
        }
    }

    fclose(rawptr);
    return 0;
}
