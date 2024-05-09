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



# class Node:
#     def __init__(self, key):
#         self.key = key
#         self.left = None
#         self.right = None


# def height(node):
#     if node is None:
#         return 0
#     else:
#         return max(height(node.left), height(node.right)) + 1


# def is_balanced(node):
#     if node is None:
#         return True

#     left_height = height(node.left)
#     right_height = height(node.right)

#     if abs(left_height - right_height) <= 1 and is_balanced(node.left) and is_balanced(node.right):
#         return True
#     return False


# root = Node(10)
# root.left = Node(5)
# root.right = Node(20)
# root.left.left = Node(3)
# root.right.left = Node(15)
# root.right.right = Node(30)

#  # Tworzenie drzewa:
#  #      10
#  #     / \
#  #    5   20
#  #   /    / \
#  #  3   15   30

# print("Is balanced?", is_balanced(root))


#--------------------------------------------------



import matplotlib.pyplot as plt
import networkx as nx

class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

def insert(root, key):
    if root is None:
        return Node(key)
    else:
        if key < root.key:
            root.left = insert(root.left, key)
        else:
            root.right = insert(root.right, key)
    return root

def plot_tree(root):
    G = nx.DiGraph()
    node_labels = {}

    def build_graph(node):
        if node:
            node_labels[node.key] = str(node.key)
            if node.left:
                G.add_edge(node.key, node.left.key)
                build_graph(node.left)
            if node.right:
                G.add_edge(node.key, node.right.key)
                build_graph(node.right)

    build_graph(root)
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, labels=node_labels, node_size=1000, node_color="skyblue", font_size=16, font_weight="bold")
    plt.show()

def main():
    root = None
    while True:
        print("Aktualne drzewo:")
        if root:
            plot_tree(root)
        else:
            print("Drzewo jest puste.")

        choice = input("Podaj liczbę do wstawienia (lub 'q' aby zakończyć): ")
        if choice == 'q':
            break
        try:
            key = int(choice)
            root = insert(root, key)
        except ValueError:
            print("Nieprawidłowe dane. Podaj liczbę lub 'q'.")

if __name__ == "__main__":
    main()
