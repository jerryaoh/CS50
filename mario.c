#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n, current_row;
do{
    n = get_int("Height: ");
}
while(n < 1 || n > 8);

for(current_row = 1; current_row <= n; current_row++)
    {
    for(int i = 0; i < n - current_row; i++)
        {
        printf(" ");
        }
    for(int j = 0; j < current_row; j++)
        {
        printf("#");
        }
    printf("\n");
    }
}
