import subprocess
import unittest

message = "WF"
key_public = "0101-19bb"
key_private = "9d5b-19bb"
expected_output = "8f84"  

message2 = "The night is dark and full of terrors"
key_private2 = "81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"
ciphered = "445b349e7318ad6af16b0bbb718be88ba1c41751f95751cd58857f88fe31f970405c6ec3f16d79172543bf4e571b5596d212f3e79cd08ef14abd244e325b80"

class TestXor(unittest.TestCase):
    def test_rsa_cipher(self):
        result = subprocess.run(
            f"echo {message} | ./my_pgp rsa -c {key_public}", 
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), expected_output)
    def test_rsa_decipher(self):
        result = subprocess.run(
            f"echo {expected_output} | ./my_pgp rsa -d {key_private}" ,
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), message)
    def test_rsa_cipher2(self):
        result = subprocess.run(
            f"echo {message2} | ./my_pgp rsa -c 010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3",
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(),ciphered)
    def test_rsa_decipher2(self):
        result = subprocess.run(
            f"echo {ciphered} | ./my_pgp rsa -d {key_private2}" ,
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), message2)
    def test_rsa_key_gen_prime1(self):
        result = subprocess.run(
            f"./my_pgp rsa -g d3 e3",
            shell=True,
            capture_output=True,
            text=True
        )
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), "public key: 0101-19bb\nprivate key: 9d5b-19bb")
    def test_rsa_key_gen_prime2(self):
        p = "4b1da73924978f2e9c1f04170e46820d648edbee12ccf4d4462af89b080c86e1"
        q = "bb3ca1e126f7c8751bd81bc8daa226494efb3d128f72ed9f6cacbe96e14166cb"
        result = subprocess.run(
            f"./my_pgp rsa -g {p} {q}",
            shell=True,
            capture_output=True,
            text=True
        )
        p_r = "010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"
        q_r = "81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"
        self.assertEqual(result.returncode, 0)
        self.assertEqual(result.stdout.strip(), f"public key: {p_r}\nprivate key: {q_r}")

if __name__ == "__main__":
    unittest.main()
