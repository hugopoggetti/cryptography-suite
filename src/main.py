# file import change in Makefile to avoid error
from parser import parser
from cipher_manager import cipher_manager


import sys

def main(argv):
    args = parser.parser(argv)

    if (not args.parse() and not args.get_message()):
        # print(f"mode = {args.mode}\nsystem = {args.system}\n"
        #       f"and key = {args.key}\ndebug mode = {args.block_mode} ")
        # print(f"message = {args.message}"
        #       f"\nand len of message = {len(args.message)}")
        cipher_manager.encryption_decryption(args)
    else:
        sys.exit(84)

if __name__ == "__main__":
   main(sys.argv[1:])
