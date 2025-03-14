# #klasy abstrakcyjne

# class TextLines:
#     readLine(numer wiersza) wiersz o danym numerze
#     addLine(numer wiersza, line) dodanie wiersza w konkretnej pozycji
#     nie pozwalamy na dodanie wiersza "z przerwą" tzn jak mamy 1,2,3 wiersz to nie mozemy dodac np 57 wiersza
#     gdy wiersze istnieje to zostaje nadpisany
#     deleteLine(numer wiersza)

# class IdentifiedTextLines: TextLines (identyfikatory nie musza byc unikalne; pelnia bardziej role tagow)
#     readLine(identyfikator) wiersz(e) posiadaja zadany identyfikator
#     addLine(identyfikator, line) dodanie wiersza na koncu
#     addLine(identyfikator, line, numer wiersza) dodanie wiersza w konkretnej pozycji
#     deleteLine(identyfikator)

# class UniquelyIdentifiedTextLines
#     container: IdentifiedTextLines
#     addLine(identyfikator, line) dodanie wiersza na koncu
#     addLine(identyfikator, line, numer wiersza) dodanie wiersza w konkretnej pozycji
#     deleteLine(identyfikator)
   
# #klasy realne

# class TextLinesInMemory: TextLines
# class TextLinesInFile: TextLines
# class TextLinesInDB: TextLines

# class IdentifiedTextLinesInMemory: IdentifiedTextLines


# class UniquelyIdentifiedTextLinesInMemory: UniquelyIdentifiedTextLines


# class Foo:
#     attr = "Common"

#     def __init__(self, arg1, arg2):
#         self.attr1 = arg1
#         self.attr2 = arg2

# #składowe klasy
# def main1():
#     f1 = Foo(1, "b")
#     f2 = Foo(2, "a")

#     print(f1.attr2)
#     print(f2.attr2)

#     print(f1.attr)
#     print(f2.attr)
#     print(Foo.attr)

#     Foo.attr = "xxx"

#     print(f1.attr)
#     print(f2.attr)
#     print(Foo.attr)

#     f1.attr = "zzz"

#     print(f1.attr)
#     print(f2.attr)
#     print(Foo.attr)

#     Foo.attr = "aaa"

#     print(f1.attr)
#     print(f2.attr)
#     print(Foo.attr)

# if __name__ == '__main__':
#     main1()


# class Foo:
#     attr = "Common"

#     def __init__(self, arg1, arg2):
#         self.attr = arg1
#         self.attr =arg2 

#     def use_me(self):
#         print("Foo: use_me")

#     def poly(self):
#         print("Foo: poly")

# class Bar(Foo):
#     def something_new(self):
#         print("Bar: something_new")

#     def poly(self):
#         print("Bar: poly")

# class XYZ:
#     def xyz(self):
#         print("XYZ: xyz")

#     def poly(self):
#         print("XYZ: poly")
    
# class Strange(Bar, XYZ):
#     pass

# def main():
#     f = Foo(1, 3)
#     b = Bar(1, 3)
#     xyz = XYZ()
#     s = Strange(1, 3)

#     f.poly()
#     b.poly()
#     xyz.poly()


# if __name__ == '__main__':
#     main()
        


#====================================================

from abc import ABC, abstractmethod

#Abstract method
class TextLines(ABC):
    #Public methods
    @abstractmethod
    def get_number_of_lines(self):
        pass
    @abstractmethod
    def read_line(self, line_number):
        pass
    @abstractmethod
    def write_Line(self, text, line_number = None):
        pass
    @abstractmethod
    def delete_line(self, line_number):
        pass

    # #Private methods
    # @abstractmethod
    # def __write_line_at_index(self, text, line_number):
    #     pass
    #
    # @abstractmethod
    # def __write_line_at_end(text):
    #     pass


class TextLinesInMemory(TextLines):
    # public methods
    def __init__(self):
        self.__lines = []

    def get_number_of_lines(self):
        return len(self.__lines)

    def read_line(self, line_number):
        if line_number < self.get_number_of_lines():
            return self.__lines[line_number]
        else:
            raise IndexError("Line number out of range")
    def delete_line(self, line_number):
        if line_number >= 0 and line_number < self.get_number_of_lines():
            self.__lines[line_number] = None
        else:
            raise IndexError("Line number out of range")
    #BEGIN: Private methods
    def __write_line_at_end(self, text):
        if type(text) is not str:
            raise TypeError("Text must be a string type")
        self.__lines.append(text)
        pass
    def __write_line_at_index(self, text, line_number):

        if type(text) is not str:
            raise TypeError("Text must be a string type")
        elif line_number < self.get_number_of_lines():
            self.__lines[line_number] = None
        else:
            raise TypeError("Line number out of range")
    #Progressive variant
    def __write_line_at_index(self, text, line_number):

        if type(text) is not str:
            raise TypeError("Text must be a string type")
        elif line_number >= 0 and line_number < self.get_number_of_lines():
            self.__lines[line_number] = None
        else:
            for _ in range(line_number - self.get_number_of_lines()):
                self.__write_line_at_end("")
            self.__write_line_at_end(text)

    def write_Line(self, text, line_number=None):
        if line_number == None:
            self.__write_line_at_end(text)
        else:
            self.__write_line_at_index(text, line_number)
        pass
    def dump(self):
        return self.__lines


class IdentifiedTextLines:
    def __init__(self):
        self.__lines = TextLinesInMemory()
        self.__ids = {}
    def write_line(self, text, identifier):
        if identifier not in self.__ids:
            self.__ids[identifier] = []
        self.__lines.write_Line((text))
        line_number = self.__lines.get_number_of_lines() - 1
        self.__ids[identifier].append(line_number)

    # def test(self):
    #     print(self.__ids)
    #     print(self.__lines.__lines)

    def read_line(self, identifier):
        if identifier not in self.__ids:
            raise KeyError("Unknown identifier")
        result = []
        for idx in self.__ids[identifier]:
            line = self.__lines.read_line(idx)
            result.append(line)
        return result
    def delete_line(self, identifier):
        if identifier not in self.__ids:
            raise KeyError("Unknown identifier")
        for idx in self.__ids[identifier]:
            self.__lines.delete_line(idx)
        del self.__ids[identifier]

    def get_identifiers(self):
        return [key for key in self.__ids]

    def dump(self):
        return self.__lines.dump()
    def test(self):
        number_of_lines = self.__lines.get_number_of_lines()
        print(number_of_lines)
def test_IdentifiedTextLines():
    titl = IdentifiedTextLines()
    titl.write_line("foo 1", "f1")
    titl.write_line("bar 1", "b1")
    titl.write_line("foo 2", "f1")
    titl.write_line("bar 2", "b1")
    titl.write_line("foo 3", "f1")

    lines = titl.read_line(("f1"))


    print(titl.r)


def main():
    test_IdentifiedTextLines()
if __name__ == "__main__":
    main()