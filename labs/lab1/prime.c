#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    if (number != 2 && number % 2 == 0)
    {
        return false;
    }
    int ctrl = 0;
    for (int i = 1; i < (number / 2); i++)
    {
        if (number % i == 0)
        {
            ctrl++;
        }
        if (ctrl > 1)
        {
            return false;
        }
    }
    return true;
}