#!/bin/bash
read -p "Enter your prefix: " varprefix
read -p "Enter the left border: " varbordleft
read -p "Enter the right border: " varbordright
for file in ~/code/Labs-first-course/*
do
filename=$(basename $file)
prefixfile=${filename%_*}
wclen=$(wc -c "$file")
len=${wclen%' '*}
real_len=$[len-1]
if [[ "$prefixfile" == "$varprefix" ]] && [[ "$real_len" -ge "$varbordleft" ]] && [[ "$real_len" -le "$varbordright" ]]
then
rm $file
fi
done