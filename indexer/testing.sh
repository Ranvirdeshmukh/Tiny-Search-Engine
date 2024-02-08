#!/bin/bash

# Example test for valid input
echo "Running indexer on sample data..."
./indexer ../data/letters ../data/letters.index

# Test index file creation
echo "Running indextest..."
./indextest ../data/letters.index ../data/letters-new.index

# Compare old and new index files (assuming you have a utility for this)
echo "Comparing index files..."
diff ../data/letters.index ../data/letters-new.index
