import csv
import sys
from copy import deepcopy


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py DATABASE SEQUENCE")
        sys.exit(1)

    # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for data in reader:
            database.append(data)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        DNA = file.readline()

    # TODO: Find longest match of each STR in DNA sequence
    keys = list(database[0])
    name_key = keys.pop(0)
    longest_list = []

    for subsequence in keys:
        n = longest_match(DNA, subsequence)
        longest_list.append(n)

    # TODO: Check database for matching profiles
    dbcopy = deepcopy(database)
    sample = {}

    for data in dbcopy:
        del data[name_key]

    for i in range(len(keys)):
        sample[keys[i]] = str(longest_list[i])

    for i in range(len(database)):
        if dbcopy[i] == sample:
            print(database[i][name_key])
            break
    else:
        print('No match')

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
