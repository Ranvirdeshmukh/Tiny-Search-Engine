
#!/bin/bash
# Ranvir Deshmukh 
# Testing script for Indexer

# Define file paths
validPageDirectory="./output" 
validIndexFile="tst.index"
newIndexFile="newTst.index"
invalidPageDirectory="invalidDir"
readonlyIndexFile="./readonly.index" 

# Running indexer with valid arguments
echo "Running indexer with valid arguments..."
./indexer "$validPageDirectory" "$validIndexFile"
cat "$validIndexFile"
echo "---------------done---------------"

# Test with no arguments
echo "Testing with no arguments..."
./indexer
echo "---------------done---------------"

# Test with one argument
echo "Testing with one argument..."
./indexer "$validPageDirectory"
echo "---------------done---------------"

# Test with invalid page directory
echo "Testing with invalid page directory..."
./indexer "$invalidPageDirectory" "$validIndexFile"
echo "---------------done---------------"

# Test with read-only index file
echo "Testing with read-only index file..."
touch "$readonlyIndexFile"
chmod 444 "$readonlyIndexFile"
./indexer "$validPageDirectory" "$readonlyIndexFile"
chmod 644 "$readonlyIndexFile" # Reset permissions
echo "---------------done--------------"

# Memory leak check for indexer
echo "Memory leak check for indexer"
valgrind --leak-check=full ./indexer "$validPageDirectory" "$validIndexFile"
echo "---------------done---------------"

# Memory leak check for indextest
echo "Memory leak check for indextest"
valgrind --leak-check=full ./indextest "$validIndexFile" "$newIndexFile"
echo "---------------done---------------"
