/**
 * @file            resize.c
 * @brief           Scales up a bmp image by factor n
 * @author          Berat BAYRAM
 * @date            27 September 2020
 * 
 * @param n         Positive integer which is the scale factor of the image
 * @param infile    bmp image to be scaled
 * @param ourfile   Output file
 * 
 * @warning         Only up-scaling from 24-bit uncompressed BMP 4.0 files are 
 *                  supported
 * @note            Forked from Harvard University CS50 team's copy.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }

    //	is second arguement	an integer ?
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (argv[1][i] < '0' && '9' < argv[1][i])
        {
            fprintf(stderr, "n must be an positive integer\n");
            return 1;
        }
    }

    //match args
    int factor = atoi(argv[1]);

    if (factor < 1)
    {
        fprintf(stderr, "n must be an positive integer\n");
        return 1;
    }
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's headers
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //set widths and heights
    int widthIn = bi.biWidth;
    int widthOut = widthIn * factor;
    int heightIn = bi.biHeight;
    int heightOut = heightIn * factor;

    //calculate paddings
    int paddingIn = (4 - (widthIn * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingOut = (4 - (widthOut * sizeof(RGBTRIPLE)) % 4) % 4;

    //update header values for new output
    bi.biWidth = widthOut;
    bi.biHeight = heightOut;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + paddingOut) *
                     abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage +
                sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's headers
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    heightIn = abs(heightIn);
    heightOut = abs(heightOut);

    // dynamically allocate space for the temporary array
    RGBTRIPLE **temp = (RGBTRIPLE **)malloc(heightIn * sizeof(RGBTRIPLE *));
    if (temp == NULL)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Could not allocate space.\n");
        return 5;
    }
    for (int i = 0; i < heightIn; i++)
    {
        temp[i] = (RGBTRIPLE *)malloc(widthIn * sizeof(RGBTRIPLE));
        if (temp[i] == NULL)
        {
            fclose(inptr);
            fclose(outptr);
            fprintf(stderr, "Could not allocate space.\n");
            return 6;
        }
    }

    // cache input file
    for (int i = 0; i < heightIn; i++)
    {
        for (int j = 0; j < heightIn; j++)
        {
            // read temp array from infile
            fread(&temp[i][j], sizeof(RGBTRIPLE), 1, inptr);
        }

        // skip over padding, if any
        fseek(inptr, paddingIn, SEEK_CUR);
    }

    // write output
    for (int i = 0; i < heightOut; i++)
    {
        for (int j = 0; j < widthOut; j++)
        {
            // write write temp array to outfile
            fwrite(&temp[i / factor][j / factor], sizeof(RGBTRIPLE), 1, outptr);
        }

        // add paddings, if any
        for (int k = 0; k < paddingOut; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close files
    fclose(inptr);
    fclose(outptr);

    // de-allocate the array
    for (int i = 0; i < heightIn; i++)
        free(temp[i]);
    free(temp);

    // success
    return 0;
}
