# Output the possible readability of the reader for the given text
import re


# Constants
LOW, HIGH = 1, 16
FACTOR1, FACTOR2, FACTOR3, FACTOR4 = 100, 0.0588, 0.296, 15.8
SENTENCES, LETTERS = '[!?.]', '[a-zA-Z]'


# Main function
def main():
    text = input("Text: ")
    show_readability(text)


# Calculate the readability based on Coleman-Liau index and show that
def show_readability(text):
    total_sentences = len(re.findall(SENTENCES, text))
    total_words = len(text.split())
    total_letters = len(re.findall(LETTERS, text))
    res = round(FACTOR2 * FACTOR1 * total_letters / total_words - FACTOR3 * FACTOR1 *
                total_sentences / total_words - FACTOR4)

    if res < LOW:
        print('Before Grade 1')
    elif res >= HIGH:
        print("Grade 16+")
    else:
        print(f"Grade {res}")


if __name__ == "__main__":
    main()
