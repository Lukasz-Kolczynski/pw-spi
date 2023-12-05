FILENAME = 'book.txt'

def read_phonebook():
    phonebook = {}
    try:
        with open(FILENAME, 'r') as file:
            for line in file:
                name, phone_number = line.strip().split('; ')
                phonebook[phone_number] = name
    except FileNotFoundError:
        pass
    return phonebook

def save_phonebook(phonebook):
    with open(FILENAME, 'w') as file:
        for phone_number, name in phonebook.items():
            file.write(f"{name}; {phone_number}\n")
    print("Phonebook saved.")

def display_phonebook():
    phonebook = read_phonebook()
    for phone_number, name in phonebook.items():
        print(f"{name}: {phone_number}")

def validate_number(phone_number):
    return len(phone_number) == 9 and phone_number.isdigit()

def add_entry(name, phone_number):
    if not validate_number(phone_number):
        print("Invalid phone number.")
        return
    phonebook = read_phonebook()
    if phone_number in phonebook:
        print("Phone number already exists.")
        return
    phonebook[phone_number] = name
    save_phonebook(phonebook)
    print("Phone number added.")

def remove_entry(phone_number):
    phonebook = read_phonebook()
    if phone_number in phonebook:
        del phonebook[phone_number]
        save_phonebook(phonebook)
        print("Phone number removed.")
    else:
        print("Phone number not found.")

def modify_entry(old_phone_number, new_name, new_phone_number):
    phonebook = read_phonebook()
    if old_phone_number not in phonebook:
        print("Old phone number not found.")
        return False
    if not validate_number(new_phone_number):
        print("Invalid new phone number.")
        return False
    del phonebook[old_phone_number]
    phonebook[new_phone_number] = new_name
    save_phonebook(phonebook)
    print("Phonebook entry modified.")
    return True

# Testowanie funkcji
read_phonebook()
add_entry("Krzysztof", "123456789")
display_phonebook()
modify_entry("123456789", "Ania", "000000000")
remove_entry("123456789")
display_phonebook()