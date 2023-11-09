# import requests
# # waluta_z
# #waluta_na
# #kwote
# def przelicz(kwota:float, waluta_z:str, waluta_na:str) -> float:
#     url = f"https://v6.exchangerate-api.com/v6/563075f9e11695fd9ef35c70/latest/{waluta_z}"
#     response =requests.get(url)
#     lista_walut = response.json()['conversion_rates']
#     wynik= kwota * lista_walut[waluta_na]
#     return wynik


# print(przelicz(100,'USD','PLN'))



# # import math
# from math import sqrt
# print (sqrt(10))



# import random
# #Generowanie losowej liczby całkowitej z zakresu 1-100:
# print(random.randint(1,100))

# #wybor losowego elementu z listy:
# fruits = ["apple", "banana", "orange"]
# print(random.choice(fruits))



# #Mieszanie listy:
# numbers= [1,2,3,4,5]
# random.shuffle(numbers)
# print(numbers)



# #Zwrócenie bieżącego czasu w sekundach
# import time
# print(time.time())

#Zwrócenie bieżącej daty i godziny:
import datetime
now= datetime.datetime.now()
print(now)

#Napisz program który sprawdza czy dany format daty jest prawidłowy
'dd-mm-yyyy'
todays_date= datetime .date.today()
print(todays_date)

        # %Y - year [0001,...,2018,2019,...,9999]
        # %m - month[01,02,...,11,12]
        # %d - day [01,02,...,30,31]
        # %H - hour [00,01,...,22,23]
        # %M - minute [00,01,...,58,59]

#1 stycznia 1970 - UTC
print (datetime.date.fromtimestamp(10000000000).year)
a=datetime.datetime(2022,12,28,23,55,59,342380).day
print(a)
a= datetime.time(11,34,56)
print(a.minute)


now=datetime.datetime.now()
print(now.strftime("%H"))
dsds




# #Napisz kod, który wypisze listę wszystkich plików w bieżącym katalogu.
# import os
# for file in os.listdir():
#     print(file)

# file_path= "abc.py"
# if os.path.exists(file_path):
#     print('file already exisits')

# print(os.path.isfile(file_path))
# print (os.listdir('linux'))
# os.rename (file_path, file_path+ "nowy_plik.txt")


