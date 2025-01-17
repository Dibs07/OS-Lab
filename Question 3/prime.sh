# Write a shell script to find out whether a number is prime or not.
#!/bin/bash
echo "Enter a number: "
read num
i=2
flag=0
j=$((( $num / 2 ) + 1))
while [ $i -lt $j ]
do
    if [ $(( $num % $i )) -eq 0 ]
    then
        flag=1
        break
    fi
    i=$(( $i + 1 ))
done
if [ $flag -eq 0 ]
then
    echo "Prime"
else
    echo "Not Prime"
fi