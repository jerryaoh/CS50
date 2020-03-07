#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n, current_row;
    //Reject user inputs not between 1 to 8
    do{
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    for(current_row = 1; current_row <= n; current_row++) //print the spaces and # before the middle gap
    {
        for(int i = 0; i < n - current_row; i++)
       {  
            printf(" "); //print number of spaces = user input - current row number           
      }
    for(int j = 0; j < current_row; j++)
        {
            printf("#"); // print number of # = current row number
        }

    printf("  ");  // print the gap

    for(int k = 0; k < current_row; k++)
    {
        printf("#"); // print the wall after the gap
    }
    printf("\n"); // next line until the number of rows is hit
}
}
