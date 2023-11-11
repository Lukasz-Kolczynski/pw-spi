from sympy import Eq, symbols, solve, sin

# Wprowadź dane od użytkownika
m1 = float(input("Podaj masę pierwszego ciała: "))
m2 = float(input("Podaj masę drugiego ciała: "))
v1p = float(input("Podaj prędkość początkową pierwszego ciała: "))

# Deklaracja symboli
v1k, v2k, kat = symbols('v1k v2k kat')

# Tworzenie równań
eq1 = Eq((m1 * (v1k**2)) / 2 + (m2 * (v2k**2)) / 2, m1 * (v1p**2) / 2)
eq2 = Eq(m1 * v1k * ((3**0.5) / 2) + m2 * v2k * (1 - sin(kat)**2)**0.5, m1 * v1p)
eq3 = Eq(m1 * v1k * 0.5 - m2 * v2k * sin(kat), 0)

# Rozwiązanie równań
wynik = solve((eq1, eq2, eq3), (v1k, v2k, kat))

# Wybierz pierwsze rozwiązanie z wyniku
wynik = wynik[0]

# Wyświetl wyniki
print(f"Prędkość końcowa pierwszego ciała: {wynik[0]}")
print(f"Prędkość końcowa drugiego ciała: {wynik[1]}")
print(f"Kąt odbicia ciała: {wynik[2]}")
