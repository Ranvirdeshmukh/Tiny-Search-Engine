// Ranvir Deshmukh 
//LAB 5

Overview

The Indexer is a key component of the Tiny Search Engine (TSE). It reads documents produced by the Crawler, builds an index mapping from words to documents and the frequency of the word in each document, and writes this index to a file.

Data Structures

Hashtable: Used for efficiently mapping unique words to their corresponding counters structure.
Counters: Used to keep track of the number of occurrences (frequencies) of a word in each document.
Algorithms

Parsing Documents: Each document fetched by the Crawler is parsed word by word. Words are normalized (converted to lowercase) for consistency.
Building the Index: For each word in a document, if the word is not already in the hashtable, a new counters structure is created and added. If the word exists, its frequency is incremented in the respective document's counter.

Testing Plan

Unit Testing
Test 1: Indexer with valid arguments (existing page directory and writable index file).
Test 2: Indexer with no arguments (should fail).
Test 3: Indexer with one argument (should fail).
Test 4: Indexer with three or more arguments (should fail).
Test 5: Indexer with non-existent page directory (should fail).
Test 6: Indexer with existing but read-only index file (should fail).
Integration Testing
Run indexer on different page directories and compare output with expected index files.
Memory Leak Check
Use Valgrind to check for memory leaks and errors in both indexer and indextest.

Memory leaks:
HEAP SUMMARY:
==2397242==     in use at exit: 0 bytes in 0 blocks
==2397242==   total heap usage: 334 allocs, 334 frees, 22,228 bytes allocated
==2397242== 
==2397242== All heap blocks were freed -- no leaks are possible

no memory leaks in the program.
Thank you so much,
Ranvir Deshmukh