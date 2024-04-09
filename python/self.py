class Node:
    __init__(self,data):
    self.data = data  #Przechowywanie danych elementu
    self.next = None #Wskaźnik na następny element, początkowe None

class SinglyLinkedList:
    def __init__(self):
        self.head = None #Głowa listy, początkowo None

    def append(self,data):
        #Dodawanie elementu na koniec listy
        if not self.head:
            self.head = Node(data) #Jeśli lista jest pusta, nowy element staje sie
            return
        last = self.head
        while last.next:
            last = last.next #Przechodzenie do ostatniego elementu
        last.next = Node(data) #Tworzenie nowego elementu na koncu
        