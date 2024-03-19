def sortowanie_przez_zliczanie(arr):
    max_value= max(arr)
    counts = [0] * (max_value + 1)
    for num in arr:
        counts[num] +=1
        
    sorted_arr = []
    for i in range (len(counts)):
        sorted_arr.extend(([i] * counts[i]))

    return sorted_arr


arr = [4,2,2,8,3,1]
sorted_arr = sortowanie_przez_zliczanie(arr)
print("Posortowa lista: ", sorted_arr)
