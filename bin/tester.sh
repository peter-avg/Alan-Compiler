#!/bin/bash

files=(../test/examples/*.alan)
counter=0
failed_files=()

for file in "${files[@]}"
do
    echo "Testing $file"
    
    if ! ./alan -o "$file"; then
        echo "Failed to compile $file"
        echo "---------------------------------"
        counter=$((counter + 1))
        failed_files+=("$file")
        continue
    fi

    if ! ./a.out; then
        echo "Failed to run $file"
        continue
    fi

    echo "---------------------------------"
done

echo 
echo 

if [ $counter -eq 0 ]; then
    echo "All files passed"
elif [ $counter -eq 1 ]; then
    echo "$counter file failed to compile"
    echo "Failed file:"
else
    echo "$counter files failed to compile"
    echo "Failed files:"
fi

for file in "${failed_files[@]}"
do
    echo "$file"
done

