// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 18278;

// Hash table
node *table[N] = {NULL};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert the word to lowercase
    char tmp[LENGTH + 1];
    int i = 0;
    while (word[i] != '\0')
    {
        if (isalpha(word[i]))
            tmp[i] = tolower(word[i]);
        else
            tmp[i] = word[i];
        i++;
    }
    tmp[i] = '\0';

    // Check
    int index = hash(tmp);
    for (node* ptr = table[index]; ptr != NULL; ptr = ptr->next)
    {
        if (strcmp(ptr->word, tmp) == 0)
            return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Use length and the first three characters
    int length = strlen(word);

    // 修复bug2: 确保正确使用字符进行映射, 而不是'
    if (length == 1 || (length == 2 && !isalpha(word[1])))
        return tolower(word[0]) - 'a';
    else if (length == 2)
        return LETTER + LETTER * (tolower(word[0]) - 'a') + tolower(word[1]) - 'a';
    else
    {
        int res = LETTER + LETTER * LETTER + LETTER * LETTER * (tolower(word[0]) - 'a');
        for (int start = 1, times = 0; word[start] != '\0'; start++)
        {
            if (!isalpha(word[start]))
                continue;
            else if (times == 0)
            {
                res += LETTER * (tolower(word[start]) - 'a');
                times++;
            }
            else
            {
                res += tolower(word[start]) - 'a';
                return res;
            }
        }
        return res;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE* dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Cann't open the dictionary\n");
        return false;
    }

    // Read the file and build the hash table
    char word[LENGTH + 1];

    // 修复bug1: fscanf函数仅在未到达文件末尾且读取失败时才返回0
    // 读取成功和读取到文件末尾都返回非0
    while (fscanf(dic, "%s", word) == 1)
    {
        node* new = malloc(sizeof(node));
        if (new == NULL)
        {
            printf("Allocated Failure\n");
            unload();
            fclose(dic);
            return false;
        }

        else // Insert the new word directly at the very beginning
        {
            int index = hash(word);
            new->next = table[index];
            table[index] = new;
            strcpy(new->word, word);
        }
    }

    // Close the file
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Traverse the hash table
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (!table[i])
            continue;
        else
        {
            for (node* tmp = table[i]; tmp != NULL; tmp = tmp->next)
                count++;
        }
    }
    return count;
}

// Help to free the memory
void help_free(node* p)
{
    if (p == NULL)
        return;
    help_free(p->next);
    free(p);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
        help_free(table[i]);
    return true;
}
