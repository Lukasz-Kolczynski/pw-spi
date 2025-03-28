# 7,3,5,2,1,8,3,4,6 ... (bardzo duży zbiór danych)

# Etap I:

# Dzielimy ten zbiór na mniejsze zbiory

# plik 1: 7,3,5
# plik 2: 2,1,8
# plik 3: 3,4,6

# Etap II:

# Wczytujemy pliki pojedyńczo  
# sortuje go 
# zapisuje spowrotem do pliku
# read(plik1)->sort->plik 1: 3 , 5 ,7
# read(plik2)->sort->plik 2: 1, 2 ,8
# read(plik3)->sort->plik 3: 3 , 4 ,6

# Etap III:

# Dziel te pliki na pary np łącze plik 1 i 2 powstaje plik_1_2

# Powtarzam ten proces wielkortonie , mam zbiór plików grupuje łącze je (wielokrotny proces) aż otrzymam jeden plik

        
# plik 1: 3 , 5 ,7
#         ^
#         |
# plik 2: 1, 2 ,8
#         ^
#         |


# łapka na pierwszy i drugi plik na pierwsa liczbe wstawiam mniejsza , łapke przesuwam w pliku z którego pochodzi pierwsza liczba i porównuje ją z łapką załączną na pliku gdzie łapki nie zmieniłem 
# 1,3->1 1 2,3->3  2 8,3-> 3 (!! tutaj liczba w pliku 1 jest mniejsza wiec biore liczbe z pliku 1 i na dole w pliku 2 porównuje liczby(tam łapka stoi w miejscy )) 5,8-> 5 7,8->7 zostało 8 koniec
# plik_1_2: 1,2,3,5,7,8

#===================================================================

import os
import random
from timeit import default_timer as timer

#poniższe generowanie jest to 1 części zadania, tzn generuje plik z samymi liczbami
#  (jedna liczba w jednym wierszu)
# 4
# 10
# ...


# def generate_data(file_path, size, max_value):
#     with open(file_path, "w") as file_out:
#         for i in range(size-1):
#             number = random.randint(0, max_value)
#             file_out.write(str(number) + "\n")
#         number = random.randint(0, max_value)
#         file_out.write(str(number))


#poniższe generowanie jest to 2 części zadania, tzn generuje plik z w postaci (liczba, zliczbaliczba)
#  (jedna liczba w jednym wierszu)
# 4,z44
# 10,z1010
# ...

def generate_data(file_path, size, max_value):
    with open(file_path, "w") as file_out:
        for i in range(size - 1):
            number = random.randint(0, max_value)
            file_out.write(str(number) + "," + "z" + str(number) + str(number) +  "\n") 
        number = random.randint(0, max_value)
        file_out.write(str(number) + "," + "z" + str(number) + str(number))


def divide_file(file_path, size, working_directory):
    with open(file_path, "r") as file_data:
        file_number = 1
        end = False

        while not end:
            file_out_name = f"data_{file_number}.dat"
            file_out_path = os.path.join(working_directory, file_out_name)
            file_number += 1
            counter = 0

            line = file_data.readline().strip()
            if not line:
                break

            with open(file_out_path, "w") as file_out:
                file_out.write(line)
                counter += 1

                while counter < size:
                    line = file_data.readline().strip()
                    if not line:
                        end = True
                        break

                    file_out.write("\n" + line)
                    counter += 1
            if file_number % 10 == 0:
                print(f"{file_number} of {size}")

def get_all_files_in_directory(working_directory):
    files = []
    for file in os.listdir(working_directory):
        file_path= os.path.join(working_directory, file)

        if not os.path.isdir(file_path):
            files.append(file)
    return files

def get_first(el):
    return int(el.split(',')[0])

def sort_data_in_directory(working_directory):
    files = get_all_files_in_directory(working_directory)
    c = 1
    number_of_files = len(files)

    for file in files:
        file_path = os.path.join(working_directory, file)
        data = None
        with open(file_path, "r") as source_file:
            data = [(line.strip()) for line in source_file]
        data.sort(key = get_first)

        with open(file_path, "w") as result_file:
            for i in range(len(data)-1):
                result_file.write(str(data[i])+ "\n")
            result_file.write(str(data[-1]))
        
        if c % 10 == 0:
            print(f"{c} of {number_of_files}")


def merge_two_file(working_directory, file_in_1_name, file_in_2_name, file_out_name):
    file_in_1_path = os.path.join(working_directory, file_in_1_name)
    file_in_2_path = os.path.join(working_directory, file_in_2_name)
    file_out_path = os.path.join(working_directory, file_out_name)


    with open(file_in_1_path, "r") as file_in_1:
        with open(file_in_2_path, "r") as file_in_2:
            with open(file_out_path, "w") as file_out:
                line_1 = file_in_1.readline().strip()
                line_2 = file_in_2.readline().strip()

                while True:
                    if line_1 and line_2:
                        v1 = (int(line_1.split(',')[0]))
                        v2 = (int(line_2.split(',')[0]))

                        if v1 < v2:
                            file_out.write(str(line_1))
                            line_1 = file_in_1.readline().strip()
                        else:
                            file_out.write(str(line_2))
                            line_2 = file_in_2.readline().strip()
                    elif line_1 and not line_2:
                        file_out.write(line_1)
                        line_1 = file_in_1.readline().strip()
                    elif not line_1 and line_2:
                        file_out.write(line_2)
                        line_2 = file_in_2.readline().strip()
                    else:
                        break

                    if line_1 or line_2:
                        file_out.write("\n")

