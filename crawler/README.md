# CS50 TSE Lab4
## Ranvir Deshmukh
## Ranvirdeshmukh


In the crawler directory,

Write a program crawler.c according to the Specs.
Write a Makefile that will, by default, build the crawler executable program.
Add a make clean target that removes files produced by Make or your tests.
Add a make test target that tests your crawler. Read about testing below.
Save the output of your tests with make test &> testing.out.
Add a README.md file to describe any assumptions you made while writing the crawler, any ways in which your implementation differs from the three Specs, or any ways in which you know your implementation fails to work.
Write a .gitignore file telling Git to ignore any unnecessary files in this directory (anything not already covered by the top-level .gitignore).

implementation
- I have implemented the following function as demanded by the lab into the crawler.c :
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[],char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

I also ran the testing.sh file with different numbers of depth and the output is in the testing.out file. Moreover, I have 0 memory leaks :
"HEAP SUMMARY:
==3776294==     in use at exit: 0 bytes in 0 blocks
==3776294==   total heap usage: 1,195 allocs, 1,195 frees, 307,207 bytes allocated
==3776294== 
==3776294== All heap blocks were freed -- no leaks are possible
==3776294== 
==3776294== For lists of detected and suppressed errors, rerun with: -s
==3776294== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"

The program runs in the best possible way completely.

This lab was extremely interesting and I am looking forward to finishing the TSE and this is the best thing i have learned soo far. Thank you so much.

Ranvir Deshmukh

