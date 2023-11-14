                                        # https://strftime.org/
# Zwrócenie bieżącej daty i godziny:
from datetime import datetime
# now = datetime.now()
# print(now)
# print(now.year)
# print(now.strftime("%Y"))

# # Wyswietl akutalny miesiac jako nazwe, np. "Listopad"
# print(now.strftime("%b"))

# # Wyswietl akutalny dzien tygodnia jako nazwe, np. "Poniedzialek"
# print(now.strftime("%A"))

#Konwertuj napis "2023-11-15" na obiekt daty
date_object = datetime.strptime("2023-11-15", "%Y-%m-%d")
print(date_object)

past_date = datetime(2023, 11, 15)