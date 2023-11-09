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



#Zwrócenie bieżącego czasu w sekundach
import time
print(time.time())

#Zwrócenie bieżącej daty i godziny:
import datetime
now= datetime.datetime.now()
print(now)



#