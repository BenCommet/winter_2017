#!/bin/bash
while IFS='' read -r line || [[ -n "$line" ]]; do
	array=($line)
	mkdir -p ${array[0]}
	touch ${array[0]}/${array[1]}
done < "$1"
