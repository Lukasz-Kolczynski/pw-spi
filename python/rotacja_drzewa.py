class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1  # Wysokość węzła początkowo ustawiona na 1

def update_height(node):
    # Aktualizacja wysokości węzła na podstawie wysokości jego dzieci
    if node is None:
        return 0
    return max(height(node.left), height(node.right)) + 1

def height(node):
    # Pobranie wysokości węzła, jeśli węzeł nie istnieje, zwróć 0
    if node is None:
        return 0
    return node.height

def right_rotate(y):
    # Wykonanie rotacji w prawo na węźle y
    x = y.left
    T2 = x.right

    # Wykonanie rotacji
    x.right = y
    y.left = T2

    # Aktualizacja wysokości po rotacji
    y.height = update_height(y)
    x.height = update_height(x)

    # Nowy korzeń po rotacji
    return x

def left_rotate(x):
    # Wykonanie rotacji w lewo na węźle x
    y = x.right
    T2 = y.left

    # Wykonanie rotacji
    y.left = x
    x.right = T2

    # Aktualizacja wysokości po rotacji
    x.height = update_height(x)
    y.height = update_height(y)

    # Nowy korzeń po rotacji
    return y

def right_left_rotate(x):
    if x is None or x.right is None:
        return x  # Nie można wykonać rotacji
    # Wykonanie rotacji w prawo na prawym dziecku
    x.right = right_rotate(x.right)
    # Wykonanie rotacji w lewo na węźle x
    return left_rotate(x)


# Użycie:
# Załóżmy, że mamy drzewo AVL i potrzebujemy wykonać rotację w prawo na węźle 'y'
root = Node(30)
root.left = Node(20)
root.left.left = Node(10)

print("Klucz korzenia przed rotacją:", root.key)
# Wykonanie rotacji w prawo
root = right_rotate(root)
print("Klucz korzenia po rotacji w prawo:", root.key)

# Załóżmy, że mamy drzewo AVL i potrzebujemy wykonać rotację w lewo na węźle 'x'
root = Node(30)
root.right = Node(40)
root.right.right = Node(50)

print("Klucz korzenia przed rotacją:", root.key)
# Wykonanie rotacji w lewo
root = left_rotate(root)
print("Klucz korzenia po rotacji w lewo:", root.key)

# Załóżmy, że mamy drzewo AVL i potrzebujemy wykonać rotację w prawo-lewo na węźle 'x'
root = Node(30)
root.left = Node(20)
root.left.right = Node(25)

print("Klucz korzenia przed rotacją:", root.key)
# Wykonanie rotacji w prawo-lewo
root = right_left_rotate(root)
print("Klucz korzenia po rotacji w prawo-lewo:", root.key)
