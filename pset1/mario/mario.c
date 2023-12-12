#include <cs50.h>
#include <stdio.h>

void printSpaces(int number);
void printHashes(int number);

int main(void)
{
    int n;
    do
    {
        n = get_int("Enter a number: ");
    }
    while (n > 8 || n < 1);

    for (int i = 1; i <= n; i++)
    {
        printSpaces(n - i);
        printHashes(i);
        printf("\n");
    }
}

void printSpaces(int number)
{
    for (int i = number; i > 0; i--)
    {
        printf(" ");
    }
}

void printHashes(int number)
{
    for (int i = 1; i <= number; i++)
    {
        printf("#");
    }
}