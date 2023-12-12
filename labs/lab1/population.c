#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int initial, final, years = 0, population;

    do
    {
        initial = get_int("Start size: ");
    }
    while (initial < 9);

    do
    {
        final = get_int("End size: ");
    }
    while (final <= initial);

    population = initial;

    while (population < final)
    {
        population += (population / 3) - (population / 4);
        years++;
    }

    printf("Years: %i\n", years);
}