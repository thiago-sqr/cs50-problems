// Become familiar wih C syntax
// Learn to debug buggy code
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is your name? ");
    string location = get_string("Where do you live? ");
    printf("Hello, %s, from %s!\n", name, location);
}

/* ORIGINAL CODE

#include <cs50.h>

int main(void)
{
    // Ask for your name and where live
    name = get_string("What is your name? ")
    location = get_string("Where do you live? ")

    // Say hello
    print("Hello, %i, from %i!", name, location)
}
*/