def merge_one_iteration(working_directory, files ,iteration, remove_source_files=True):
    dim = 2
    list_of_pairs = [files[i:i+dim] for i in range(0,len(files),dim)]

    p = 1

    for pair in list_of_pairs:
        if len(pair) == dim:
            file_in_1_name = pair[0]
            file_in_2_name = pair[1]
            file_out_name = f"{iteration}_{p}.dat"
            merge_two_file(working_directory, file_in_1_name, file_in_2_name, file_out_name)

        else:
            path_current = os.path.join(working_directory, pair[0])
            path_new = os.path.join(working_directory, f"{iteration}_{p}.dat")
            os.rename(path_current, path_new)

        p += 1

    if remove_source_files:
        for file in files:
            file_path = os.path.join(working_directory, file)
            if not os.path.isdir(file_path):
                if os.path.exists(file_path):
                    os.remove(file_path)


def merge_all_files(working_directory):
    files = get_all_files_in_directory(working_directory)
    number_of_files = len(files)
    iteration = 1
    safe = 10

    while (number_of_files > 1 and safe > 0):
        safe -= 1
        merge_one_iteration(working_directory, files, iteration, True)
        files = get_all_files_in_directory(working_directory)
        number_of_files = len(files)
        iteration += 1

# def Counter_files(file_path_1, file_path_2):

    
#     count_1 = count_occurrences(file_path_1)
#     count_2 = count_occurrences(file_path_2)
    
#     print("Liczba wystąpień w pliku wygenerowanym:")
#     for number in sorted(count_1.keys()):
#         print(f"{number}: {count_1[number]}")
    
#     print("\nLiczba wystąpień w pliku posortowanym:")
#     for number in sorted(count_2.keys()):
#         print(f"{number}: {count_2[number]}")
    
#     if count_1 == count_2:
#         print("\nWszystkie liczby występują tyle samo razy.")
#     else:
#         print("\nLiczby nie zgadzają się!")

def sort_check(file_path):
    with open(file_path, "r") as file:
        numbers = []
        for line in file:
            numbers.append(int(line.strip()))
    
    is_sorted = True
    for i in range(len(numbers) - 1):
        if numbers[i] > numbers[i + 1]:
            is_sorted = False
            break
    
    if is_sorted:
        print("Plik wynikowy jest poprawnie posortowany.")
    else:
        print("Plik wynikowy nie jest posortowany!")


def count_occurrences(file_path):

    counter = 1
    with open(file_path, "r") as file:
        occurrences = {}
        for line in file:   
            if line not in occurrences.keys():
                occurrences[line]=counter
            else:
                occurrences[line] += counter
        return print(occurrences)

def main():
    # begin = timer()
    # generate_data("data.dat", 10, 20) #generuje plik z x(miejsce po nazwie) randomowymi liczbami w zakresie y (ostatnie miejsce w () )
    # end = timer()
    # print(f"Generate time: {end - begin} s")

    # begin = timer()
    # divide_file("data.dat", 4 , "/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/data_file")   #dzieli wygenerowany plik na mniejsze pliki po z (cyfra przed ścieżką) liczb w każdym
    # end = timer()
    # print(f"Divide time: {end - begin} s")

    # begin = timer()
    # sort_data_in_directory("/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/data_file")  #sortuje liczby rosnąco w każdym pliku
    # end = timer()
    # print(f"Sort time: {end - begin} s")

    # ##begin = timer()
    # ##merge_two_file("/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/data_file", "data_1.dat", "data_2.dat", "data_1_2.dat") # laczy pliki ale juz nie trzeba tego uzywac
    # ##end = timer()
    # ##print(f"Merge time: {end - begin} s")

    # begin = timer()
    # merge_all_files("/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/data_file") # generuje posortowany plik z wcześniej utworzonych(podzielonych i posortowanych) i usuwa pozostałe podzielone
    # end = timer()
    # print(f"Merge and delete time: {end - begin} s")


    #Counter_files("/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/data_file/2_1.dat", "/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/data.dat") # sprawdza czy plik ktory generuje liczby ma tyle samo liczb(takich samych) co plik posortowany
    #sort_check("/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/data_file/2_1.dat") # sprawdza czy plik posortowany w data_file jest naprawde posortowany
    count_occurrences("/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/data_file/2_1.dat")

if __name__ == "__main__":
    main()