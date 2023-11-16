import re

# txt= "Dopasowuje pozycje, która nie jest granicą słowa."

# x= re.search("^Dopasowuje.*słowa.$", txt)
# print(x)

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
# x=re.findall("nie",txt,)
# print(x)

# x=re.split("\s",txt,)
# print(x)

# x=re.sub("nie","WOW",txt)
# print(x)

# x= re.findall(r'\bnie\b',txt)
# print(x)

# x= re.findall(r'[\w]+',txt)
# print(x)

# mail="jakub.chmielak@pw.edu.pl"
# x=re.match("^[\w\.]+@[\w\.]+",mail)
# print(bool(x))
# # x=re.split("@",mail)
# # print(x)

# txt1="rok 2023 bedzie lepszy."
# x=re.sub("\d",'X',txt)
# print(x)

# x=re.findall(r"\b[n]\w+", txt)
# print(x)

# kot="Nasz kot ma 6 lat i waży 4kg."
# x=re.findall("\d+",kot)
# print(x)

# x=re.search(r"^nasz",kot, re.IGNORECASE)
# print(x)

text= "Mój numer to 1230-456-7890."
x=re.search(r"\d{3}+-\d{3}+-\d{3}+",text)
print(x)