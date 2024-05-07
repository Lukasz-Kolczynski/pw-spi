class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
def height(node):
    if node is None:
        return 0
    else:
        left_height = height(node.left)
        right_height = height(node.right)

        return max(left_height, right_height) + 1
# Tworzenie drzewa:
#      10
#     / \
#    5   20
#   /    / \
#  3   15   30
root = Node(10)
root.left = Node(5)
root.right = Node(20)
root.left.left = Node(3)
root.right.right = Node(15)
root.right.right = Node(30)
print("Wysokość drzewa:", height(root))