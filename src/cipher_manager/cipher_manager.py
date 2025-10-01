import ctypes
from ..parser import parser

# Encryption and Decryption module
from ..xor import xor_c_d

def init_cipher_lib():
    lib = ctypes.CDLL("./lib/libcipher.so")
    lib.aes_c_d.argtypes = (ctypes.c_char_p, ctypes.c_char_p, ctypes.c_bool, ctypes.c_bool)
    lib.aes_c_d.restype = ctypes.c_char_p
    return lib

def encryption_decryption(args):
    message = None
    mode = True
    if args.mode == parser.mode.decrypt:
        mode = False
    if args.system == parser.system.xor:
        message = xor_c_d.xor_cipher(args.message, args.key, mode, args.block_mode)
    elif args.system == parser.system.aes:
        lib_cipher = init_cipher_lib()
        message = lib_cipher.aes_c_d(
                args.message.encode("utf-8"),
                args.key.encode("utf-8"),
                mode,
                args.block_mode)
        message = message.decode()
    print(f"{message}")
