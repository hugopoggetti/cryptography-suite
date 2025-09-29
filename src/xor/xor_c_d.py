from typing import List
# https://en.wikipedia.org/wiki/XOR_cipher

def xor_cipher(message: str, key: str, encrypt: bool, block_mode: bool) -> str:
    message = hanlde_padding(message, key, encrypt, block_mode)
    if encrypt:
        return xor_encrypt(message, key)
    else:
        return xor_decrypt(message, key)

def pad_with_zero(message: str, key: str):
    diff = len(key) - len(message)
    message = message + '\0' * diff
    return message

def hanlde_padding(message: str, key: str, encrypt: bool, block_mode: bool) -> str:
    if encrypt and not block_mode:
        if (len(message) * 2) < len(key):
            message = pad_with_zero(message, key)
    elif encrypt:
        if (len(message) * 2) < len(key):
            message = pad_with_zero(message, key)
        elif (len(message) * 2) > len(key):
            message = message[:len(key)]
    return message

def split_hex_string(key:str) -> List[int]:
    split = []

    while key:
        split.append(int(key[:2], 16))
        key = key[2:]
    return split

def xor_encrypt(message: str, key: str) -> str:
    encrypted_data = []
    hex_key = split_hex_string(key)

    for i in range(0, len(message)):
        c =  ord(message[i]) ^ hex_key[i % len(hex_key)]
        encrypted_data.append(f"{c:02x}")
    return "".join(encrypted_data)

def xor_decrypt(message: str, key: str) -> str:
    decrypted_data = []
    hex_key = split_hex_string(key)
    hex_message = split_hex_string(message)

    for i in range(0, len(hex_message)):
        c = hex_message[i] ^ hex_key[i % len(hex_key)]
        decrypted_data.append(chr(c))
    return "".join(decrypted_data)
