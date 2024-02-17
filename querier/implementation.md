  
# Querier Implementation Specification 



# Implementation Details 

 ## Overview 
The Querier is a standalone program that reads the index file produced by the TSE Indexer and page files produced by the TSE Crawler, and answers search queries submitted via stdin.

 ### Source Files 
querier.c: Main program file.
Major Functions
main

Validates the command-line arguments and calls the interactiveMode function to start the query processing loop.

 ### interactiveMode 

Runs a loop that continually prompts the user for queries until EOF (Ctrl+D). Each query is processed by calling processQuery.

 ### processQuery 

Takes a query string, tokenizes it, validates the tokenized query, and then processes the query if it's valid. It outputs the results or an error message if the query is invalid.

 ### tokenize 

Splits the query string into an array of words using whitespace as delimiters. It normalizes each word to lowercase.

 ### isValidQuery 

Checks the array of tokens to ensure the query meets the specified criteria (e.g., not starting or ending with an operator, no adjacent operators).

 ### and_sequence and or_sequence 

These functions process the 'and' and 'or' sequences in the query, respectively, and create a counters_t structure that represents the query results.

 ### print_query_results 

Prints the results of a query in a readable format, listing documents where matches were found along with their scores.

### counters_union and counters_intersection 

Perform set union and intersection operations on counters_t structures.

 ### Data Structures 
counters_t: Used for storing and manipulating counts associated with document IDs.


## Testing

The testing for the querier is comprehensive and structured to cover a range of scenarios. Each test aims to validate a specific aspect of the querier functionality. The tests are executed using a series of commands and input files, and the output is examined to ensure correctness and robustness of the program. Below are the details of the test cases:

1. Testing with No Arguments
Purpose: To check the program's response when no arguments are provided.
Command: ./querier
Expected Outcome: The program should report an error message about missing arguments and show the correct usage.
2. Testing with One Argument
Purpose: To verify the program's behavior with only one argument.
Command: ./querier /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2
Expected Outcome: The program should report an error indicating that a second argument is needed.
3. Testing with Specific Word 'dartmouth'
Purpose: To test the program's ability to find documents containing the word 'dartmouth'.
Command: ./querier /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2 /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2.index < testfile.txt
Expected Outcome: The program should list documents where 'dartmouth' appears, along with their scores.
4. Testing with Specific Word 'harvard'
Purpose: Same as above, but for the word 'harvard'.
[Repeat steps similar to the previous test case]
5. Testing with 'dartmouth and harvard'
Purpose: To check the program's handling of 'and' logic in queries.
[Repeat steps with appropriate command and expected outcome]
6. Testing with 'dartmouth or harvard'
Purpose: To verify 'or' logic in queries.
[Repeat steps with appropriate command and expected outcome]
7. Testing with Incomplete Query 'dartmouth and '
Purpose: To test how the program handles incomplete queries.
[Repeat steps with appropriate command and expected outcome]
8. Testing with Incomplete Query 'dartmouth or '
Purpose: Similar to the above, but with 'or' logic.
[Repeat steps with appropriate command and expected outcome]
9. Testing with 'pittsburgh or nanoscale or include'
Purpose: To test the program with a more complex query involving multiple 'or' operators.
[Repeat steps with appropriate command and expected outcome]


