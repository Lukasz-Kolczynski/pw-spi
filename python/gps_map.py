import pandas as pd
import folium

file_path = "/mnt/c/Users/takty/Desktop/gps_track.csv"

try:
    df = pd.read_csv(file_path, encoding="latin1", delimiter=",", header=1, on_bad_lines='skip')
    print("Dane załadowane pomyślnie!")
except Exception as e:
    print(f"Błąd wczytywania pliku: {e}")
    exit()

required_columns = ['CurrentLatitude', 'CurrentLongitude', 'SSID', 'MAC', 'RSSI', 'AuthMode']
if not all(col in df.columns for col in required_columns):
    print("Brak wymaganych kolumn w danych.")
    exit()

m = folium.Map(location=[df["CurrentLatitude"].mean(), df["CurrentLongitude"].mean()], zoom_start=12)

for _, row in df.iterrows():
    folium.Marker(
        location=[row["CurrentLatitude"], row["CurrentLongitude"]],
        popup=f"SSID: {row['SSID']}<br>MAC: {row['MAC']}<br>RSSI: {row['RSSI']}",
        tooltip=row["SSID"],
        icon=folium.Icon(color="blue" if row["AuthMode"] == "[OPEN]" else "red"),
    ).add_to(m)

m.save("mapa_wifi.html")
print("Mapa zapisana jako 'mapa_wifi.html'.")
