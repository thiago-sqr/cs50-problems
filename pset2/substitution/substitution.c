#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int SIZE = 26;

bool only_alphabet(string s);
char substitute(char c, string key);

int main(int argc, string argv[])
{
    string ptxt, ctxt, key;

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != SIZE)
    {
        printf("Key must contain %i characters.\n", SIZE);
        return 1;
    }
    else if (!only_alphabet(argv[1]))
    {
        printf("Key must contain %i valid characters.\n", SIZE);
        return 1;
    }
    else
    {
        ptxt = get_string("plaintext: ");
        ctxt = ptxt;
    }

    for (int i = 0, n = strlen(ptxt); i < n; i++)
    {
        ctxt[i] = substitute(ptxt[i], argv[1]);
    }

    printf("ciphertext: %s\n", ctxt);
    return 0;
}

bool only_alphabet(string key)
{
    int alphabet[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        if (isupper(key[i]))
        {
            alphabet[key[i] - 'A']++;
        }
        else if (islower(key[i]))
        {
            alphabet[key[i] - 'a']++;
        }
        else
        {
            return false;
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        if (alphabet[i] == 0)
        {
            return false;
        }
    }
    return true;
}

char substitute(char c, string key)
{
    char newchar;
    if (isupper(c))
    {
        newchar = toupper(key[c - 'A']);
    }
    else if (islower(c))
    {
        newchar = tolower(key[c - 'a']);
    }
    else
    {
        newchar = c;
    }
    return newchar;
}
