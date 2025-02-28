import pandas as pd
import numpy as np

def load_file(file_path):
    try:
        df = pd.read_csv(file_path, sep = ',', header = None)
    except:
        try:
            df = pd.read_csv(file_path, sep = ';', header = None)
        except:
            df = pd.read_csv(file_path, sep = '\t', header = None)
    return df


cols = ["timestamp", "id", "dc1", "dc2", "dyskretne", "names", "wczwo1", "wczwo2", "wczwo_plus", "wczwo_minus", "x", "y", "z"]



df = load_file('/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/data_01.dat')
print(df)
df.columns = cols
print(df[['timestamp', 'id']]) 