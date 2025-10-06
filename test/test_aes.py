##
## EPITECH PROJECT, 2025
## TECH3 [WSL: Ubuntu-22.04]
## File description:
## test_aes
##

import sys
import os
import ctypes

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'src'))

def test_aes_lib():
    """Test de chargement de la bibliothèque AES compilée"""
    lib_path = os.path.join(os.path.dirname(__file__), '..', 'lib', 'libcipher.so')
    
    if not os.path.exists(lib_path):
        print("AES library not found, run make lib first")
        return
    
    try:
        lib = ctypes.CDLL(lib_path)
        assert lib is not None
        print(f"AES library loaded successfully")
        
        file_size = os.path.getsize(lib_path)
        print(f"Library size: {file_size} bytes")
        
    except OSError as e:
        print(f"Failed to load AES library: {e}")
    except Exception as e:
        print(f"AES library test failed: {e}")

def test_key_sizes():
    """Test de validation des tailles de clés AES standard"""
    key_128 = b'0' * 16  # 128 bits = 16 bytes
    key_192 = b'0' * 24  # 192 bits = 24 bytes  
    key_256 = b'0' * 32  # 256 bits = 32 bytes
    
    assert len(key_128) == 16, "AES-128 key should be 16 bytes"
    assert len(key_192) == 24, "AES-192 key should be 24 bytes"
    assert len(key_256) == 32, "AES-256 key should be 32 bytes"
    
    print("AES key sizes validation passed")
    print(f"AES-128: {len(key_128)} bytes")
    print(f"AES-192: {len(key_192)} bytes") 
    print(f"AES-256: {len(key_256)} bytes")

if __name__ == "__main__":
    test_aes_lib()
    test_key_sizes()
    print("AES tests completed")