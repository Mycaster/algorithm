#!/bin/bash

num=$1
if [ "${num}" == "" ]; then
	num=10;  #default 1000 numbers
fi


echo $num > testdata.txt; 
for i in $(seq 1 ${num});
do
	echo $RANDOM >> testdata.txt;
done