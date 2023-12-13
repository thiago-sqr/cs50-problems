#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS = 8;

void print_bulb(int bit);

int main(void)
{
    string message = get_string("Message: ");

    int binary[strlen(message) * BITS];

    for (int i = 0, n = strlen(message); i < n; i++)
    {
        int ascii = message[i];
        for (int j = 1; j <= BITS; j++)
        {
            if (ascii % 2 == 0)
            {
                binary[(BITS * (i + 1)) - j] = 0;
            }
            else
            {
                binary[(BITS * (i + 1)) - j] = 1;
            }
            ascii /= 2;
        }
    }

    for (int i = 0, n = BITS * strlen(message); i < n; i++)
    {
        print_bulb(binary[i]);
        if ((i + 1) % BITS == 0)
        {
            printf("\n");
        }
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}