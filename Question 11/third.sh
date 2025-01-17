# Write a shell script for exchange of given two numbers without using 3rd variable .
#!/bin/bash
echo "Enter two numbers: "
read a b
echo "Before swapping: $a $b"
a=$(( $a + $b ))
b=$(( $a - $b ))
a=$(( $a - $b ))
echo "After swapping: $a $b"