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

    printf("Grade = %f\n", grade);
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
        if((isalpha(array[i])) && (isalpha(array[i+1]) == 0))
        {
            if((array[i+1] != 45) && (array[i+1] != 39))
            {
                no_of_words++;
            }
        }
    }
    printf("%i word(s)\n", no_of_words);
    return no_of_words;
}

float letters(char array[], int words)
{
    int no_of_letters = 0;
    float L;

    for(int i = 0, n = strlen(array); i < n; i++)
    {
        if(isalpha(array[i]))
        {
            no_of_letters++;
        }
    }
    printf("%i letters(s)\n", no_of_letters);
    L = 100 * ((float) no_of_letters / (float) words);

    printf("%f letter(s) per 100 words\n", L);

    return L;
}

float sentences(char array[], int words)
{
    int no_of_sentences = 0;
    float S;

    for(int i = 0, n = strlen(array); i < n; i++)
    {
        if((array[i] == 33) || (array[i] == 46) || (array[i] == 63))
        {
            no_of_sentences++;
        }
         else
        {
            no_of_sentences += 0;
        }
    }
    printf("%i sentence(s)\n", no_of_sentences);
    S = 100 * ((float) no_of_sentences / (float) words);

    printf("%f sentence(s) per 100 words\n", S);
    return S;
}