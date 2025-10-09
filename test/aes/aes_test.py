import subprocess
import unittest

message = "All men must die"
key = "57696e74657220697320636f6d696e67"
expected_output = "744ce22c385958348f0df26eceb62eef"  

class TestXor(unittest.TestCase):
    def test_aes_cipher(self):
        result = subprocess.run(
            f"echo {message} | ./my_pgp aes -c -b {key}", 
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), expected_output)
    def test_aes_decipher(self):
        result = subprocess.run(
            f"echo {expected_output} | ./my_pgp aes -d -b {key}" ,
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), message)

if __name__ == "__main__":
    unittest.main()
