# Design Specification for Querier

# Overview
The Querier is a standalone program that reads the index file produced by the Indexer, and page files produced by the Crawler, to answer search queries entered by the user.

## Data Structures

### Main Data Structures
1. Index: The Index is a hashtable where each entry is a word, and its value is a counter structure mapping document IDs to the number of occurrences of the word in that document.
2. Counters: This is used to store the number of occurrences of a word in various documents, and also for storing the scores of documents based on query processing.

### Auxiliary Data Structures
1. Words Array: An array of strings to store individual words from the user's query.
2. Results: A counters structure to hold the final scores of documents after processing the query.

## Algorithms
### Query Parsing
1. Tokenization: The query string is tokenized into individual words.
2. Normalization: Each word is normalized (e.g., converted to lowercase).
3. Validation: The parsed query is validated for syntactic correctness.

```plaintext
Function tokenize(query: string, numWords: pointer to integer) returns array of strings
    Begin
        1. If query is NULL
            a. Set numWords to 0
            b. Return NULL

        2. Initialize capacity to 10
        3. Create an array 'words' that can hold 'capacity' number of strings

        4. Set numWords to 0
        5. Set wordStart pointer to the beginning of the query

        6. While wordStart does not point to the end of the string (not '\0')
            a. Skip all whitespace characters from wordStart onwards
               (advance wordStart while it points to a space)
            
            b. Set wordEnd pointer equal to wordStart

            c. Advance wordEnd pointer until it points to a space or end of string
               (loop while wordEnd is not a space and not '\0')

            d. If wordEnd is not equal to wordStart (a word is found)
                i. Calculate wordLength as the difference between wordEnd and wordStart
                ii. Allocate memory for the new word and copy the word into this memory
                iii. Add the new word to the words array
                iv. Increment numWords by 1

                v. If numWords equals capacity
                    - Increase the capacity by multiplying it by 2
                    - Reallocate the words array with the new capacity

                vi. Move wordStart to wordEnd

            e. If wordStart is not at the end of the string, increment wordStart

        7. Return the words array
    End

```plaintext
Function and_sequence(words: array of strings, start: integer, end: integer, index: index_t) returns counters_t
    Begin
        1. Check if words or index is NULL
            a. If true, return NULL

        2. Create a new counters object 'result'
            a. If result is NULL, return NULL

        3. Get the counters for the word at 'start' index from the index and store it in 'temp'

        4. Iterate over 'temp', adding its counts to 'result' using the union_helper function

        5. Loop from 'start' to 'end'
            a. If the current word is not "and"
                i. Get the counters for the current word from the index and store it in 'temp'
                ii. Iterate over 'temp', updating 'result' using intersection_helper
                iii. Iterate over 'result', updating 'temp' using intersection_helper
                iv. Again, iterate over 'temp', updating 'result' using intersection_helper

        6. Return the 'result' counters object
    End

```pseudocode
Function or_sequence(words: array of strings, numWords: integer, index: index_t) returns counters_t
    Begin
        1. Create a new counters object 'result'
        
        2. Initialize 'start' to 0

        3. Loop through each word from 0 to numWords
            a. If the current word is "or"
                i. Call and_sequence with words, start, and (i - 1) as arguments to get 'subResult'
                ii. Perform counters union of 'result' and 'subResult'
                iii. Delete 'subResult'
                iv. Set 'start' to i + 1

        4. Call and_sequence with words, start, and numWords as arguments to get 'subResult'

        5. Perform final counters union of 'result' and 'subResult' to get 'final'
        
        6. Delete 'subResult'

        7. Return 'final'
    End

### Query Processing
1. rocessing 'AND' Sequences: Consecutive words without 'OR' are processed as an 'AND' sequence, intersecting the document sets.
2. Processing 'OR' Sequences: Words separated by 'OR' are processed by taking the union of the document sets resulting from each 'AND' sequence.
3. Scoring Documents: Documents are scored based on the number of occurrences of the query terms.

### Result Sorting and Display
1. Sorting: Documents are sorted in descending order based on their scores.
2. Display: The sorted list of documents is displayed, showing document ID, score, and URL.

### Modules and Functions

1. Main Module: Contains the main function and command line processing.
2. Interactive Mode: Handles the interactive query mode.
3. Query Processing: Includes functions to process, validate, and handle the queries.
4. Utilities: Helper functions for operations like tokenization, normalization, intersection, and union of counters.

### Testing

Comprehensive testing will be conducted to ensure that:

1. Query parsing and validation work correctly.
2. AND/OR operations produce correct results.
3. Document scoring and sorting are accurate.
4. Error handling and edge cases are properly managed.

