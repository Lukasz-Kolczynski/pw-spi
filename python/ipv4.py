def bin_dec(ip):

    first = ip >> 24
    second = (ip >> 16) & 0xFF
    third = (ip >> 8) & 0xFF
    last = ip & 0xFF
    result = (str(first), str(second), str(third), str(last))
    return '.'.join(result)


addr = "192.168.4.0/22"
addr = addr.split('/')
mask_len = int(addr[1])
ip = addr[0]
ip = ip.split('.')
ip = (int(ip[0]) << 24) | (int(ip[1]) << 16) | (int(ip[2]) << 8) | int(ip[3])
mask = (2**mask_len - 1) << (32 - mask_len)
net_ip = ip & mask
not_mask = ~mask & 0xFFFFFFFF
broadcast = net_ip | not_mask
host_first = net_ip + 1
host_last = broadcast - 1
print("Adres IP:", bin_dec(ip))
print("Maska:", bin_dec(mask))
print("Adres sieciowy:", bin_dec(net_ip))
print("Adres broadcast:", bin_dec(broadcast))
print("Pierwszy host:", bin_dec(host_first))
print("Ostatni host:", bin_dec(host_last))
hosts_amount = 2**(32 - mask_len) - 2
print("Ilość hostów w sieci:", hosts_amount)