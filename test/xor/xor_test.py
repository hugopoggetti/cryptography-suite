import subprocess
import unittest

message = "You know nothing, Jon Snow"
key = "576861742069732064656164206d6179206e6576657220646965"
expected_output = "20070f2700071c6a4449060a490515164e4e12190b190011063c"  

class TestXor(unittest.TestCase):
    def test_xor_cipher(self):
        result = subprocess.run(
            f"echo {message} | ./my_pgp xor -c -b {key}", 
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), expected_output)
    def test_xor_decipher(self):
        result = subprocess.run(
            f"echo {expected_output} | ./my_pgp xor -d -b {key}" ,
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), message)

if __name__ == "__main__":
    unittest.main()
