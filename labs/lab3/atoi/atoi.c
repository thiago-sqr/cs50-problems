#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    printf("%i\n", convert(input));
}

// Recursive Atoi Implementation
int convert(string input)
{
    if (input[0] == '\0')
    {
        return 0;
    }

    int n = strlen(input);
    int last_digit = input[n - 1] - '0';
    input[n - 1] = '\0';

    return last_digit + 10 * convert(input);
}
