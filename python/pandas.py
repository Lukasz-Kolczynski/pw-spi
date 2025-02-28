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
