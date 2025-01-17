# Write a shell script to find the maximum number from given three numbers using if-else
#!/bin/bash
echo "Enter three numbers: "
read a b c
if [ $a -gt $b ] && [ $a -gt $c ]
then 
    echo "$a is maximum"
elif [ $b -gt $c ]
then
    echo "$b is maximum"
else
    echo "$c is maximum"
fi