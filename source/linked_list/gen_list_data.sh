#!/bin/bash

num=$1
if [ "${num}" == "" ]; then
	num=10;  #default 15 numbers
fi

echo -n "$num " > list_testdata.txt;
for i in $(seq 1 ${num});
do
	echo -n "$RANDOM " >> list_testdata.txt;
done

echo "" >> list_testdata.txt
echo -n "$num " >> list_testdata.txt;
for i in $(seq 1 ${num});
do
	echo -n "$RANDOM " >> list_testdata.txt;
done

echo "" >> list_testdata.txt
