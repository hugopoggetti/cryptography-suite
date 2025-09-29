import sys

def display_usage():
    print("USAGE\n"
        "./my_pgp CRYPTO_SYSTEM MODE [OPTIONS] [key]"
        "DESCRIPTION\n"
        "Cipher or decipher MESSAGE using a given CRYPTO_SYSTEM. The MESSAGE is read from the\n"
        "standard input.\n"
        "CRYPTO_SYSTEM\n"
        "\"xor\" computation using XOR algorithm\n"
        "\"aes\" computation using 128-bit AES algorithm\n"
        "\"rsa\" computation using RSA algorithm\n"
        "\"pgp-xor\" computation using both RSA and XOR algorithm\n"
        "\"pgp-aes\" computation using both RSA and 128-bit AES algorithm\n"
        "MODE\n"
        "-c MESSAGE is clear and we want to cipher it\n"
        "-d MESSAGE is ciphered and we want to decipher it\n"
        "-g P Q for RSA only: Don't read a MESSAGE, but instead generate a public and\n"
        "private key pair from the prime number P and Q\n"
        "OPTIONS\n"
        "-b for XOR, AES and PGP, only works on one block. The MESSAGE and the\n"
        "symmetric key must be the same size\n"
        "key Key used to cipher/decipher MESSAGE (incompatible with -g MODE)\n")
    sys.exit(0)
