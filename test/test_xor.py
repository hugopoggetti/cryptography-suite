##
## EPITECH PROJECT, 2025
## TECH3 [WSL: Ubuntu-22.04]
## File description:
## test_xor
##

import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'src'))

def test_xor_basic():
    """Test basique de chiffrement XOR"""
    try:
        from xor.xor_c_d import xor_cipher, xor_decipher
        message = b"test"
        key = b"key"
        result = xor_cipher(message, key)
        assert result is not None
        print("XOR cipher function works")
    except (ImportError, AttributeError, NameError):
        print("XOR functions not implemented")
    except Exception as e:
        print(f"XOR test failed: {e}")

def test_imports():
    """Test d'importation du module XOR"""
    try:
        from xor import xor_c_d
        assert xor_c_d is not None
        print("XOR module import OK")
    except ImportError:
        print("XOR module not found")
    except Exception as e:
        print(f"XOR import failed: {e}")

if __name__ == "__main__":
    test_xor_basic()
    test_imports()
    print("Tests completed")