# . Write a shell script to find factorial of a given number. 
#!/bin/bash
echo "Enter a number: "
read n
fact=1
while [ $n -gt 1 ]
do
    fact=$(( $fact * $n ))
    n=$(( $n - 1 ))
done
echo "Factorial is $fact"