class Node:
    def __init__(self,key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1 #Wysokosc wezla inicjalnie ustawiona na 1

def update_height(node):
    #Aktualizacja wysokości wezła na podstawie wysokości jego dzieci

def height(node):
    #Pobranie wysokości wezła, jeśli wezeł nie istnieje zwróć 0

def right_rotate(y):
    #Wykonanie rotacji w prawo na wezle y

    #Przeprowadzenie rotacji

    #Aktualizacja wysokosci po rotacji

    #Nowy korzen po rotacji

#Użycie:
#Załóżmy, ze mamy drzewo AVl i potrzebujemy wykonac rotacje w prawo na wezle 'y'
root= Node(30)
root.left = Node(20)
root.left.left = Node(10)

print(root.key)
#wykonanie rotacji w prawo
root = right_rotate(root)
print(root.key)