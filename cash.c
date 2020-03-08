#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
    /* Variable list:
    dollars as user input, coins as input in coins, 
    counter as summation of coins needed, rem as the temporary remainder to be carried
    through the equations
    */
    float dollars;
    int coins, counter = 0, rem;
    
    //prompt user for non-negative input if user fails to provide the correct amount
    do  
        {
            dollars = get_float("Change owed: ");
        }
    while(dollars <= 0);

    //convert input into cents and round
    coins = round(dollars * 100);
    
    //Calculating the number of quarters needed
    counter += coins/25;
    rem = coins % 25;

    //Add on the number of dimes needed
    counter += rem / 10;
    rem %= 10;

    //Add on the number of quarters needed
    counter += rem / 5;
    rem %= 5;

    //Add on the number of pennies needed
    counter += rem;

    //Print the result

    printf("%d\n", counter);
}
