// Print pyramids with hashes and spaces
#include <cs50.h>
#include <stdio.h>

// The pyramids consist of three parts: left gap right
int get_height(int low, int high);
void print_left(int height, int row);
void print_gap(int count);
void print_right(int row);
void print_pyramids(int height, int cur_gap);

// main function
int main(void)
{
    int low_case = 1;
    int high_case = 8;
    int height = get_height(low_case, high_case);
    int cur_gap = 2;
    print_pyramids(height, cur_gap);
}

// Get an int that is between the low and high
int get_height(int low, int high)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < low || height > high); // do-while loop should put the while below
    return height;
}

// Print the left half of a specific row of the pyramids
void print_left(int height, int row)
{
    for (int i = 0; i < height - row - 1; i++)
        printf(" ");
    for (int i = 0; i < row + 1; i++)
        printf("#");
}

// Print spaces between pyramids
void print_gap(int count)
{
    for (int i = 0; i < count; i++)
        printf(" ");
}

// Print the right half of a specific row of the pyramids
void print_right(int row)
{
    for (int i = 0; i < row + 1; i++)
        printf("#");
}

// Print the whole pyramids
void print_pyramids(int height, int cur_gap)
{
    for (int i = 0; i < height; i++)
    {
        print_left(height, i);
        print_gap(cur_gap);
        print_right(i);
        printf("\n");
    }
}
