#!/bin/bash
gcc ./Source/L1.c -o L1
echo 'Test 1:'
cat ./Tests/test1.txt
echo -e '\n'
./L1 < ./Tests/test1.txt
echo -e ''
echo 'Test 2:'
cat ./Tests/test2.txt
echo -e '\n'
./L1 < ./Tests/test2.txt
echo -e ''
echo 'Test 3:'
cat ./Tests/test3.txt
echo -e '\n'
./L1 < ./Tests/test3.txt
echo -e ''
echo 'Test 4:'
cat ./Tests/test4.txt
echo -e '\n'
./L1 < ./Tests/test4.txt
echo -e ''
echo 'Test 5:'
cat ./Tests/test5.txt
echo -e '\n'
./L1 < ./Tests/test5.txt
echo -e ''
echo 'Test 6:'
cat ./Tests/test6.txt
echo -e '\n'
./L1 < ./Tests/test6.txt