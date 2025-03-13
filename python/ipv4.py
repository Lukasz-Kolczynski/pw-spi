addr = "78.100.240.0/23"
addr = addr.split('/')

ip = addr[0]
ip = ip.split('.')
ip = (int(ip[0]) << 24) | (int(ip[1]) << 16) | (int(ip[2]) << 8) | int(ip[3])

mask = int(addr[1])
mask = int(mask * "1" + (32 - mask) * "0", 2)

print("IP:", format(ip, '032b'))
print("Maska:", format(mask, '032b'))
first = (ip >> 24)
second = (ip >> 16) & 0xFF
third = (ip >> 8) & 0xFF
last = (ip & 0xFF)
print("IP: ", first, second, third, last)

#n = 2 ^ (32 - b) - 2, ilośc dostepnych hostów

net_ip = mask & ip
not_maSK = ~mask
brode_cast = ip | (not_maSK &  0xFFFFFFFF)
host_1 = net_ip +1
last_host = brode_cast -1
print("First ip addr")
print(format(host_1,'032b'))
print("----------")
print("Last ip addr")
print(format(last_host,'032b'))