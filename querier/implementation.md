  
# Querier Implementation Specification (h1)



# Implementation Details (h3)

 # Overview (h4)
The Querier is a standalone program that reads the index file produced by the TSE Indexer and page files produced by the TSE Crawler, and answers search queries submitted via stdin.

 # Source Files (h6)
querier.c: Main program file.
Major Functions
main

Validates the command-line arguments and calls the interactiveMode function to start the query processing loop.

 # interactiveMode (h6)

Runs a loop that continually prompts the user for queries until EOF (Ctrl+D). Each query is processed by calling processQuery.

 # processQuery (h6)

Takes a query string, tokenizes it, validates the tokenized query, and then processes the query if it's valid. It outputs the results or an error message if the query is invalid.

 # tokenize (h6)

Splits the query string into an array of words using whitespace as delimiters. It normalizes each word to lowercase.

 # isValidQuery (h6)

Checks the array of tokens to ensure the query meets the specified criteria (e.g., not starting or ending with an operator, no adjacent operators).

 # and_sequence and or_sequence (h6)

These functions process the 'and' and 'or' sequences in the query, respectively, and create a counters_t structure that represents the query results.

 # print_query_results (h6)

Prints the results of a query in a readable format, listing documents where matches were found along with their scores.

# counters_union and counters_intersection (h6)

Perform set union and intersection operations on counters_t structures.

 # Data Structures (h4)
counters_t: Used for storing and manipulating counts associated with document IDs.

# Testing Plan (h2)

Unit Testing
tokenize: Test with various strings, including edge cases like empty strings, strings with multiple spaces, and strings with special characters.
isValidQuery: Test with valid and invalid queries, including edge cases like queries that start or end with an operator and queries with adjacent operators.

