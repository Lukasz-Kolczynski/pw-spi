class Node:
    def __init__(self, reservation_id, passenger_name, flight_date):
        self.reservation_id = reservation_id
        self.passenger_name = passenger_name
        self.flight_date = flight_date
        self.left = None
        self.right = None

class BinarySearchTree:
    def __init__(self):
        self.root = None

    def add_reservation(self, reservation_id, passenger_name, flight_date):
        if not self.root:
            self.root = Node(reservation_id, passenger_name, flight_date)
        else:
            self._add_reservation(self.root, reservation_id, passenger_name, flight_date)

    def _add_reservation(self, node, reservation_id, passenger_name, flight_date):
        if reservation_id < node.reservation_id:
            if node.left:
                self._add_reservation(node.left, reservation_id, passenger_name, flight_date)
            else:
                node.left = Node(reservation_id, passenger_name, flight_date)
        elif reservation_id > node.reservation_id:
            if node.right:
                self._add_reservation(node.right, reservation_id, passenger_name, flight_date)
            else:
                node.right = Node(reservation_id, passenger_name, flight_date)
        else:
            print("Reservation with ID already exists.")

    def find_reservation(self, reservation_id):
        return self._find_reservation(self.root, reservation_id)

    def _find_reservation(self, node, reservation_id):
        if not node:
            return None
        elif reservation_id == node.reservation_id:
            return node
        elif reservation_id < node.reservation_id:
            return self._find_reservation(node.left, reservation_id)
        else:
            return self._find_reservation(node.right, reservation_id)

    def remove_reservation(self, reservation_id):
        self.root = self._remove_reservation(self.root, reservation_id)

    def _remove_reservation(self, node, reservation_id):
        if not node:
            return node
        if reservation_id < node.reservation_id:
            node.left = self._remove_reservation(node.left, reservation_id)
        elif reservation_id > node.reservation_id:
            node.right = self._remove_reservation(node.right, reservation_id)
        else:
            if not node.left:
                return node.right
            elif not node.right:
                return node.left
            temp = self._find_min(node.right)
            node.reservation_id = temp.reservation_id
            node.passenger_name = temp.passenger_name
            node.flight_date = temp.flight_date
            node.right = self._remove_reservation(node.right, temp.reservation_id)
        return node

    def _find_min(self, node):
        current = node
        while current.left:
            current = current.left
        return current

    def display_all_reservations(self):
        self._display_all_reservations(self.root)

    def _display_all_reservations(self, node):
        if node:
            self._display_all_reservations(node.left)
            print("Reservation ID:", node.reservation_id, ", Passenger:", node.passenger_name, ", Flight Date:", node.flight_date)
            self._display_all_reservations(node.right)

# Przykład użycia:
bst = BinarySearchTree()
bst.add_reservation(1001, "John Doe", "2024-05-20")
bst.add_reservation(1002, "Jane Smith", "2024-05-22")
bst.add_reservation(1003, "Alice Johnson", "2024-05-25")

print("Displaying all reservations:")
bst.display_all_reservations()

print("\nFinding reservation with ID 1002:")
reservation = bst.find_reservation(1002)
if reservation:
    print("Reservation found - ID:", reservation.reservation_id, ", Passenger:", reservation.passenger_name, ", Flight Date:", reservation.flight_date)
else:
    print("Reservation not found.")

print("\nRemoving reservation with ID 1002:")
bst.remove_reservation(1002)

print("\nDisplaying all reservations after removal:")
bst.display_all_reservations()
