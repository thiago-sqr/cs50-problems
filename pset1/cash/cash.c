#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    int cents = get_cents();

    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    int coins = quarters + dimes + nickels + pennies;

    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents;
    do
    {
        cents = get_float("Change owed: ");
    }
    while (cents < 0.0);
    return cents;
}

int calculate_quarters(int cents)
{
    int c25 = 0;
    while (cents >= 25)
    {
        cents -= 25;
        c25++;
    }
    return c25;
}

int calculate_dimes(int cents)
{
    int c10 = 0;
    while (cents >= 10)
    {
        cents -= 10;
        c10++;
    }
    return c10;
}

int calculate_nickels(int cents)
{
    int c5 = 0;
    while (cents >= 5)
    {
        cents -= 5;
        c5++;
    }
    return c5;
}

int calculate_pennies(int cents)
{
    int c1 = 0;
    while (cents >= 1)
    {
        cents -= 1;
        c1++;
    }
    return c1;
}