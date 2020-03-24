#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int words(char array[]); //counts number of words in sentence input
float letters(char array[], int words); //counts number of letters per 100 words
float sentences(char array[], int words); //counts number of sentences per 100 words

int main (void)
{
    int N; //N = Number of words in string
    float L, S, grade; //L = Letters per 100 words in string, S = Sentences per 100 words in string, grade = output according to formula

    string text = get_string("Text: "); //Read Input from user

    N = words(text);
    L = letters(text, N);
    S = sentences(text, N);

    grade = (0.0588 * L) - (0.296 * S) - 15.8;


    if(grade < 1)  //Prints Grade based on the requirements
    {
        printf("Before Grade 1\n");
    }
    else if(grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(grade));
    }
}

int words(char array[])
{
    int no_of_words = 0;

    for(int i = 0, n = strlen(array); i < n ; i++)
    {
        if((isalpha(array[i])) && (isalpha(array[i+1]) == 0))  //If the current char is an alphabet and if next char is not an alphabet
        {
            if((array[i+1] != 45) && (array[i+1] != 39))       // If the next char is not a ' or -
            {
                no_of_words++;                                 //Add to no_of_words
            }
        }
    }

    return no_of_words;
}

float letters(char array[], int words)
{
    int no_of_letters = 0;
    float L;

    for(int i = 0, n = strlen(array); i < n; i++)
    {
        if(isalpha(array[i])) //if the current char is an alphabet, add to no_of_letters
        {
            no_of_letters++;
        }
    }


    L = 100 * ((float) no_of_letters / (float) words); //compute the value of L as a float and passes back to main function

    return L;
}

float sentences(char array[], int words)
{
    int no_of_sentences = 0;
    float S;

    for(int i = 0, n = strlen(array); i < n; i++)
    {
        if((array[i] == 33) || (array[i] == 46) || (array[i] == 63)) //if the current char is a . or ? or !, add to number of no_of_sentences
        {
            no_of_sentences++;
        }
         else
        {
            no_of_sentences += 0;
        }
    }

    S = 100 * ((float) no_of_sentences / (float) words); //compute the value of S as a float and passes back to main function

    return S;
}