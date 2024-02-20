class Car:
    #atrybut klasy
    color= "red"
    def __init__(self, make, model, year):
        #atrybuty instancji
        self.make= make
        self.__model= model
        self.year= year
    def set__model(self, new_model):
        self.__model = new_model
    def get_model(self):
        return self.__model

#############################################


car= Car("Toyota", "Camry", 2023)
print(car.color) #odczyt atrybutu klasy
car.color = 'green' #zapis atrybutu klasy
print(car.year) #odczyt atrybutu instancji
car.year=2020 #zapis atrybutu instancji
print(car.year)
car.engine = 'diesel' #atrybut dynamiczny
print(car.engine)

print(car.get_model())