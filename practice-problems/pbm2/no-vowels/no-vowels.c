#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    printf("%s\n", replace(argv[1]));
    return 0;
}

string replace(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        switch (s[i])
        {
            case 'a' : case 'A':
                s[i] = '6';
                break;

            case 'e':
            case 'E':
                s[i] = '3';
                break;

            case 'i':
            case 'I':
                s[i] = '1';
                break;

            case 'o':
            case 'O':
                s[i] = '0';
                break;

            default:
                break;
        }
    }
    return s;
}