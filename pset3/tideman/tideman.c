#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
int strength(pair p);
void lock_pairs(void);
bool circle(int winner, int loser);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Well, on line 63 I set all preferences entries to zero
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        for (int i = j; i < candidate_count; i++)
        {
            int i_over_j = preferences[i][j];
            int j_over_i = preferences[j][i];

            if (i_over_j > j_over_i)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (i_over_j < j_over_i)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble Sort
    for (int i = 0; i < pair_count; i++)
    {
        int changes = 0;
        for (int j = i; j < pair_count - 1; j++)
        {
            if (strength(pairs[j]) < strength(pairs[j + 1]))
            {
                pair aux = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = aux;
                changes++;
            }
        }

        if (changes == 0)
        {
            break;
        }
    }
    return;
}

// Get the strength of a pair
int strength(pair p)
{
    int strength = preferences[p.winner][p.loser];
    return strength;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs()
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!circle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Seek for cycles in the locked matrix
bool circle(int winner, int loser)
{
    if (loser == winner)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        // Checking (loser -> i) path and (i -> winner) path
        if (locked[loser][i] && circle(winner, i))
        {
            return true;
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Verifying if every value in a row within a column is equal to zero
    for (int j = 0; j < candidate_count; j++)
    {
        int source = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == 0)
            {
                source++;
            }
        }

        if (source == candidate_count)
        {
            printf("%s\n", candidates[j]);
            break;
        }
    }
    return;
}
