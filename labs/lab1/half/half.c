#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float bill, tax;
    int tip;

    do
    {
        bill = get_float("Bill before tax and tip: ");
        tax = get_float("Sale tax percent: ");
        tip = get_int("Tip percent: ");
    }
    while (bill <= 0 || tax < 0 || tip < 0);

    float half = ((bill * (1 + tax / 100.0)) * (1 + (float) tip / 100.0)) / 2.0;
    printf("You will owe $%.2f each!\n", half);
}