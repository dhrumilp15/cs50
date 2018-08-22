#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    //Error-checking
    
    //Not 4 command-line arguments
    if (!(argc == 4))
    {
        fprintf(stderr, "bad, usage: ./resize.c n infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);
    
    //Resizing integer is not between 0 and 100
    if (n > 100 || n <= 0)
    {
        fprintf(stderr, "Hey make sure n is a natural number > 0\n");
    }

    char *infile = argv[2];
    char *outfile = argv[3];

    FILE *inptr = fopen(infile, "r");
    //Can't open infile
    if (!inptr)
    {
        fprintf(stderr, "couldn't open %s\n", infile);
        return 1;
    }

    FILE *outptr = fopen(outfile, "w");
    //Can't make outfile
    if (!outptr)
    {
        fclose(inptr);
        fprintf(stderr, "couldn't create %s\n", outfile);
        return 1;
    }
    //Allocate memory for a bitmapfileheader and call that memory bf
    BITMAPFILEHEADER bf;
    //Read infile's file header
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    //Allocate memory for a bitmapfileheader and call that memory bf
    BITMAPINFOHEADER bi;
    
    //Read infile's info header
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }
    
    //Old padding, given formula
    int padding = (4 - (bi.biWidth * (sizeof(RGBTRIPLE)) % 4)) % 4;
    
    //New condensed formula(extra step of "n (mod 4)" for very large values of n)
    int padding_new = (padding * (n % 4)) % 4;

    int width_old = bi.biWidth;

    int height_old = bi.biHeight;
    
    //Width and Height scale by n
    bi.biWidth *= n;

    bi.biHeight *= n;
    
    //Same as given formula but with new values
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding_new) * abs(bi.biHeight);

    bf.bfSize = sizeof(BITMAPFILEHEADER) + bi.biSizeImage + sizeof(BITMAPINFOHEADER);
    
    //Write new file header
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write new BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //For each scanline of infile
    for (int i = 0; i < abs(height_old); i++)
    {
        //Will represent scanlines of outfile
        for (int j = 0; j < n; j++)
        {
            //For each pixel in infile
            for (int k = 0; k < width_old; k++)
            {
                //Read the pixel and store it
                
                RGBTRIPLE triple;

                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                //Write each of infile's pixels n times in outfile (Resize horizontally)
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            //Add outfile's padding to denote line ending
            for (int m = 0; m < padding_new; m++)
            {
                fputc(0x00, outptr);
            }

            //Go back to the beginning of the infile's scanline "n - 1" times since one of the outfile's scanlines has already been written once
            if (j < (n - 1))
            {
                fseek(inptr, - (sizeof(RGBTRIPLE)*width_old), SEEK_CUR);
            }
        }
        // skip over infile's padding
        fseek(inptr, padding, SEEK_CUR);

    }

    fclose(inptr);
    fclose(outptr);

    return 0;
}
