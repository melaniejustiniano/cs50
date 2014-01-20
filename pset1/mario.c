/*
 * Problem Set 1 - mario.c
 * Melanie Justiniano <melaniejustiniano@college.harvard.edu>
 *
 * Builds a pyramid alligned on the right-side of the screen.
 *
 */
 
#include <stdio.h>
#include <cs50.h>
 
int main(void)
{
    // loop until user provides appropriate height
    int height = 0;
    
    do
    {
        printf("Height: ");
        height = GetInt();
        
        
        // prompt for appropriate height if invalid
        if (height > 23 || height <= 0)
        {
            printf("Please enter a number between 1 and 23. \n");
        }
    }
    while (height > 23 || height <= 0);
    
    // create pyramid
    for (int row = 0; row < height; row++)
    {    
        // print spaces
        for (int space = height - row; space > 1; space--)
        {
            printf(" ");
        }
        
        // print hashes
        for (int hash = 0; hash < row + 2; hash ++)
        {
            printf("#");
        }
        
        // print new line
        printf("\n");
    }
    return 0;  
}
