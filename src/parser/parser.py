import sys, getopt
from enum import Enum
from ..usage import usage 

class system(Enum):
    xor = 1
    aes = 2
    rsa = 3
    pgpxor = 4
    pgpaes = 5

class mode(Enum):
    encrypt = 1
    decrypt = 2
    generate = 3

class parser:
    def __init__(self, arg):
        self.arg = arg
        self.system = None
        self.mode = None
        self.block_mode = False
        self.key = None
        self.p = None
        self.q = None
        self.message = None
 
    def check_errors(self) -> int:
        if self.mode is None or self.system is None:
            return 84
        if self.mode == mode.generate:
            if self.system != system.rsa:
                return 84
            if self.p is None or self.q is None:
                return 84
        elif self.mode != mode.generate:
            if self.key is None:
                return 84
        return 0

    def parse(self):
        if len(self.arg) < 2:
            return 84

        crypto = self.arg[0].lower()
        if crypto == "xor":
            self.system = system.xor
        elif crypto == "aes":
            self.system = system.aes
        elif crypto == "rsa":
            self.system = system.rsa
        elif crypto in ("pgp-xor", "pgpxor"):
            self.system = system.pgpxor
        elif crypto in ("pgp-aes", "pgpaes"):
            self.system = system.pgpaes
        else:
            return 84

        try:
            opts, args = getopt.getopt(
                self.arg[1:],
                "cdgbh",
                ["cipher", "decipher", "generate", "block", "help"]
            )
        except getopt.GetoptError:
            return 84

        for opt, _ in opts:
            if opt in ('-h', '--help'):
                usage.display_usage()
            elif opt in ('-c', '--cipher'):
                self.mode = mode.encrypt
            elif opt in ('-d', '--decipher'):
                self.mode = mode.decrypt
            elif opt in ('-g', '--generate'):
                self.mode = mode.generate
            elif opt in ('-b', '--block'):
                if self.system and self.mode:
                    self.block_mode = True
                else:
                    return 84

        if self.mode == mode.generate:
            if len(args) != 2 or self.block_mode:
                return 84
            try:
                self.p = args[0]
                self.q = args[1]
            except ValueError:
                return 84
        else:
            if len(args) > 0:
                self.key = args[0]
        return self.check_errors()

    # get message from stdin
    def get_message(self) -> int:
        if (self.mode == mode.generate):
            return 0
        self.message = sys.stdin.read()[:-1]
        if not self.message:
            return 84
        return 0
