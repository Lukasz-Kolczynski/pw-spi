# def sum_number(digits:str) -> int:
#     total = 0
#     for digit in digits:
#         total += int(digit)
#     return total

# number = input ('Enter a number: ')
# if number.isdigit():
#     result = sum_number(number)
#     print(f"suma cyfr liczby {number} wynosi: {result}")
# else:
#     print("Please enter only digits.")



def check_float(tekst):
    try:
        float(tekst)
        return True
    except ValueError:
        return False


def calculate_bmi(weight, height):
    try:
        bmi= weight / (height ** 2)
        return bmi
    except ZeroDivisionError:
        return "Wzrost musi byc wiekszy od 0"
    except TypeError:
        return "Waga i wzrost muszą byc liczbami"
    except ValueError:
        return "Waga i wzrost muszą byc liczbami"

weight = float(input("Enter your weight (in kilograms): "))
height = float(input("Enter your height (in meters): "))
check_float(weight, height)
bmi = calculate_bmi(weight, height)
if bmi < 18.5:
    print("Niedowaga")
elif 18.5 <= bmi < 24.9:
    print("Prawidłowa waga")
elif 25 <= bmi < 29.9: 
    print("Otyłość")



print(f"Your BMI is {bmi}")