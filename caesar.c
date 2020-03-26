#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int InvalidKey(char str[]);
void caesar_encryptor(char str[], int k);


int main(int argc, string argv[])
{
    //check for correct number of command line arguments and whether it is a number. If either condition is 1, return 1.
    if((argc != 2) || InvalidKey(argv[1]))
    {
        printf("./caesar key\n");
        return 1;
    }

    //prompt user for plaintext and perform modulo on user input key
    string plaintext = get_string("Plaintext:");
    int key = atoi(argv[1]);
    int k = key % 26;

    caesar_encryptor(plaintext, k);

    return 0;
}

//Checks if the user's command line argument are all digits. If any 1 is not a digit, return 1.
int InvalidKey(char str[])
{
    for(int i = 0, n = strlen(str); i < n; i++)
    {
        if(!isdigit(str[i]))
        {
            return 1;
        }
    }
    return 0;
}

//prints ciphertext from plaintext
void caesar_encryptor(char str[], int k)
{
    int placeholder;
    printf("ciphertext:");

    for(int i = 0, n = strlen(str); i < n; i++)
    {
     //If the char is not an alphabet, just print it back out.
     if(isalpha(str[i]) == 0)
     {
         printf("%c", str[i]);
     }

     //If the char is a lowercase alphabet, add k to its ASCII value. If it exceeds 122('z'), minus 26 and print. Else, just print.
     else if(islower(str[i]))
     {
         placeholder = (int) (str[i]);
         placeholder += k;

         if(placeholder > 122)
         {
             placeholder -= 26;
         }
         printf("%c", placeholder);
    }

     //If the char is an uppercase alphabet, add k to its ASCII value. If it exceeds 90('Z'), minus 26 and print. Else, just print.
     else if(isupper(str[i]))
     {
         
         str[i] += k;

         if(str[i] > 90)
         {
             str[i] -= 26;
         }
         printf("%c", str[i]);
     }

    }

    printf("\n");
}