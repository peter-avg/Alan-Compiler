#!/bin/bash

files=(examples/*.alan)

for file in "${files[@]}"
do
    echo "Testing $file"
    ./alan "$file"
    echo "---------------------------------"
done
