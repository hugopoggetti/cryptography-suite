# file import change in Makefile to avoid error
from parser import parser


import sys

def main(argv):
    arg = parser.parser(argv)

    if arg.parse() == 0:
        print("no error")
    else:
        return 84

if __name__ == "__main__":
   main(sys.argv[1:])
