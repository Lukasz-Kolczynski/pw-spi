import socket

HOST = '0.0.0.0'
PORT = 12345

users = {}

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((HOST, PORT))

print(f"Serwer działa na {HOST}:{PORT}")

while True:
    data, addr = sock.recvfrom(1024)

    if not data:
        if addr in users:
            print(f"[INFO] {users[addr]} rozłączony")
            del users[addr]
        continue

    prefix = data[:1]

    if prefix == b'\0':
        nickname = data[1:].decode('utf-8', errors='ignore')
        users[addr] = nickname
        print(f"[INFO] Nowy użytkownik {nickname} z {addr}")
    elif prefix == b'\1':
        if addr in users:
            message = data[1:].decode('utf-8', errors='ignore')
            sender = users[addr]
            full_message = f"{sender}: {message}".encode('utf-8')
            print(f"[MSG] {sender}: {message}")

            for user_addr in users:
                if user_addr != addr:
                    sock.sendto(full_message, user_addr)
        else:
            print(f"[IGNORED] Wiadomość od nieznanego adresu: {addr}")
    else:
        print(f"[WARNING] Nieznany prefiks od {addr}")
