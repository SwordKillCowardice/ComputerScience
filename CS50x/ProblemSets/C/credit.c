// Check if the card number is valid
#include <cs50.h>
#include <stdio.h>

// Length and the first two digits of each type of card
#define AMEX 15
#define MASTERCARD 16
#define VISA 13
#define AMEX_START1 34
#define AMEX_START2 37
#define MASTERCARD_LOW 51
#define MASTERCARD_HIGH 55
#define VISA_START 4

string check(long number);

// main function
int main(void)
{
    long card_number = get_long("Number: ");
    string result = check(card_number);
    printf("%s\n", result);
}

// Using Luhn’s Algorithm, also checking for length and the first two digits
string check(long number)
{
    int first_two_digits;
    int length = 0;
    int checksum = 0;

    // Get the checksum, the length and the first_two_digits
    while (number)
    {
        int last_digit = number % 10;
        if (length % 2 == 0)
            checksum += last_digit;
        else
        {
            int cur = last_digit * 2;
            if (cur >= 10)
                checksum += cur % 10 + cur / 10;
            else
                checksum += cur;
        }
        number /= 10;
        length++;
        if (number >= 10 && number <= 99)
            first_two_digits = number;
    }

    // Check
    if (checksum % 10 != 0)
        return "INVALID";
    else if (length == AMEX && (first_two_digits == AMEX_START1 || first_two_digits == AMEX_START2))
        return "AMEX";
    else if (length == MASTERCARD && first_two_digits >= MASTERCARD_LOW &&
             first_two_digits <= MASTERCARD_HIGH)
        return "MASTERCARD";
    else if ((length == VISA || length == MASTERCARD) && first_two_digits / 10 == VISA_START)
        return "VISA";
    else
        return "INVALID";
}
