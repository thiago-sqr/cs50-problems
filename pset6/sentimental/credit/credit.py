from cs50 import get_int


def main():
    while True:
        number = get_int("Number: ")
        if number > 0:
            break

    if luhnAlgorithm(number):
        print(f"{issuer(number)}")
    else:
        print("INVALID")


def luhnAlgorithm(number):
    sum = 0
    cursor = 1
    snumber = str(number)[::-1]

    for i in snumber:
        if cursor % 2 == 0:
            digit = int(i) * 2
            sdigit = str(digit)
            for c in sdigit:
                sum += int(c)
        else:
            digit = int(i)
            sum += digit
        cursor += 1

    return sum % 10 == 0


def issuer(number):
    string = str(number)
    size = len(string)
    first = int(string[0])
    second = int(string[1])

    if size == 15 and first == 3 and (second == 4 or second == 7):
        return "AMEX"
    elif size == 16 and first == 5 and (second in [1, 2, 3, 4, 5]):
        return "MASTERCARD"
    elif (size == 13 or size == 16) and first == 4:
        return "VISA"

    return "INVALID"


main()
