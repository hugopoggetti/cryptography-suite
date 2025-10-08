import sys
from ..parser import parser
from ..xor import xor_c_d
from ..aes import aes_c_d
from ..rsa import rsa_c_d

def pgp_system(args) -> str:
    keys = args.key.split(":")
    data = None
    ciphered_key = None

    if args.mode == parser.mode.encrypt:
        ciphered_key = rsa_c_d.rsa_encrypt(keys[0], keys[1])
        if args.system == parser.system.pgpaes:
            data = aes_c_d.aes_c_d(args.message, keys[0], args.block_mode, True)
            return ciphered_key + "\n" + data
        if args.system == parser.system.pgpxor:
            data = xor_c_d.xor_cipher(args.message, keys[0], True, args.block_mode) 
            return ciphered_key + "\n" + data
    else:
        if args.system == parser.system.pgpaes:
            ciphered_key = rsa_c_d.rsa_decrypt(keys[0], keys[1])
            data = aes_c_d.aes_c_d(args.message, ciphered_key, args.block_mode, False)
            return data
        if args.system == parser.system.pgpxor:
            ciphered_key = rsa_c_d.rsa_decrypt(keys[0], keys[1])
            data = xor_c_d.xor_cipher(args.message, ciphered_key, False, args.block_mode)
            return data
    sys.exit(84)

