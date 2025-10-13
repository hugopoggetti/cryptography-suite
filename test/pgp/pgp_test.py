import subprocess
import unittest

message = "You know nothing, Jon Snow"
sym_key = "576861742069732064656164206d6179206e6576657220646965"
rsa_public = "0101-19bb"
expected_cipher = "9e18\n20070f2700071c6a4449060a490515164e4e12190b190011063c"

message2 = "All men must die"
symmetric_key = "57696e74657220697320636f6d696e67"
expected_output2 = "cd5d\n744ce22c385958348f0df26eceb62eef"

message3 = "The night is dark and full of terrors"
expected_output3 = "9e18\n241a0e06520c0700020a41084c180759440004560e00410049163e48151c47001d00010d35"

class TestXor(unittest.TestCase):
    def test_pgp_xor_cipher(self):
        result = subprocess.run(
            f"echo {message} | ./my_pgp pgp-xor -c {sym_key}:{rsa_public}",
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), expected_cipher)
        
    def test_pgp_aes_cipher(self):
        result = subprocess.run(
            f"echo {message2} | ./my_pgp pgp-aes -c -b {symmetric_key}:{rsa_public}",
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), expected_output2)
        
    def test_pgp_xor_cipher2(self):
        result = subprocess.run(
            f"echo {message3} | ./my_pgp pgp-xor -c {sym_key}:{rsa_public}",
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), expected_output3)

if __name__ == "__main__":
    unittest.main()