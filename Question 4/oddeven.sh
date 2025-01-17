# Write a shell script to check whether the given number is odd or even.
#!/bin/bash
echo "Enter a number: "
read num
if [ $(( $num % 2)) -eq 0 ] 
then
    echo "Even"
else
    echo "Odd"
fi
