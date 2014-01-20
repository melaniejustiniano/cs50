/*
 * Problem Set 2 - caesar.c
 * Melanie Justiniano <melaniejustiniano@college.harvard.edu>
 *
 * Ciphers text based on user's alphabetical input.
 *
 */
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // disallows more than one word in command line input
    if (argc != 2)
    {
        printf("Your key must be only one word! \n");
        return 1;
    }

    // disallows non-alphabetical command line input
    string key = argv[1];
    int keylength = strlen(key);
     
    for (int i = 0; i < keylength; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("You key must only be letters! \n");
            return 1;
        }
    }

    // disallows empty string
    if (keylength == 0)
    {
        printf("That's actually just really mean! \n");
        return 1;
    }
           
    // prompts user for plaintext
    printf("Insert your text here: ");
    string text = GetString();
    
    // outside the loop so as to not be repeated
    printf("Your ciphered text is: ");

    // ciphers text using key    
    int j = 0;
    int textlength = strlen(text);
    
    for (int i = 0; i < textlength; i++)
    {
        // loops the key
        j = j % keylength;
        int keyletter = key[j];
        
        // key will shift standardly regardless of case
        if (isupper(key[j]))
        {
            keyletter = key[j] - 'A';
        }
            
        if (islower(key[j]))
        {
            keyletter = key[j] - 'a';
        }
        
        // preserves text case while ciphering  
        if (isalpha(text[i]))
        {
            int lettercase = 0;
            
            // preserves uppercase        
            if (isupper(text[i]))
            {
                lettercase = 'A';
            }
            
            // preserves lowercase
            if (islower(text[i]))
            {
                lettercase = 'a';
            }
            
            // ciphers text    
            int textletter = text[i] - lettercase;
            int cipherletter = (textletter + keyletter) % 26;
            cipherletter += lettercase;
            printf("%c", (char) cipherletter);
            
            // shifts key letter for alphabetical input
            j++;
        }
        
        // preserves non-alphabetical text   
        else
        {
            printf("%c", text[i]);
        }
    }
    
    printf("\n");
    
    return 0;
}
