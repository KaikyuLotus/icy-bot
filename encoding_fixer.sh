#!/bin/bash

find ./ -name "*.hpp" -o -name "*.cpp" -type f |
while read file
do
    dos2unix -n "$file" tmp.f
    rm "$file"
    mv tmp.f "$file"
done