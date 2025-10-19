import ctypes
import sys
import struct

def init_cipher_lib():
    try:
        lib = ctypes.CDLL("./lib/libaes.so")
    except OSError:
            sys.exit(84)
    lib.aes_c_d.argtypes = (ctypes.c_char_p, ctypes.c_char_p, ctypes.c_bool, ctypes.c_bool)
    lib.aes_c_d.restype = ctypes.c_char_p
    return lib

def to_little_endian(hex_string):
    data = bytes.fromhex(hex_string)
    result = b""
    for i in range(0, len(data), 4):
        word = struct.unpack('>I', data[i:i+4])[0]
        result += struct.pack('<I', word)
    return result.hex()

# swap little endian to big indian
def swap_endian(hex_string):
    result = ""
    for i in range(0, len(hex_string), 8):
        block = hex_string[i:i+8]
        reversed_block = ''.join([block[j:j+2] for j in range(0, 8, 2)][::-1])
        result += reversed_block
    return result

def aes_c_d(message: str, key: str, b_mode: bool , encrypt: bool) -> str:
        key = to_little_endian(key)
        lib_cipher = init_cipher_lib()
        
        if not encrypt:
            message = swap_endian(message)
        message = lib_cipher.aes_c_d(
                message.encode("utf-8"),
                key.encode("utf-8"),
                encrypt,
                b_mode)
        message = message.decode()
        if encrypt:
            message = to_little_endian(message)
        return message
