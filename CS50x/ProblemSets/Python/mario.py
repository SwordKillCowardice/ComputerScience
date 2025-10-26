# Print a pyramid of a specific height
from cs50 import get_int


# Constants
LOW = 1
HEIGHT = 8
SPACE = 2


def main():
    while True:
        height = get_int("Height: ")
        if height >= LOW and height <= HEIGHT:
            break
    print_pyramid(height)


def print_left(row, height):
    print(" " * (height - row), end="")
    print("#" * row, end="")


def print_mid(count):
    print(" " * count, end="")


def print_right(row):
    print("#" * row)


def print_pyramid(height):
    for i in range(height):
        print_left(i + 1, height)
        print_mid(SPACE)
        print_right(i + 1)


if __name__ == "__main__":
    main()
