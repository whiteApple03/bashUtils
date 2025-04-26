#!/bin/bash

SUCCESS=0
FAIL=0
DIFF_RES=""

touch test.txt
echo -e "
Betty Botter bought sum butte




jean-paul sartre
test1.txt
1 2 3 4 5
MEOWWWWWWWWWWW   we we we we
" > test.txt

TEST_FILE="test.txt"

for var in -b -e -n -s -t -v
do
    TEST1="$var $TEST_FILE"
    echo "$TEST1"
    ./s21_cat $TEST1 > s21_cat.txt
    cat $TEST1 > cat.txt
    DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
    if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
    then
        (( SUCCESS++ ))
    else
    echo "$TEST1" >> log.txt
    (( FAIL++ ))
    fi
done
rm test.txt cat.txt s21_cat.txt

echo "УСПЕХ: $SUCCESS"
echo "FAIL: $FAIL"