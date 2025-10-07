import sys
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

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def modInverse(e, phi):
    for d in range(2, phi):
        if (e * d) % phi == 1:
            return d
    return -1

def gen_keys(p: int, q: int) -> str:
    n = p * q
    phi = (p - 1) * (q - 1)

    e = 0
    for e in range(2, phi):
        if gcd(e, phi) == 1:
            break
    d = modInverse(e, phi)
    return f"public key: {e:x}-{n:x}\nprivate key: {d:x}-{n:x}"

def concat_hex_from_string(message: str) -> str:
    res = []

    for c in message:
        x = hex(ord(c))
        res.append(x[2:])
    return "0x" + "".join(res)

def rsa_encrypt(message: str, key: str): 
    keys = key.split("-")
    e = int(keys[0], 16)
    n = int(keys[1], 16)

    message = message.strip()
    m = int(concat_hex_from_string(message[::-1]), 16)
    c = pow(m, e, n)
    return format(c, 'x')

def rsa_decrypt(cipher: str, key: str) -> str:
    keys = key.split("-")
    d = int(keys[0], 16)
    n = int(keys[1], 16)

    c = int(cipher, 16)
    m = pow(c, d, n)
    hex_str = format(m, 'x')
    if len(hex_str) % 2 != 0:
        hex_str = '0' + hex_str
    message = bytes.fromhex(hex_str).decode('ascii')
    return message[::-1]
