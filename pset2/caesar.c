/*
 * Problem Set 2 - caesar.c
 * Melanie Justiniano <melaniejustiniano@college.harvard.edu>
 *
 * Ciphers text based on user's numerical input.
 *
 */
 

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // disallows more than one command line input
    if (argc != 2)
    {
        printf("You must have exactly one key! \n");
        return 1;
    }
    
    // disallows non-integer command line input
    string input = argv[1];
    int length = strlen(input);  
      
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Your key must be an non-negative integer! \n");
            return 1;
        }
    }
 
    // disallows empty string
    if (length == 0)
    {
        printf("That's actually just really mean! \n");
        return 1;
    } 
 
    // makes second command line argument the key
    int key = atoi(input);
     
    // disallows negative keys
    if (key < 0)
    {
        printf("Your key must be an non-negative integer! \n");
        return 1;
    }
        
    // allows any positive key
    if (key > 25)
    {
        key = key % 26;
    }
        
    printf("Key = %d \n", key);
       
    // prompts user for plaintext
    printf("Insert your text here: ");
    string text = GetString();
    
    // printed outside of loop so not repeated
    printf("Your ciphered text is: ");
    
    // cipher plaintext
    length = strlen(text);
    
    for (int i = 0; i < length; i++)
    {
        // ciphers only alphabetic input
        if (isalpha(text[i]))
        {
            int character = text[i];
            int lettercase = 0;
            
            // keeps lowercase characters lowercase
            if (islower(text[i]))
            {
                lettercase = 'a';
            }
            
            // keeps uppercase characters uppercase
            if (isupper(text[i]))
            {
                lettercase = 'A';
            }
            
            // actually ciphers the text    
            int result = (character - lettercase + key) % 26;
            result += lettercase;
            printf("%c", result);
        }
        
        // preserves nonalphabetic input
        else
        {
            printf("%c", text[i]);
        }
    }
    
    // prints new line after ciphering
    printf("\n");
        
    return 0;
}
