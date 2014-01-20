/*
 * Problem Set 1 - greedy.c
 * Melanie Justiniano <melaniejustiniano@college.harvard.edu>
 *
 * Calculates minimum number of coins for change.
 *
 */
 
#include <stdio.h>
#include <cs50.h>
#include <math.h>
 
int main(void)
{
    // loop until user provides an appropriate amount
    float input = 0;
    
    do
    {
        printf("How much change do you need? ");
        input = GetFloat();
        
        // prompt for appropriate value if invalid
        if (input < 0)
        {
            printf("Please enter a positive value. \n");
        }
    }
    while (input < 0);
    
    // change input into integral value
    int change = round(input*100);
    
    // define and set count to zero
    int count = 0;
    
    // determine quarters
    int quarter = 0;
    
    while (change >= 25)
    {
        // increase count
        count++;
        quarter++;
        
        // subtract a quarter from change needed
        change = change - 25;
    }
    
    // determine dimes
    int dime = 0;
    
    while (change >= 10)
    {
        // increase count
        count++;
        dime++;
        
        // subtract a dime from change needed
        change = change - 10;
    }
    
    // determine nickels
    int nickel = 0;
    
    while (change >= 5)
    {
        // increase count
        count++;
        nickel++;
        
        // subtract a nickel from change needed
        change = change - 5;
    }
    
    // determine pennies
    int penny = change;
    count = count + penny;
    
    // print minimum number of coins
    printf("The minimum number of coins is %d. \n", count);

    /*
     * Sorry about the extraneous fluff. I was being
     * particular about grammar so all the rest of this
     * is just me needing things to look pretty, and
     * I thought it would look all nice like this. :)
     *
     */

    // list how many quarters you would need
    if (quarter == 1)
        printf("You would need %d quarter. \n", quarter);
    else if (quarter > 1)
        printf("You would need %d quarters. \n", quarter);
    
    // list how many dimes you would need
    if (dime == 1)
        printf("You would need %d dime. \n", dime);
    else if (dime > 1)
        printf("You would need %d dimes. \n", dime);

    // list how many nickels you would need    
    if (nickel == 1)
        printf("You would need %d nickel. \n", nickel);
    else if (nickel > 1)
        printf("You would need %d nickels. \n", nickel);
   
    // list how many pennies you would need 
    if (penny == 1)
        printf("You would need %d penny. \n", penny);
    else if (penny > 1 )
        printf("You would need %d pennies. \n", penny);
    
    // as per the problem set instructions
    printf("\n%d \n", count);
     
    return 0;
}
