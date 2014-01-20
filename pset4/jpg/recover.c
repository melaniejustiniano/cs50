/*
 * Problem Set 4 - Recover
 * Melanie Justiniano <melaniejustiniano@college.harvard.edu>
 *
 * Recovers JPEGs from a forensic image.
 *
 */
 
#include <stdio.h>
#include <cs50.h>
#include <stdint.h>

// bytes for JPEG name
#define NAMESIZE 28
#define BLOCK 512

typedef uint8_t BYTE;

int main(void)
{
    // opens CF card for reading  
    FILE* card = fopen("card.raw", "r");
    if (card == NULL)
    {
        printf("Could not open card.raw! \n");
        return 1;
    }
    
    BYTE buffer[BLOCK];
    char filename[NAMESIZE];
    int filenumber = 0;
    FILE* jpeg = NULL;
    
    // reads buffer from card
    while (fread(buffer, 1, BLOCK, card) != 0)
    {    
        // checks first four bytes of block to see if start of JPEG            
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] == 0xe1 || buffer[3] == 0xe0))
        {
            // if JPEG opened
            if (jpeg != NULL)
            {
                // closes unless error (fclose returns EOF)
                if (fclose(jpeg) == EOF)
                {
                    printf("Could not close %s! \n", filename);
                    return 2;
                }
            }
            
            // creates and JPEG in order
            sprintf(filename, "%03d.jpg", filenumber);
            filenumber++;
            
            // opens JPEG for writing
            jpeg = fopen(filename, "w");
            if (jpeg == NULL)
            {
                printf("Could not open %s! \n", filename);
                return 3;
            }
        }
        
        // writes buffer to JPEG
        if (jpeg != NULL)
            fwrite(buffer, 1, BLOCK, jpeg);
    }
    
    // close files
    fclose(card);
    fclose(jpeg);
    
    return 0;
}
