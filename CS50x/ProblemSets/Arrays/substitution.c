// Implement substitution encryption
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

// Constants
#define VALID 2
#define LETTER 26

// Structure array for check key
typedef struct ksearch
{
    int use;
    char letter;
} ksearch;
ksearch sea[LETTER];

// Prototype
bool search_and_insert(char letter);
bool check_key(string key);
void substitution(string plaintext, string key);

// Main function
int main(int argc, string argv[])
{
    // Check for the command-line arguments
    if (argc != VALID)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (!check_key(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        // Get the plaintext
        string plaintext = get_string("plaintext: ");

        // encrypt and output the result
        printf("ciphertext: ");
        substitution(plaintext, argv[1]);
    }
}

// search the single letter
bool search_and_insert(char letter)
{
    int left = 0, right = LETTER - 1;
    int mid;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (sea[mid].letter > letter)
            right = mid - 1;
        else if (sea[mid].letter < letter)
            left = mid + 1;
        else if (sea[mid].use == 1)
            return false;
        else
        {
            sea[mid].use = 1;
            return true;
        }
    }
    return true;
}

// Check the key for number of letters, unique
bool check_key(string key)
{
    // initialize the sea array
    char sign = 'A';
    for (int i = 0; i < LETTER; i++, sign++)
    {
        sea[i].use = 0;
        sea[i].letter = sign;
    }

    // check the key letter by letter
    int length = 0;
    while (key[length] != '\0')
    {
        if (!isalpha(key[length]) || !search_and_insert(toupper(key[length])))
            return false;
        length++;
    }
    if (length != LETTER)
        return false;
    return true;
}

// Substitution encryption
void substitution(string plaintext, string key)
{
    int i = 0;
    while (plaintext[i] != '\0')
    {
        if (!isalpha(plaintext[i]))
            printf("%c", plaintext[i]);
        else
        {
            int pos = toupper(plaintext[i]) - 'A';
            if (isupper(plaintext[i]))
                printf("%c", toupper(key[pos]));
            else
                printf("%c", tolower(key[pos]));
        }
        i++;
    }
    printf("\n");
}
