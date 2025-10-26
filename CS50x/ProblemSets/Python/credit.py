# Check if the credit card is valid
from cs50 import get_int
import re


# Constants
AMEX_LEN, MASTERCARD_LEN, VISA_LEN = 15, 16, 13
AMEX_START = "34|37"
MASTERCARD_START = "5[1-5]"
VISA_START = "4"


# Main function
def main():
    card = get_int("Number: ")
    check = check_sum(card)
    if check:
        check_pattern(str(card))
    else:
        print('INVALID')


# Luhn
def check_sum(card):
    sum = 0
    while card:
        sum += card % 10
        card //= 10
        two = (card % 10) * 2
        if two >= 10:
            sum += two % 10 + two // 10
        else:
            sum += two
        card //= 10

    if sum % 10 == 0:
        return True
    return False


# Check card pattern
def check_pattern(card):
    length = len(card)
    if length == AMEX_LEN and re.match(AMEX_START, card):
        print("AMEX")
    elif length == MASTERCARD_LEN and re.match(MASTERCARD_START, card):
        print("MASTERCARD")
    elif (length == MASTERCARD_LEN or length == VISA_LEN) and re.match(VISA_START, card):
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
