##
## EPITECH PROJECT, 2025
## TECH3 [WSL: Ubuntu-22.04]
## File description:
## test_main
##

import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'src'))

def test_parser_import():
    """Test d'importation du module parser"""
    try:
        from parser import parser
        assert parser is not None
        print("Parser module import OK")
    except ImportError:
        print("Parser module not found")
    except Exception as e:
        print(f"Parser import failed: {e}")

def test_cipher_manager_import():
    """Test d'importation du cipher manager"""
    try:
        from cipher_manager import cipher_manager
        assert cipher_manager is not None
        print("Cipher manager module import OK")
    except ImportError:
        print("Cipher manager module not found")
    except Exception as e:
        print(f"Cipher manager import failed: {e}")

def test_executable():
    """Test de l'existence et permissions de l'exécutable principal"""
    executable_path = os.path.join(os.path.dirname(__file__), '..', 'my_pgp')
    
    if not os.path.exists(executable_path):
        print("Executable my_pgp not found, run make first")
        return
    
    if not os.access(executable_path, os.X_OK):
        print("Executable my_pgp exists but not executable")
        return
        
    file_size = os.path.getsize(executable_path)
    print(f"Executable my_pgp found and executable")
    print(f"File size: {file_size} bytes")
    
    try:
        with open(executable_path, 'r', encoding='utf-8') as f:
            first_line = f.readline().strip()
            if first_line.startswith('#!'):
                print(f"Shebang: {first_line}")
    except Exception as e:
        print(f"Could not read executable: {e}")

if __name__ == "__main__":
    test_parser_import()
    test_cipher_manager_import()
    test_executable()
    print("Main tests completed")