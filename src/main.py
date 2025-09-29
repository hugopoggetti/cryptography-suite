# file import change in Makefile to avoid error
from parser import parser


import sys

def main(argv):
    arg = parser.parser(argv)

    if arg.parse() == 0:
        print(f"mode = {arg.mode}\nsystem = {arg.system}\nand key = {arg.key}\ndebug mode = {arg.block_mode} ")
        arg.get_message()
    else:
        sys.exit(84)
    return 0

if __name__ == "__main__":
   main(sys.argv[1:])
