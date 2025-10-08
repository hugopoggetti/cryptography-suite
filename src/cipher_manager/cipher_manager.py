from ..parser import parser

# Encryption and Decryption module
from ..pgp import pgp_system
from ..xor import xor_c_d
from ..aes import aes_c_d
from ..rsa import rsa_c_d

def encryption_decryption(args) -> None:
    message = None
    mode = True

    if args.mode == parser.mode.decrypt:
        mode = False
    if args.system == parser.system.xor:
        message = xor_c_d.xor_cipher(args.message[::-1], args.key, mode, args.block_mode)
    elif args.system == parser.system.aes:
        message = aes_c_d.aes_c_d(args.message, args.key, args.block_mode, mode)
        message = message.decode()
    elif args.system == parser.system.rsa:
        message = rsa_c_d.rsa_c_d(args)
    elif (args.system == parser.system.pgpaes 
          or args.system == parser.system.pgpxor):
        message = pgp_system.pgp_system(args)
    print(f"{message}")
