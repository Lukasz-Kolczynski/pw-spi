# [{'id':1, 'value': 5},
#  {'id': 2, 'value':3},
#  {'id': 3, 'value':5},
#  {'id': 4, 'value':8},
#  {'id': 5, 'value':3},]

# zastosowac sortowanie niestabilne - (quicksort)



#sortowanie stabilne (przez scalanie) - mergesort



# def quicksort(arr):
#         if len(arr) <= 1:
#             return arr
#     pivot = arr[len(arr) // 2]['value']
#     left = [x for x in arr if x['value'] < pivot]
#     middle = [x for x in arr if x['value'] == pivot]
#     right = [x for x in arr if x['value'] > pivot]
# return quicksort(left) + middle + quicksort(right)

# def mergesort(arr):
#     if len(arr) <= 1:
#         return arr
# mid = len(arr) // 2
# left = mergesort(arr[:mid])
# right = mergesort(arr[mid:])
# return merge(left, right)

# def merge(left, right):
#     result = []
# i = j = 0
# while i < len(left) and j < len(right):
#     if left[i]['value'] <= right[j]['value']:
#         result.append(left[i])
#         i += 1
#     else:
#         result.append(right[j])
#         j += 1
#         result.extend(left[i:])
#         result.extend(right[j:])
# return result

# data = [{'id': 1, 'value': 5}, {'id': 2, 'value': 3}, {'id': 3, 'value': 5}, {'id': 4, 'value': 8}, {'id': 5, 'value': 3}]
# print("Przed sortowaniem:")
# print(data)

# print("\nPo sortowaniu niestabilnym (quicksort):")
# print(quicksort(data))

# print("\nPo sortowaniu stabilnym (mergesort):")
# print(mergesort(data))




mapa = {
    'A':{'B':2, 'D':4},
    'B':{'C':3, 'D':3},
    'C':{'E':2},
    'D':{'C':3, 'E':4},
    'E':{}
}

def dijkstra(graph, start, goal):

    #ustaw odleglosc na nieskonczonosc
    shortest_distances = {vortex:float ('infinity') for vortex in graph}
    #dla wierzcholka startowego ustaw wartosc 0
    shortest_distances[start] = 0
    predecessors= {}
    #nieodwiedzone wierzcholki
    unvisited= graph.copy()
    #petle nieodwiedzonych
    while unvisited:
        #wybierz wiezrcholek z najmneijsza odlegloscia
        current_min_vortex= None
        for vortex in unvisited:
            if current_min_vortex is None:
                current_min_vortex = vortex
            elif shortest_distances[vortex] < shortest_distances[current_min_vortex]:
                current_min_vortex = vortex
        #sprawdz wszystkich sasiadow aktualnego wierzcholka
        for neighbour, cost in graph[current_min_vortex].items():
            if cost + shortest_distances[current_min_vortex] < shortest_distances[neighbour]:
                shortest_distances[neighbour] = cost + shortest_distances[current_min_vortex]
                predecessors[neighbour] = current_min_vortex
        #usun z listy przetworzony wierzcholek
        unvisited.pop(current_min_vortex)
    #odtworzenie sciezki od startu do celu
    current_vortex = goal
    path=[]
    while current_vortex != start:
        path.append(current_vortex)
        current_vortex = predecessors[current_vortex]
    path.append(start)

    return path[::-1], shortest_distances[goal]

path, distance = dijkstra(mapa, 'A', 'E')
print(f"Najkrótsza ścieżka: {path}, długość: {distance}")