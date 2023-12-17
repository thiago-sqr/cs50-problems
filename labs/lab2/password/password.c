#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int upper = 0, lower = 0, number = 0, symbol = 0;
    for (int i = 0, n = strlen(password); i < n; i++)
    {
        if (islower(password[i]))
        {
            lower++;
        }
        else if (isupper(password[i]))
        {
            upper++;
        }
        else if (isdigit(password[i]))
        {
            number++;
        }
        else if (ispunct(password[i]))
        {
            symbol++;
        }
    }

    if (upper > 0 && lower > 0 && number > 0 && symbol > 0)
    {
        return true;
    }
    return false;
}
