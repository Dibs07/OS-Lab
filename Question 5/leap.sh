# How do you write a shell script to enter a year and show a message whether the year is a leap year or not?
#!/bin/bash
echo "Enter a year: "
read year
if [ $(( $year % 4 )) -eq 0 ] && [ $(( $year % 100 )) -ne 0 ] || [ $(( $year % 400 )) -eq 0 ]
then
    echo "Leap year"
else
    echo "Not a leap year"
fi