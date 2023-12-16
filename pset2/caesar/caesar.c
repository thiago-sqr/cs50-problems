#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string arg);
char rotate(char c, int key);

int main(int argc, string argv[])
{
    string ptxt, ctxt;
    int key;

    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        key = atoi(argv[1]);
        ptxt = get_string("plaintext:  ");
        ctxt = ptxt;
    }

    for (int i = 0, n = strlen(ptxt); i < n; i++)
    {
        ctxt[i] = rotate(ptxt[i], key);
    }
    printf("ciphertext: %s\n", ctxt);
    return 0;
}

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int key)
{
    char newchar;
    if (c >= 'a' && c <= 'z')
    {
        c -= ('a');
        newchar = (c + key) % 26;
        newchar += 'a';
    }
    else if (c >= 'A' && c <= 'Z')
    {
        c -= ('A');
        newchar = (c + key) % 26;
        newchar += 'A';
    }
    else
    {
        newchar = c;
    }
    return newchar;
}
