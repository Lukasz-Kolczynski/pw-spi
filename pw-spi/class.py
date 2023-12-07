class Phonebook:
    FILENAME = 'book.txt'
    def __init__(self, filename='book.txt'):
        self.filename = filename
        self.read_phonebook= self.read_phonebook()
        
    def read_phonebook(self):
        phonebook = {}
        try:
            with open(self.filename, 'r') as file:
                for line in file:
                    name, phone_number = line.strip().split('; ')
                    phonebook[phone_number] = name
        except FileNotFoundError:
            pass
        return phonebook

book1= Phonebook()

