#!/bin/bash 
# ./witaj.sh
# echo "Witaj świecie"

# nazwa=Jan

# echo "Witaj, $nazwa"


# a=10

# b=10

# if [ $a -eq $b]: then
#     echo "Równe"
# else
#     echo "Różne"
# fi


# echo "Jak masz na imie?"
# read imie
# echo "Cześć $imie!"


echo "Podaj liczbe"
read liczba
if [ $liczba -gt 10 ]
then
    echo "Liczba większa od 10"
else
    echo "Liczba mniejsza lub rowna 10"
fi

for i in {1.liczba}
do
    echo " Iteracja $i"
done

while [ $liczba -le 5 ]
do  echo "Liczba: $liczba"
    ((liczba++))

