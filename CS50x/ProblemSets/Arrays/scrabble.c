// Implement a simple Scrabble game
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

// Constants
#define LETTER 26

// A structure that stores character and score correspondences
typedef struct cscore
{
    char letter;
    int score;
} cscore;

// A global array for record
cscore scores[LETTER] = {{'A', 1}, {'B', 3}, {'C', 3},  {'D', 2}, {'E', 1}, {'F', 4}, {'G', 2},
                         {'H', 4}, {'I', 1}, {'J', 8},  {'K', 5}, {'L', 1}, {'M', 3}, {'N', 1},
                         {'O', 1}, {'P', 3}, {'Q', 10}, {'R', 1}, {'S', 1}, {'T', 1}, {'U', 1},
                         {'V', 4}, {'W', 4}, {'X', 8},  {'Y', 4}, {'Z', 10}};

// Prototypes
int cal_single(char sign);
int cal_total(string word);

// Main function
int main(void)
{
    // Get players' inputs
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Calculate theirs scores
    int score1 = cal_total(word1);
    int score2 = cal_total(word2);

    // Compare their scores and output the result
    if (score1 > score2)
        printf("Player 1 wins!\n");
    else if (score1 < score2)
        printf("Player 2 wins!\n");
    else
        printf("Tie!\n");

    return 0;
}

// Calculate the score for a single char
int cal_single(char sign)
{
    if (!isalpha(sign))
        return 0;
    else
    {
        char letter = toupper(sign);
        for (int i = 0; i < LETTER; i++)
        {
            if (letter == scores[i].letter)
                return scores[i].score;
        }
        return 0;
    }
}

// Calculate the total scores for a word
int cal_total(string word)
{
    int n = 0, score = 0;
    while (word[n] != '\0')
    {
        score += cal_single(word[n]);
        n++;
    }
    return score;
}
