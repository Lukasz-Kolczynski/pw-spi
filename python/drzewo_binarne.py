# class Node:
#     def __init__(self, key):
#         self.key = key
#         self.left = None
#         self.right = None
# def height(node):
#     if node is None:
#         return -1
#     else:
#         left_height = height(node.left)
#         right_height = height(node.right)

#         return max(left_height, right_height) + 1
# # Tworzenie drzewa:
# #      10
# #     / \
# #    5   20
# #   /    / \
# #  3   15   30
# root = Node(10)
# root.left = Node(5)
# root.right = Node(20)
# root.left.left = Node(3)
# root.right.right = Node(15)
# root.right.right = Node(30)
# print("Wysokość drzewa:", height(root))


#----------------------------------------------



class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None


def height(node):
    if node is None:
        return 0
    else:
        return max(height(node.left), height(node.right)) + 1


def is_balanced(node):
    if node is None:
        return True

    left_height = height(node.left)
    right_height = height(node.right)

    if abs(left_height - right_height) <= 1 and is_balanced(node.left) and is_balanced(node.right):
        return True
    return False

True = 'Yes'

root = Node(10)
root.left = Node(5)
root.right = Node(20)
root.left.left = Node(3)
root.right.left = Node(15)
root.right.right = Node(30)

 # Tworzenie drzewa:
 #      10
 #     / \
 #    5   20
 #   /    / \
 #  3   15   30

print("Is balanced?", is_balanced(root))

