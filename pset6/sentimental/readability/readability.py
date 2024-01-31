def main():
    text = input("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    grade = grade_text(letters, words, sentences)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def count_letters(text):
    letters = 0
    for c in text:
        if c.isalpha():
            letters += 1
    return letters


def count_words(text):
    words = len(text.split())
    return words


def count_sentences(text):
    sentences = 0
    punctuation = ['.', '!', '?']
    for c in text:
        if c in punctuation:
            sentences += 1
    return sentences


def grade_text(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    return index


main()
