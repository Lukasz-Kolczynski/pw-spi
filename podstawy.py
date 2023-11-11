# ctr + k + c/u




# imie=input("Podaj swoje imie: ")
# print("Witaj, "+imie+ "!")



# pierwsza_liczba=10
# druga_liczba=2



# sum= pierwsza_liczba + druga_liczba
# sub= pierwsza_liczba - druga_liczba
# div= pierwsza_liczba / druga_liczba
# nul= pierwsza_liczba * druga_liczba
# print("suma: ", sum, "różnica: ",sub,"dzielenie: ", div,"mnożenie: ", nul)



# tekst="Python"
# pierwsza_litera= tekst[0]
# ostatnia_litera= tekst[-1]
# print("To jest ostatnia litera: ", ostatnia_litera)
# print("To jest pierwsza litera: ", pierwsza_litera)

# tekst= "Python jest Super!"
# małe_litery=tekst.lower()
# print("Oto tekst z małych liter: ", małe_litery)



# tekst="To jest przykład tekstu z literą a."
# nowy_tekst=tekst.replace("a", "x")
# print("To jest nowy tekst: ", nowy_tekst)


# tekst="To jest przykład tekstu z literą a."
# lista_slow=tekst.split()
# print(lista_slow)



# tekst="        To jest tekst z nadmiernymi    białymi znakami  "
# nowy_tekst=tekst.strip()
# print("To jest tekst poprawny: ", nowy_tekst)



# tekst="To jest przykład tekstu z literą a."
# liczba_a=tekst.count("a")
# print("Tyle 'a' jest w tym zdaniu: ", liczba_a)


# tekst="Python jest super!"
# if tekst.startswith("Python"):
#     print("Tekst ten zaczyna sie od słowa Python")
# else:
#     print("Tekst nie zaczyna sie od słowa Python")
    


# tekst="To jest przykład tekstu z literą a"
# odwrocony_tekst=tekst[::-1]
# print("Tak wygląda odwrócony tekst: ", odwrocony_tekst)



# tekst="To jest przykład tekstu z literą a"
# odwrocony_tekst=tekst[10:]
# print("Tak wygląda odwrócony tekst: ", odwrocony_tekst)



liczba_pierwsza=input("Wprowadź liczbe pierwszą: ")
liczba_druga=input("Wprowadź liczbe drugą: ")
float(liczba_pierwsza)
float(liczba_druga)
opcja=input("Co mam zrobic z tymi liczbami? [Wybierz i wypisz opcje (dodaj, odejmij, pomnóż, podziel)]: ")
if opcja=="dodaj": 
    wynik_dodawania=liczba_pierwsza + liczba_druga
