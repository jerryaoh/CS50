#include <stdio.h>
#include <cs50.h>
#include <math.h>

void card_type(long n); //this function returns the card type by taking the card number as input

int main (void){

    long card_number;

    //Store card number from user input
    do{ 
    card_number = get_long("Number: ");
    }
    while(card_number <= 0);

    /*temp_odd_digits is just the card number to be used to help find the 
    sum of the odd digits place (counting from the back),which are those in the 1st, 
    3rd, 5th digit and so on from the back*/
    long temp_odd_digits = card_number, temp_even_digits = card_number / 10;

    int sum_odd_digits = card_number % 10, sum_even_digits = 0, i;
    //sum_odd_digits is the sum of all the numbers in the odd digits place
    //sum_even_digits is the sum of all the numbers in the even digits place

    // evaluate sum_even_digits
    while(temp_even_digits != 0)
    {
        if(temp_even_digits % 10 < 5)
        {
            sum_even_digits += (temp_even_digits % 10) * 2;
        }
        else
        {
            i = (temp_even_digits % 10) * 2;
            sum_even_digits += (i % 10) + (i / 10);
        }
        temp_even_digits /= 100;
    }
    
    // evaluate sum_odd_digits
    while((temp_odd_digits / 100) > 0)
    {
        temp_odd_digits /= 100;
        sum_odd_digits += temp_odd_digits % 10;
    }
    //sum_odd_digits + sum_even_digits. Check if last digit is 0. If not, pass a 0 to next function.
    if((sum_odd_digits + sum_even_digits) % 10 != 0)
    {
        card_number = 0;
    }
    
    //print card type if valid
    card_type(card_number);
    
}

void card_type(long n){
    
    //The first part of the function aims to determine the number of digits and the first number
    int no_of_digits = 0, first_digit, first_2_digits;
    long temp;

    temp = n;

    while (temp > 0)
    {
        temp /= 10;
        no_of_digits++;
    }

    first_digit = (n / (pow(10, (no_of_digits - 1))));
    first_2_digits = (n / (pow(10, (no_of_digits - 2))));
    /*The second part of the function is a series of conditional statements that prints
    the card type based on the number of digits and first_digit unique to the card type*/

    if((no_of_digits == 13 && first_digit == 4) || (no_of_digits == 16 && first_digit == 4))
    {
        printf("VISA\n");
    }
    else if(no_of_digits == 15 && (first_2_digits == 34 || first_2_digits == 37))
    {
        printf("AMEX\n");
    }
    else if(no_of_digits == 16 && (first_2_digits == 51 || first_2_digits == 52|| first_2_digits == 53||            first_2_digits == 54|| first_2_digits == 55))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

}
