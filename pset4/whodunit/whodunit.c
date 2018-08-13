#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    if (!(argc == 3))
    {
        fprintf(stderr, "Non! Usage: ./whodunit infile outfile\n");
        return 1; //Not 3 commandline args
    }

    char *infile = argv[1];
    char *outfile = argv[2];

    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "baguette! couldn't open infile for reading\n");
        return 2;
    }

    FILE *outptr = fopen(outfile, "w");
    if (!outptr)
    {
        fclose(inptr);
        fprintf(stderr, "bad! couldn't create that outfile\n");
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "stop, Not a 24-bit bmp can't help you\n");
        return 4;
    }

    int colour = 0x000000;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            if (triple.rgbtRed == 0xff)
            {
                fwrite(&colour, sizeof(RGBTRIPLE), 1, outptr);
            }
            else
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
