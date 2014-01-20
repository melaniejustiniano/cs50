/*
 * Problem Set 4 - Resize
 * Melanie Justiniano <melaniejustiniano@college.harvard.edu>
 *
 * Resizes an image by a given value.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // disallows improper command line input
    if (argc != 4)
    {
        printf("Proper usage: resize n input output \n");
        return 1;
    }
    
    // disallows non-integer command line input 
    string n = argv[1];
    int length = strlen(n);
    
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(n[i]))
        {
            printf("Your factor must be a non-negative integer! \n");
            return 2;
        }
    }
    
    // turns command line input to integer
    int factor = atoi(n);
    
    // disallows integers over 100
    if (factor > 100 || factor == 0)
    {
        printf("Your factor must be between 1 and 100! \n");
        return 3;
    }
    
    // name command line files
    char* input = argv[2];
    char* output = argv[3];
    
    // open input file 
    FILE* inpointer = fopen(input, "r");
    
    if (inpointer == NULL)
    {
        printf("Could not open %s.\n", input);
        return 4;
    }

    // open output file
    FILE* outpointer = fopen(output, "w");
    
    if (outpointer == NULL)
    {
        fclose(inpointer);
        fprintf(stderr, "Could not create %s.\n", output);
        return 5;
    }

    // read input's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inpointer);

    // read input's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inpointer);

    // ensure input is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(inpointer);
        fclose(outpointer);
        fprintf(stderr, "Unsupported file format.\n");
        return 6;
    }
    
    // save old data from input for reading
    int oldPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;
    int oldSizeImage = bi.biSizeImage;
   
    // change BITMAPINFOHEADER and padding for output
    bi.biWidth *= factor;
    bi.biHeight *= factor;
    
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + newPadding) * abs(bi.biHeight);
    
    // change BITMAPFILEHEADER to reflect changes in BITMAPINFOHEADER
    bf.bfSize = bf.bfSize - oldSizeImage + bi.biSizeImage;
    
    // write output's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outpointer);

    // write output's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outpointer);

    // iterate over each line
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
        // copy each line factor times
        for (int j = 0; j < factor; j++)
        {            
            // iterate over each pixel in each line
            for (int k = 0; k < oldWidth; k++)
            {
                // read RGB triple from infile
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inpointer);
          
                // copy each pixel factor times
                for (int x = 0; x < factor; x++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outpointer);
                }
            }
                
            // insert padding based on new width
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outpointer);
            }
                                        
            // move cursor to start of line except for on last copy
            if (j != factor - 1)
            {
                int location = -(oldWidth * sizeof(RGBTRIPLE));
                fseek(inpointer, location, SEEK_CUR);
            }
        }
        
        // skip over padding from input after lines have been copied
        fseek (inpointer, oldPadding, SEEK_CUR); 
    }

    // close files
    fclose(inpointer);
    fclose(outpointer);

    return 0;
}
