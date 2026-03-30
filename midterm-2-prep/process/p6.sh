#!/bin/bash

gcc p6.c 
mkdir p6_out 
truncate -s 0 p6_diff.txt

for ((i=0; i<$1;i++)) do
	./a.out 
	cat p6.txt > p6_out/p6_$i.txt 
done

for ((i=0;i<$1;i++)) do
	for((j=i+1;j<$1;j++)) do
		diff p6_out/p6_$i.txt p6_out/p6_$j.txt >> p6_diff.txt 
	done
done
