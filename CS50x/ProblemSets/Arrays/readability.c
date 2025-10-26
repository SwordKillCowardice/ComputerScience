// Output the possible readability of the reader for the given text
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

// Constants
#define LOW 1
#define HIGH 16
#define FACTOR1 100
#define FACTOR2 0.0588
#define FACTOR3 0.296
#define FACTOR4 15.8

// Prototype
int cal_readability(string text);

// Main function
int main(void)
{
    // Get the text
    string text = get_string("Text: ");

    // Calculate the readability and output it
    int readability = cal_readability(text);
    if (readability < LOW)
        printf("Before Grade 1\n");
    else if (readability >= HIGH)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", readability);

    return 0;
}

// Calculate the readability based on Coleman-Liau index
int cal_readability(string text)
{
    int total_letters = 0, total_sentences = 0, total_words = 1;
    int n = 0;
    while (text[n] != '\0')
    {
        if (isalpha(text[n]))
            total_letters++;
        else if (isspace(text[n]))
            total_words++;
        else if (text[n] == '.' || text[n] == '!' || text[n] == '?')
            total_sentences++;
        n++;
    }
    double L = FACTOR1 * total_letters / (float) total_words;
    double S = FACTOR1 * total_sentences / (float) total_words;
    int result = round(FACTOR2 * L - FACTOR3 * S - FACTOR4);
    return result;
}
