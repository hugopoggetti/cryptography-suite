from ..parser import parser

# Encryption and Decryption module
from ..xor import xor_c_d
from ..aes import aes_c_d

def encryption_decryption(args):
    message = None
    mode = True

    if args.mode == parser.mode.decrypt:
        mode = False

    if args.system == parser.system.xor:
        message = xor_c_d.xor_cipher(args.message, args.key, mode, args.block_mode)
    elif args.system == parser.system.aes:
        message = aes_c_d.aes_c_d(args.message, args.key, args.block_mode, mode)
        message = message.decode()
    elif args.system == parser.system.rsa:
        message = "test"
    print(f"{message}")
