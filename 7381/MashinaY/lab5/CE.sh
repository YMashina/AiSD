#!/bin/bash
gcc ./Source/Lab5.c -lm -o Lab5
echo 'Test 1:'
cat ./Tests/Test1.txt
echo -e '\n'
./Lab5 < ./Tests/Test1.txt
echo -e ''
echo 'Test 2:'
cat ./Tests/Test2.txt
echo -e '\n'
./Lab5 < ./Tests/Test2.txt
echo -e ''
echo 'Test 3:'
cat ./Tests/Test3.txt
echo -e '\n'
./Lab5 < ./Tests/Test3.txt
echo -e ''
echo 'Test 4:'
cat ./Tests/Test4.txt
echo -e '\n'
./Lab5 < ./Tests/Test4.txt
echo -e ''
echo 'Test 5:'
cat ./Tests/Test5.txt
echo -e '\n'
./Lab5 < ./Tests/Test5.txt
echo 'Test 6:'
cat ./Tests/Test6.txt
echo -e '\n'
./Lab5 < ./Tests/Test6.txt 
