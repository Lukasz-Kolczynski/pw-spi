import hashlib
import os

def hash_p(password, algorithm='sha256'):
    if algorithm not in hashlib.algorithms_available:
        raise ValueError ("Wrong algorithm")
    

    hasher = hashlib.new(algorithm)
    salt = os.urandom(16)
    hasher.update(salt+password.encode('utf-8'))
    return hasher.hexdigest()

def main():
    try:

        password = input ("Podaj hasło: ")
        algorithm = input ("Hash type (Default -sha256-):  ").lower() or 'sha256'
        hashed_p = hash_p(password, algorithm)
        print(f"Hashed password ({algorithm}): {hashed_p}")
    except Exception as e:
        print(f"Wystąpił błąd: {e}")
main()