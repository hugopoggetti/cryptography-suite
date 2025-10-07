import ctypes
import sys

def init_cipher_lib():
    try:
        lib = ctypes.CDLL("./lib/libcipher.so")
    except OSError:
            sys.exit(84)
    lib.aes_c_d.argtypes = (ctypes.c_char_p, ctypes.c_char_p, ctypes.c_bool, ctypes.c_bool)
    lib.aes_c_d.restype = ctypes.c_char_p
    return lib

def aes_c_d(message: str, key: str, b_mode: bool , encrypt: bool):
        lib_cipher = init_cipher_lib()
        message = lib_cipher.aes_c_d(
                message.encode("utf-8"),
                key.encode("utf-8"),
                encrypt,
                b_mode)
        return message
