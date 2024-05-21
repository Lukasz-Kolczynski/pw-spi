import hashlib
import os

def hash_p(password):
    sha= hashlib.sha256()
    salt = os.urandom(16)
    sha.update(salt+password.encode('utf-8'))
    return sha.hexdigest()

password = input ("Podaj hasło: ")
hashed_p = hash_p(password)
print (f"Hashed password (sha256): {hashed_p}")