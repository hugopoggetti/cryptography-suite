from ast import Tuple
import sys
import math
from ..parser import parser

def rsa_c_d(args: parser.parser) -> str:
    if args.mode == parser.mode.generate and args.p and args.q:
        return gen_keys(args.p, args.q)
    elif args.mode == parser.mode.encrypt and args.message and args.key:
        return rsa_encrypt(args.message, args.key)
    elif args.mode == parser.mode.decrypt and args.message and args.key:
        return rsa_decrypt(args.message, args.key)
    else:
        sys.exit(84)

def egcd(a, b):
    if a == 0:
        return b, 0, 1
    gcd, x1, y1 = egcd(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return gcd, x, y

# Extended Euclidean algorithm
# https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
def modInverse(e, lambda_n):
    g, x, _ = egcd(e, lambda_n)
    return x % lambda_n if g == 1 else -1

def lcm(a, b):
    return abs(a * b) // math.gcd(a, b)

def le_to_number(hex_str) -> int:
    hex_str = hex_str.replace(' ', '').replace('\n', '').replace('\\', '')
    
    if len(hex_str) % 2 == 1:
        hex_str = '0' + hex_str
    bytes_list = [hex_str[i:i+2] for i in range(0, len(hex_str), 2)]
    big_endian = ''.join(reversed(bytes_list))
    
    return int(big_endian, 16)

def number_to_le(num):
    hex_str = f"{num:x}"
    if len(hex_str) % 2 == 1:
        hex_str = '0' + hex_str
    bytes_list = [hex_str[i:i+2] for i in range(0, len(hex_str), 2)]
    return ''.join(reversed(bytes_list))

def gen_keys(p_hex: str, q_hex: str) -> str:
    p = le_to_number(p_hex)
    q = le_to_number(q_hex)
    n = p * q
    lambda_n = lcm(p - 1, q - 1)
    fermat_primes = [3, 5, 17, 257, 65537]

    e = 0
    for candidate in reversed(fermat_primes):
        if candidate < lambda_n and math.gcd(candidate, lambda_n) == 1:
            e = candidate
            break

    d = modInverse(e, lambda_n)
    e_le = number_to_le(e)
    n_le = number_to_le(n)
    d_le = number_to_le(d)
    return f"public key: {e_le}-{n_le}\nprivate key: {d_le}-{n_le}"

def concat_hex_from_string(message: str) -> str:
    res = []

    for c in message:
        x = hex(ord(c))
        res.append(x[2:])
    return "0x" + "".join(res)

def split_keys(key: str) -> tuple[int, int]:
    keys = key.split("-")
    a = le_to_number(keys[0])
    b = le_to_number(keys[1])
    return (a, b)

def string_to_le_number(message: str) -> int:
    message_bytes = message.encode('ascii')
    num = int.from_bytes(message_bytes, byteorder='little')
    return num

def le_number_to_string(num: int) -> str:
    num_bytes = (num.bit_length() + 7) // 8
    if num_bytes == 0:
        num_bytes = 1
    message_bytes = num.to_bytes(num_bytes, byteorder='little')
    return message_bytes.decode('ascii')

def rsa_encrypt(message: str, key: str) -> str:
    e, n = split_keys(key)
    m = string_to_le_number(message)
    c = pow(m, e, n)
    return number_to_le(c)

def rsa_decrypt(cipher: str, key: str) -> str:
    d, n = split_keys(key)
    c = le_to_number(cipher)
    m = pow(c, d, n)
    return le_number_to_string(m)
