# tree = [1,2,3,4,5,6,7]

# def get_left_child(index):
#     """Zwraca lewe dziecko węzła o danym indeksie."""
#     return 2 * index + 1

# def get_right_child(index):
#     """Zwraca prawe dziecko węzła o danym indeksie."""
#     return 2 * index + 2

# def get_parent(index):
#     """Zwraca rodzica węzła o danym indeksie."""
#     return (index-1) // 2

# index= 0
# left_child_index = get_left_child(index)
# right_child_index = get_right_child(index)
# parent_index = get_parent(index)
# print(f"Lewe:  {left_child_index}")
# print(f"Prawe:  {right_child_index}")
# print(f"Rodzic:  {parent_index}")



## Przeszukiwanie w głąb (DFS)
# class Node:
#     def __init__(self, value):
#         self.value = value
#         self.left = None
#         self.right = None 

# def dfs_preorder(node):
#     if node:
#         print(node.value)
#         dfs_preorder(node.left)
#         dfs_preorder(node.right)


# root = Node(1)
# root.left = Node(2)
# root.right = Node(3)
# root.left.left = Node(4)
# root.left.right = Node(5)

# print("Przeszukiwanie w głąb(DFS) - Pre-order:")
# dfs_preorder(root)



## Przeszukiwanie wszerz(BFS)

from collections import deque

class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None 
        
def bfs(root):
    if root is None:
        return
     
    queue = deque([root])

    while queue:
        current_node = queue.popleft()
        print(current_node.value)

        if current_node.left is not None:
            queue.append(current_node.left)
        if current_node.right is not None:
            queue.append(current_node.right)

root = Node(1)
root.left = Node(2)
root.right = Node(3)
root.left.left = Node(4)
root.left.right = Node(5)

print("Przeszukiwanie wszerz (BFS):")
bfs(root)

