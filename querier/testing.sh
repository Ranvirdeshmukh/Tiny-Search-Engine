# Ranvir Deshmukh 
#


#Testing with no arguments 
echo -e "testing with no arguments\n"
./querier
echo -e "---------------------END-------------------------"


#Testing with one argument
echo -e "testing with one arguments\n"
./querier /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2
echo -e "---------------------END-------------------------"


echo -e "the word - 'dartmouth' is tested"
./querier /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2 /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2.index < testfile.txt
echo -e "---------------------END-------------------------"

echo -e "the word - 'harvard' is tested"
./querier /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2 /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2.index < testfile1.txt
echo -e "---------------------END-------------------------"

echo -e " 'dartmouth and harvard' are tested"
./querier /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2 /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2.index < testfile2.txt
echo -e "---------------------END-------------------------"


echo -e " 'dartmouth or harvard' are tested"
./querier /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2 /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2.index < testfile3.txt
echo -e "---------------------END-------------------------"


echo -e " 'dartmouth and ' are tested"
./querier /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2 /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2.index < testfile4.txt
echo -e "---------------------END-------------------------"

echo -e " 'dartmouth or ' are tested"
./querier /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2 /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2.index < testfile5.txt
echo -e "---------------------END-------------------------"

echo -e " 'harvard or ' are tested"
./querier /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2 /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2.index < testfile6.txt
echo -e "---------------------END-------------------------"


echo -e " pittsburgh or nanoscale or include "
./querier /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2 /thayerfs/home/f006bpr/cs50-dev/shared/tse/output/wikipedia-2.index < testfile7.txt
echo -e "---------------------END-------------------------"