import socket
import select
import sys

SERVER_IP = '127.0.0.1'
SERVER_PORT = 12345

nickname = input("Podaj swój nickname: ")

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setblocking(False)

sock.sendto(b'\0' + nickname.encode('utf-8'), (SERVER_IP, SERVER_PORT))

print("Możesz teraz pisać wiadomości. Wyślij pustą wiadomość, aby się rozłączyć.")

try:
    while True:
        readable, _, _ = select.select([sock, sys.stdin], [], [])

        for r in readable:
            if r == sock:
                data, _ = sock.recvfrom(1024)
                print(data.decode('utf-8'))
            elif r == sys.stdin:
                msg = sys.stdin.readline().strip()
                if msg == "":
                    sock.sendto(b'', (SERVER_IP, SERVER_PORT))
                    print("Rozłączono.")
                    sys.exit(0)
                else:
                    sock.sendto(b'\1' + msg.encode('utf-8'), (SERVER_IP, SERVER_PORT))
except KeyboardInterrupt:
    sock.sendto(b'', (SERVER_IP, SERVER_PORT))
    print("\nZamknięto klienta.")
