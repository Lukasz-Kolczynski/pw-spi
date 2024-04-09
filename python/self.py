class Node:
   def __init__(self,data) -> None:
    self.data = data  #Przechowywanie danych elementu
    self.next = None #Wskaźnik na następny element, początkowe None
    self.prev = None


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


    def display_all(self):
        current = self.head
        while current:
            print(current.data, " ")
            current = current.next


    def display_all_(self,data):
        current= self.head
        while current:
            next_value = current.next.data if current.next else "None"
            print(f"Value: {current.data} , Next {current.next}")
            return
        current = current.next
        #Wyswietlenie wszystkich wartosci wraz z nastepna wartoscia
        return 0
    

lista = SinglyLinkedList()
lista.append(1)
lista.append(2)
lista.append(3)

lista.display_all()

