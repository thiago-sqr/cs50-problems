#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dolars;

    do
    {
        dolars = get_float("Change owed: $");
    }
    while (dolars < 0.0);

    int cents = round(dolars * 100);

    int c25 = 0, c10 = 0, c5 = 0, c1 = 0;

    while (cents >= 25)
    {
        cents -= 25;
        c25++;
    }
    while (cents >= 10)
    {
        cents -= 10;
        c10++;
    }
    while (cents >= 5)
    {
        cents -= 5;
        c5++;
    }
    while (cents >= 1)
    {
        cents -= 1;
        c1++;
    }
    printf("Quarters: %i\n", c25);
    printf("Dimes: %i\n", c10);
    printf("Nickles: %i\n", c5);
    printf("Pennies: %i\n", c1);
}