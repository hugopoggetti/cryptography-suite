from ..parser import parser

# Encryption and Decryption module
from ..xor import xor_c_d

def encryption_decryption(args):
    message = None
    mode = True
    if args.mode == parser.mode.decrypt:
        mode = False
    if args.system == parser.system.xor:
        message = xor_c_d.xor_cipher(args.message, args.key, mode, args.block_mode)
    elif args.system == parser.system.aes:
        message = "aes cipher"
    print(f"{message}")
