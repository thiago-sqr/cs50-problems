#include <cs50.h>
#include <math.h>
#include <stdio.h>

int Luhn_algorithm_valid(long number);
int find_digit(long number, int i);
int get_size(long number);
int american_express_valid(long number);
int mastercard_valid(long number);
int visa_valid(long number);

int main(void)
{
    long number;
    do
    {
        number = get_long("Enter your credit card number: ");
    }
    while (number < 0);

    if (Luhn_algorithm_valid(number))
    {
        if (american_express_valid(number))
        {
            printf("AMEX\n");
        }
        else if (mastercard_valid(number))
        {
            printf("MASTERCARD\n");
        }
        else if (visa_valid(number))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int american_express_valid(long number)
{
    int size = get_size(number);
    int first_digit = find_digit(number, size);
    int second_digit = find_digit(number, size - 1);
    return (size == 15 && first_digit == 3 && (second_digit == 4 || second_digit == 7));
}

int mastercard_valid(long number)
{
    int size = get_size(number);
    int first_digit = find_digit(number, size);
    int second_digit = find_digit(number, size - 1);
    return (size == 16 && first_digit == 5 &&
            (second_digit == 1 || second_digit == 2 || second_digit == 3 || second_digit == 4 || second_digit == 5));
}

int visa_valid(long number)
{
    int size = get_size(number);
    int first_digit = find_digit(number, size);
    int second_digit = find_digit(number, size - 1);
    return ((size == 13 || size == 16) && first_digit == 4);
}

int Luhn_algorithm_valid(long number)
{
    int sum = 0;
    for (int i = 1; i <= get_size(number); i++)
    {
        if (i % 2 == 0)
        {
            int digit = find_digit(number, i) * 2;
            for (int j = 1; j <= get_size(digit); j++)
            {
                sum += find_digit(digit, j);
            }
        }
        else
        {
            int digit = find_digit(number, i);
            sum += digit;
        }
    }
    return sum % 10 == 0;
}

int find_digit(long number, int i)
{
    if (i > get_size(number))
    {
        return 0;
    }
    if (i == 1)
    {
        return number % 10;
    }
    return ((number % (long long) pow(10, i))) / (long long) pow(10, i - 1);
}

int get_size(long number)
{
    if (number == 0)
    {
        return 1;
    }
    int size = 0;
    while (number != 0)
    {
        number /= 10;
        size++;
    }
    return size;
}