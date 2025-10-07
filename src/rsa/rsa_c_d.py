from ast import Tuple
import sys
import math
from ..parser import parser

def rsa_c_d(args: parser.parser) -> str:
    if args.mode == parser.mode.generate and args.p and args.q:
        return gen_keys(int(args.p, 16), int(args.q, 16))
    elif args.mode == parser.mode.encrypt and args.message and args.key:
        return rsa_encrypt(args.message, args.key)
    elif args.mode == parser.mode.decrypt and args.message and args.key:
        return rsa_decrypt(args.message, args.key)
    else:
        sys.exit(84)

def egcd(a, b):
    if b == 0:
        return a, 1, 0
    g, x, y = egcd(b, a % b)
    return g, y, x - (a // b) * y

# Extended Euclidean algorithm
# https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
def modInverse(e, phi):
    g, x, _ = egcd(e, phi)
    return x % phi if g == 1 else -1

def gen_keys(p: int, q: int) -> str:
    n = p * q
    phi = (p - 1) * (q - 1)
    e = 0x10001 # most commonly chosen

    if math.gcd(e, phi) != 1:
        for e in range(3, phi, 2):
            if math.gcd(e, phi) == 1:
                break
    d = modInverse(e, phi)
    return f"public key: {e:x}-{n:x}\nprivate key: {d:x}-{n:x}"

def concat_hex_from_string(message: str) -> str:
    res = []

    for c in message:
        x = hex(ord(c))
        res.append(x[2:])
    return "0x" + "".join(res)

def split_keys(key: str) -> tuple[int, int]:
    keys = key.split("-")
    a = int(keys[0], 16)
    b = int(keys[1], 16)
    return (a, b)

def rsa_encrypt(message: str, key: str): 
    e, n = split_keys(key)
    m = int(concat_hex_from_string(message[::-1]), 16)
    c = pow(m, e, n)
    return format(c, 'x')

def rsa_decrypt(cipher: str, key: str) -> str:
    d, n = split_keys(key)
    c = int(cipher, 16)
    m = pow(c, d, n)
    hex_str = format(m, 'x')

    if len(hex_str) % 2 != 0:
        hex_str = '0' + hex_str
    message = bytes.fromhex(hex_str).decode('ascii')
    return message[::-1]
