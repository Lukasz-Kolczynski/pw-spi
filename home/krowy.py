krowy=input("Ile razy byłeś u krów: ")
lista_liczb = [0.5 * i for i in range(1, 30)]
try:
    krowy_float=float(krowy)
    if 0 <= krowy_float <= 7 and (krowy_float.is_integer() or krowy_float in lista_liczb):
        kasa_za_dzien=130
        naleznosc=krowy_float * kasa_za_dzien
        str(naleznosc)
        print("Tyle powinieneś dostac: ", (naleznosc))
        
    else:
        print("Niepoprawna wartość, wprowadź liczbe całkowitą lub co 0.5 z zakresu 0-7")
        
except ValueError:
    print("Niepoprawna wartość, wprowadź liczbe całkowitą lub co z zakresu 0-7")