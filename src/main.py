# file import change in Makefile to avoid error
from parser import parser
from manager import manager


import sys

def main(argv):
    args = parser.parser(argv)

    if (not args.parse() and not args.get_message()):
        print(f"mode = {args.mode}\nsystem = {args.system}\n"
              f"and key = {args.key}\ndebug mode = {args.block_mode} ")
        print(f"message = {args.message}"
              f"and len of message = {len(args.message)}")
        manager.encryption_decryption(args)
    else:
        sys.exit(84)

if __name__ == "__main__":
   main(sys.argv[1:])
