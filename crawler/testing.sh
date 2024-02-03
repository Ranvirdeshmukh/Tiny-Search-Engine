#!/bin/bash

# rm -rf ./output

# mkdir ./output


# Test with invalid depth (e.g., non-numeric or out of range)
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./output depth

# Testing  with a correct setup
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./output 1

# Testing with the ldepth of 2
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./output 2

#Testing wit the depth of 3
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./output 3

#Testing with the depth of 4
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./output 4


#Testing with the depth of 10
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ./output 10
