// Declares a dictionary's functionality

// 避免重复编译
#ifndef DICTIONARY_H
#define DICTIONARY_H

// 包含bool定义
#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define LETTER 26

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
