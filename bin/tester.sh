#!/bin/bash

files=(../test/examples/*.alan)

for file in "${files[@]}"
do
    echo "Testing $file"
    ./alan "$file"
    echo "---------------------------------"
done
