                                        # https://strftime.org/
# Zwrócenie bieżącej daty i godziny:
from datetime import datetime
now = datetime.now()
# print(now)
# print(now.year)
# print(now.strftime("%Y"))

# # Wyswietl akutalny miesiac jako nazwe, np. "Listopad"
# print(now.strftime("%b"))

# # Wyswietl akutalny dzien tygodnia jako nazwe, np. "Poniedzialek"
# print(now.strftime("%A"))

# #Konwertuj napis "2023-11-15" na obiekt daty
# date_object = datetime.strptime("2023-11-15", "%Y-%m-%d")
# print(date_object)

# past_date = datetime(2023, 11, 15)

# # 2023-Nov-15
# from datetime import timedelta
# # Dodaj 5 dni do aktualnej daty
# print(now + timedelta(days=5))
# # Odejmij 2 tygodnie od aktualnej daty
# print(now - timedelta(weeks=2))

# #Wyswietl roznice w dniach miedzy 1 stycznia 2023 a dzisiaj
# past_date = datetime(2023, 1, 1)
# day= now - past_date
# print(day.days)

# import calendar
# #Sprawdz czy rok 2024 jest rokiem przestepnym
# rok = 2024
# if calendar.isleap(rok):
#     print(f'{rok} jest rokiem przestepnym')
# else:
#     print(f'{rok} nie jest rokiem przestepnym')

# wyswietl numer biezacego roku tygodnia
print(now.strftime("%U"))