# class Node:
#    def __init__(self,data) -> None:
#     self.data = data  #Przechowywanie danych elementu
#     self.next = None #Wskaźnik na następny element, początkowe None
#     self.prev = None


# class SinglyLinkedList:
#     def __init__(self):
#         self.head = None #Głowa listy, początkowo None

#     def append(self,data):
#         #Dodawanie elementu na koniec listy
#         if not self.head:
#             self.head = Node(data) #Jeśli lista jest pusta, nowy element staje sie
#             return
#         last = self.head
#         while last.next:
#             last = last.next #Przechodzenie do ostatniego elementu

#         new = Node(data)
#         last.next = new #Tworzenie nowego elementu na koncu
#         new.prev = last


#     def display_all(self):
#         current = self.head
#         while current:
#             print(current.data, " ")
#             current = current.next


#     def display_all_(self,data):
#         current= self.head
#         while current:
#             next_value = current.next.data if current.next else "None"
#             print(f"Value: {current.data} , Next {current.next}")
#             return
#         current = current.next
#         #Wyswietlenie wszystkich wartosci wraz z nastepna wartoscia
#         return 0
    

# lista = SinglyLinkedList()
# lista.append(1)
# lista.append(2)
# lista.append(3)

# lista.display_all()

##--------------ZADANIE------------

##Tworzenie kolejki w kinie
# import time 
# import random

# class queueInCinema:
#     def __init__(self):
#         self.queue = []

#     def AddToQueue(self,person):
#         self.queue.append(person)
#         print(f"{person} was has been added to the queue.")

#     def serveQueue(self):
#         if len (self.queue) > 0:
#             print (f"\nServe still i+n progress...")
#             for person in self.queue:
#                 print(f"The person served is: {person}")
#                 time.sleep(random.randint(1,3))
#             print("\nAll person were served.")
#             self.queue = []
#         else:
#             print("Queue is empty.")


# queueCinema = queueInCinema()
# queueCinema.AddToQueue("Bolek Bobek")
# queueCinema.AddToQueue("Balo Halo")
# queueCinema.AddToQueue("Alek Palek")

# queueCinema.serveQueue()






#---------------ZADANIE----------

#Funkcja do obliczania przyszlej wartosci inwestycji z wykorzytaniem procentu składanego.

#   Parametry:
#   p (float): poczatkowa kwota główna/inwestycja.
#   r (float): roczna stopa procentowa w formie dziesiętnej
#   n (int): liczba okresów kapitalizacji rocznie
#   t (float): czas trwania inwestycji w latach

#   Zwraca:
#   float: przyszła wartość inwestycji.

def sum_after(p, r, n, t):

    sum_after = p * (1 + r / n) ** (n * t)
    return sum_after


sum = 20000 
interest_rate = 3.25 
capitalization_periods = 12 
investment_time = 2

investment = sum_after(sum, interest_rate
, capitalization_periods, investment_time)

print("The future value of the investment is: ", investment)
