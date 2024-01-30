// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 702;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int i = hash(word);

    for (node *n = table[i]; n != NULL; n = n->next)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (word[1] == '\0')
    {
        return (tolower(word[0]) - 'a') * 27;
    }
    else
    {
        return (tolower(word[0]) - 'a') * 27 + (tolower(word[1]) - 'a' + 1);
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char buffer[LENGTH + 1];
    while (fscanf(source, "%s", buffer) != EOF)
    {
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            fclose(source);
            return false;
        }

        strcpy(new->word, buffer);
        int i = hash(buffer);

        new->next = table[i];
        table[i] = new;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    for (int i = 0; i < N; i++)
    {
        for (node *temp = table[i]; temp != NULL; temp = temp->next)
        {
            count++;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *temp = table[i];

        while (cursor != NULL)
        {
            cursor = temp->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}
