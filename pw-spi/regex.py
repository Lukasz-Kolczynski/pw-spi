import re

txt= "Dopasowuje pozycje, która nie jest granicą słowa."

x= re.search("^Dopasowuje.*słowa.$", txt)
print(x)

# findall - zwracaja liste zawierajaca wszystkie wystapienia
# search - zwraca obiekt match, jesli w dowolnym miejscu znajdzie dopasowanie
# split - zwraca liste, w ktorej ciagu znakow zostal podzielony przy kazdym dopasowaniu
# sub - zastepuje jedno lub wiecej wystapien

# [a-z] - zwraca dopasowania pasujace do wzoru od a-z, male litery
# [A-Z] -
# [0-9] -
# [678] -
# [a-k] -
# [^michal] -
# #00-62
# [0-6][0-9] -> 56 pasuje, 72 juz nie
# [+]


txt= "Dopasowuje nie poznieycje, która nie jest grannieicą nie słowa."
x=re.findall("nie",txt)
print(x)