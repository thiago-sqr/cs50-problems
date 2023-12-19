/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#define NUM_ITEMS 8

typedef struct
{
    string item;
    float price;
} menu_item;

menu_item menu[NUM_ITEMS];

void add_items(void);
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

void add_items(void)
{
    menu[0].item = "Buguer";
    menu[0].price = 9.5;

    menu[1].item = "Vegan Burguer";
    menu[1].price = 11.0;

    menu[2].item = "Hot Dog";
    menu[2].price = 5.0;

    menu[3].item = "Cheese Dog";
    menu[3].price = 7.0;

    menu[4].item = "Fries";
    menu[4].price = 5.0;

    menu[5].item = "Chesse Fries";
    menu[5].price = 6.0;

    menu[6].item = "Water";
    menu[6].price = 2.0;

    menu[7].item = "Soda";
    menu[7].price = 2.0;
    return;
}

// Linear Search Implementation
float get_cost(string item)
{
    float cost = 0.0;
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (!strcasecmp(menu[i].item, item))
        {
            cost = menu[i].price;
            break;
        }
    }
    return cost;
}
