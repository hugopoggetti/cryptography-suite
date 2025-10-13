import subprocess
import unittest

class TestArgs(unittest.TestCase):
    def test_no_args(self):
        result = subprocess.run(
            ["./my_pgp"],
            capture_output=True,
        )
        self.assertEqual(result.returncode, 84)
    def test_invalid_args1(self):
        result = subprocess.run(
            ["./my_pgp", "invalid"],
            capture_output=True,
        )
        self.assertEqual(result.returncode, 84)
    def test_invalid_args2(self):
        result = subprocess.run(
            ["./my_pgp", "-f"],
            capture_output=True,
        )
        self.assertEqual(result.returncode, 84)
    def test_missing_arg_key(self):
        result = subprocess.run(
            ["./my_pgp", "xor", "-b", "-c"],
            capture_output=True,
        )
        self.assertEqual(result.returncode, 84)
    def test_missing_arg_system(self):
        result = subprocess.run(
            ["./my_pgp","-b", "-c", "5657"],
            capture_output=True,
        )
        self.assertEqual(result.returncode, 84)
    def test_missing_arg_mode(self):
        result = subprocess.run(
            ["./my_pgp", "xor", "-b","5657"],
            capture_output=True,
        )
        self.assertEqual(result.returncode, 84)
    def test_bad_arg_system(self):
        result = subprocess.run(
            ["./my_pgp", "sha", "-b", "-c", "5657"],
            capture_output=True,
        )
        self.assertEqual(result.returncode, 84)
    def test_valid_args_xor(self):
        result = subprocess.run(
            "echo test | ./my_pgp xor -c 5657",
            shell=True,
            capture_output=True,
        )
        self.assertEqual(result.returncode, 0)
    def test_valid_args_aes(self):
        result = subprocess.run(
            "echo All men must die | ./my_pgp aes -c -b 57696e74657220697320636f6d696e67",
            shell=True,
            capture_output=True,
        )
        self.assertEqual(result.returncode, 0)
    def test_valid_args_rsa_gen(self):
        result = subprocess.run(
            "./my_pgp rsa -g  d3 e3",
            shell=True,
            capture_output=True,
        )
        self.assertEqual(result.returncode, 0)
    def test_invalid_args(self):
        result = subprocess.run(
            "echo test | ./my_pgp xor -b -c 5657",
            shell=True,
            capture_output=True,
        )
        self.assertEqual(result.returncode, 84)
    def test_invalid_args2(self):
        result = subprocess.run(
            "./my_pgp rsa -g -b d3 e3",
            shell=True,
            capture_output=True,
        )
        self.assertEqual(result.returncode, 84)

if __name__ == "__main__":
    unittest.main()
