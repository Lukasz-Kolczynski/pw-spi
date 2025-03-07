# import pandas as pd
# import numpy as np

# def load_file(file_path):
#     try:
#         df = pd.read_csv(file_path, sep = ',', header = None)
#     except:
#         try:
#             df = pd.read_csv(file_path, sep = ';', header = None)
#         except:
#             df = pd.read_csv(file_path, sep = '\t', header = None)
#     return df


# cols = ["timestamp", "id", "dc1", "dc2", "dyskretne", "names", "wczwo1", "wczwo2", "wczwo_plus", "wczwo_minus", "x", "y", "z"]



# df = load_file('/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/data_01.dat')
# print(df)
# df.columns = cols
# print(df[['timestamp', 'id']].head()) 


# --------------------------next task -----------------------------

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def load_file(file_path):
    try:
        df = pd.read_csv(file_path, sep = ',', header = None)
    except:
        try:
            df = pd.read_csv(file_path, sep = ';', header = None)
        except:
            df = pd.read_csv(file_path, sep = '\t', header = None)
    return df


def check_duplicates(file_path):
    df = load_file(file_path)
    cols = ["timestamp", "id", "dc1", "dc2", "dyskretne", "names", "wczwo1", "wczwo2", "wczwo_plus", "wczwo_minus", "x", "y", "z"]

    df = load_file('/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/data_01_with_redundant.dat')
    df.columns = cols

    duplicate_rows = df[df.duplicated()]
    duplicate_count = len(duplicate_rows)

    if duplicate_count > 0:
        print(f"Znaleziono {duplicate_count} zduplikowanych wierszy.")
        print("Zduplikowane wiersze:")
        print(duplicate_rows)
    else:
        print("Brak zduplikowanych wierszy.")
    return duplicate_count


file_path = '/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/data_01_with_redundant.dat'
check_duplicates(file_path)


