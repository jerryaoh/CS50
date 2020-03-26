#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int InvalidKey(string str);
void Uppercase(string str);

int main (int argc, string argv[])
{
    char key[26];

    // Check if there is only 1 command line argument. If it is not 1, end the program.
    if (argc != 2 )
    {
        printf("./substitution key\n");
        return 1;
    }

    // Convert key to uppercase
    Uppercase(argv[1]);


    // Check if the command line argument contains 26 characters. If it's not, return the error message and end program.
    if (InvalidKey(argv[1]))
    {
        printf("Key must contain 26 non-repeating characters.\n");
        return 1;
    }

    // Copy argv[1] into a new string called 'key'
    strcpy(key, argv[1]);

    // Prompts the user for plaintext
    string s = get_string("plaintext: ");

    printf("ciphertext: ");

    //go through each char of the plaintext string, modify and print depending on char type accordingly
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //if it's not alphabetical, print itself out
        if (isalpha(s[i]) == 0)
        {
            printf("%c", s[i]);
        }

        //if it's lowercase, find its position in the 'key' string and convert back to lowercase as key is all in uppercase
        else if (islower(s[i]))
        {
            s[i] = tolower(key[s[i] - 97]);
            printf("%c", s[i]);
        }

        //if it's uppercase, find its position in the 'key string' and print
        else if (isupper(s[i]))
        {
            s[i] = key[s[i] - 65];
            printf("%c", s[i]);
        }
    }

    printf("\n");

    return 0;
}


// Function that returns 1 for an invalid key provided
int InvalidKey(string str)
{
    if (strlen(str) != 26)
    {
        return 1;
    }

    for (int i = 0, n = strlen(str); i < n; i++)
    {

        // Rejects non-alphabetical characters
        if (isalpha(str[i]) == 0)
        {
            return 1;
        }

        // Check current char against all the previous chars in the key
        for (int j = 0; j < i; j++)
        {
            if(str[j] == str[i])
            {
                return 1;
            }
        }
    }

    return 0;
}

// Function that converts all the letters in the key to uppercase letters and pass back to the main function
void Uppercase(string str)
{
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (islower(str[i]))
        {
            str[i] = toupper(str[i]);
        }
    }
}