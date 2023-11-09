# def powitanie (imie):
#     print (f"Witaj {imie} w świecie pythona")
# powitanie("Anna")



# def max_min (a, b, c):
#     return max(a,b,c), min(a,b,c)
# print(max_min(10,20,30))



# def dlugosc_ciagu(ciag):
#     return len(ciag)
# print(dlugosc_ciagu("Python"))



# def silnia(n):
#     if n == 0:
#         return 1
#     else:
#         return n * silnia(n-1)
# t = silnia(5)
# print(t)



# def sumuj(a: int, b: int) -> int:
#     wynik= a+b
#     return wynik
# x=5
# y=10
# suma = sumuj (x,y)
# print("Wynik dodawania:", suma)



# import requests
# response=requests.get('http://www.google.com')
# #print(response.text)
# print(response.status_code)

                                                    #pip3 install requests



#Czy istnieje @
#walidacja pustych znaków
#User ma od 6 do 30 znaków
#domena to pw.edu.pl

# def validate_email(email):
#     if email.count('@') != 1:
#         raise ValueError("To nie jest adres mailowy")
#     #podzial adresu na username i domene
#     parametry= email.split('@')
#     #print(parametry.count('@'))
# try:
#     validate_email('jakub.chmielak@pw.edu.pl')
# except ValueError as e:
#     print(f"Komunikat błedu: {e}")


# import re
# def vailtade_password(password):
#     if len(password) <8:
#         return False
#     if not re.search(r'[A-Z]',password):
#         return False
#     if not re.search (r'\d', password):
#         return False
#     return True
# password = input ("Podaj hasło: ")
# if vailtade_password(password):
#     print("Hasło jest poprawne.")
# else:
#     print("Hasło jest niepoprawne")



# def validate_username(nazwa):   
#     if nazwa.isalnumd
#     ():
#         if 3<= len(nazwa) <=16:
#             return True
#     return False

# nazwa=input("Podaj nazwe: ")
# if validate_username(nazwa):
#     print("Poprawna nazwa")
# else:
#     print("Niepoprawna nazwa")



# def validate_ip(adres):
#     czesci= adres.split('.')
#     if len(czesci) !=4:
#         return False
#     for czesci in czesci:
#         if not czesci.isdigit():
#             return False
#         oktet= int(czesci)
#         if oktet <0 or oktet> 255:
#             return False
#     return True
# adres_ipv4=input("Wprowadz adres ipv4: ")
# if validate_ip(adres_ipv4):
#     print("adres poprawny")
# else:
#     print("adres niepoprawny")



# nip= 1234567890

# def validate_nip(nip:str):
#     weights= [6,5,7,2,3,4,5,6,7]
#     suma= 0
# #sprawdzamy czy mamy 10 znakow
# #czy wszystkie sa cyframi
#     if len(nip) !=10:
#         False
#     if nip.isdigit():
#         False
#     for i in range(9):
#         suma+= int(nip[i]) * weights[i]
#     if suma%11== int(nip[9]):
#         False
#     return True


# if validate_nip('6543256986'):
#     print("Nip jest OK")
# else:
#     print("Jestes oszust es")
#dsds
