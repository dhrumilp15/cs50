#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    //Error Checking

    if (!(argc == 4))
    {
        fprintf(stderr, "bad, usage: ./resize.c n infile outfile\n");
        return 1;
    }

    //Initialize Scaling Factor
    float n = 0.0;

    sscanf(argv[1], "%f", &n);

    if (n <= 0.0 || n > 100.0)
    {
        fprintf(stderr, "give rational number between 0 and 100\n");
        return 1;
    }

    //File initialization

    char *infile = argv[2];
    char *outfile = argv[3];

    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "couldn't open %s\n", infile);
        return 1;
    }

    FILE *outptr = fopen(outfile, "w");
    if (!outptr)
    {
        fclose(inptr);
        fprintf(stderr, "couldn't create %s\n", outfile);
        return 1;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }

    int padding = (4 - (bi.biWidth * (sizeof(RGBTRIPLE)) % 4)) % 4;

    int width_old = bi.biWidth;

    int height_old = bi.biHeight;

    bi.biWidth = floor(bi.biWidth * n);

    bi.biHeight = ceil(bi.biHeight * n);

    int padding_new = (4 - (bi.biWidth * (sizeof(RGBTRIPLE)) % 4)) % 4;

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding_new) * abs(bi.biHeight);

    bf.bfSize = sizeof(BITMAPFILEHEADER) + bi.biSizeImage + sizeof(BITMAPINFOHEADER);

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    float hater; //Horizontal iterator(h_iter sounds like hater)
    float vader = n; //Vertical iterator(v_iter sounds like vader)

    int iter = 0; //Spare iterator - two variables need to change at different places
    int jiter;

    for (int i = 0; i < abs(height_old); i++)
    {

        while (iter < (int)vader)
        {
            hater = n; //Need to reinitialize this for each scanline of outfile
            jiter = 0;

            for (int k = 0; k < width_old; k++)
            {
                RGBTRIPLE triple;

                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                while (jiter < (int)hater)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    jiter++;
                }
                hater += n;

            }

            fseek(inptr, padding, SEEK_CUR);

            //Add outfile's padding
            for (int m = 0; m < padding_new; m++)
            {
                fputc(0x00, outptr);
            }

            iter++;

            fseek(inptr, - (int)(sizeof(RGBTRIPLE) * width_old + padding), SEEK_CUR);
        }

        vader += n;

        // skip over infile's padding
        fseek(inptr, (int)(sizeof(RGBTRIPLE) * width_old + padding), SEEK_CUR);
    }

    fclose(inptr);
    fclose(outptr);

    return 0;
}
