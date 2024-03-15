[{'id':1, 'value': 5},
 {'id': 2, 'value':3},
 {'id': 3, 'value':5},
 {'id': 4, 'value':8},
 {'id': 5, 'value':3},]

# zastosowac sortowanie niestabilne - (quicksort)



#sortowanie stabilne (przez scalanie) - mergesort



def quicksort(arr):
        if len(arr) <= 1:
            return arr
pivot = arr[len(arr) // 2]['value']
left = [x for x in arr if x['value'] < pivot]
middle = [x for x in arr if x['value'] == pivot]
right = [x for x in arr if x['value'] > pivot]
return quicksort(left) + middle + quicksort(right)

def mergesort(arr):
    if len(arr) <= 1:
        return arr
mid = len(arr) // 2
left = mergesort(arr[:mid])
right = mergesort(arr[mid:])
return merge(left, right)

def merge(left, right):
    result = []
i = j = 0
while i < len(left) and j < len(right):
    if left[i]['value'] <= right[j]['value']:
        result.append(left[i])
        i += 1
    else:
        result.append(right[j])
        j += 1
        result.extend(left[i:])
        result.extend(right[j:])
return result

data = [{'id': 1, 'value': 5}, {'id': 2, 'value': 3}, {'id': 3, 'value': 5}, {'id': 4, 'value': 8}, {'id': 5, 'value': 3}]
print("Przed sortowaniem:")
print(data)

print("\nPo sortowaniu niestabilnym (quicksort):")
print(quicksort(data))

print("\nPo sortowaniu stabilnym (mergesort):")
print(mergesort(data))
