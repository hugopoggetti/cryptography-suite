![Build](https://img.shields.io/badge/build-passing-brightgreen)
![Language](https://img.shields.io/badge/language-C%20%7C%20Rust%20%7C%20Python-blue)

# Cryptography Suite

A modular encryption system implementing classical cryptographic algorithms and their hybrid combination following the PGP model.

## Description

This cryptography suite provides command-line tools for encrypting and decrypting messages using various cryptographic algorithms.\
The project supports symmetric algorithms (XOR, AES), asymmetric algorithms (RSA),
and their hybrid combination inspired by the PGP (Pretty Good Privacy) protocol. \
The AES implementation is written in C and designed to be reusable.

## Implemented Algorithms

### XOR (eXclusive OR)

[XOR cipher](https://en.wikipedia.org/wiki/XOR_cipher) is a basic symmetric encryption method that performs a bitwise exclusive OR operation between the message and the key. While simple, it provides a fundamental basis for understanding encryption principles.

**Characteristics:**
- Symmetric encryption (same key for encryption and decryption)
- Reversible operation: `M XOR K XOR K = M`
- Fast but insecure if the key is reused
- Requires a key of the same length as the message (in block mode)

### AES (Advanced Encryption Standard)

[AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) is a symmetric block cipher algorithm standardized by NIST.
This implementation uses AES (128/192/256-bits key) and is written in C as a reusable library.

**Characteristics:**
- Symmetric block cipher with 128, 192 or 256 bits blocks
- Considered secure by current standards
- Uses complex substitution and permutation operations
- Slower than XOR but significantly more secure
- Implementation in C for performance and portability
- Rust implementation also available

### RSA (Rivest-Shamir-Adleman)

[RSA](https://en.wikipedia.org/wiki/RSA_(cryptosystem)) is an asymmetric encryption algorithm based on the difficulty 
of factoring large prime numbers. It uses a key pair: public key for encryption, private key for decryption.

**Characteristics:**
- Asymmetric encryption (public/private key pair)
- Based on modular arithmetic
- Key generation from two prime numbers P and Q
- Enables secure key exchange

### PGP (Pretty Good Privacy)

[PGP](https://en.wikipedia.org/wiki/Pretty_Good_Privacy) mode combines the advantages of symmetric algorithms (speed) 
and asymmetric algorithms (secure key exchange). \
Two variants are available:

**PGP-XOR:** Combines RSA for key exchange and XOR for message encryption.

**PGP-AES:** Combines RSA for key exchange and AES for message encryption (more secure).

**How it works:**
1. Generate a random symmetric key
2. Encrypt the message with the symmetric key (XOR or AES)
3. Encrypt the symmetric key with RSA (public key)
4. Transmit both the encrypted message and encrypted key

To decrypt:
1. Decrypt the symmetric key with RSA (private key)
2. Decrypt the message with the recovered symmetric key

## Tools

### my_pgp - Main Encryption Tool

#### Syntax

```bash
./my_pgp CRYPTO_SYSTEM MODE [OPTIONS] [key]
```

The message to encrypt or decrypt is read from standard input.

#### Crypto Systems

- `xor` - XOR algorithm encryption
- `aes` - AES encryption
- `rsa` - RSA encryption
- `pgp-xor` - Hybrid RSA + XOR encryption
- `pgp-aes` - Hybrid RSA + AES encryption

#### Modes

- `-c` - Cipher mode: clear message will be encrypted
- `-d` - Decipher mode: encrypted message will be decrypted
- `-g P Q` - Generate mode (RSA only): generates a public/private key pair from prime numbers P and Q

#### Options

- `-b` - Single block mode: processes only one block (XOR, AES and PGP only). Message and key must be the same size.

#### Parameters

- `key` - Key used to cipher/decipher message (incompatible with `-g` mode)

#### Examples

**Generate RSA keys:**
```bash
./my_pgp rsa -g 61 53
```

**XOR encryption:**
```bash
echo "Secret message" | ./my_pgp xor -c "secret_key"
```

**AES encryption:**
```bash
echo "Confidential data" | ./my_pgp aes -c "1234567890123456"
```

**PGP-AES encryption:**
```bash
echo "Top secret message" | ./my_pgp pgp-aes -c "rsa_public_key"
```

**Single block mode:**
```bash
echo "0123456789ABCDEF" | ./my_pgp aes -c -b "fedcba9876543210"
```

### random_keygen - Key Generation Utility

A dedicated tool for generating cryptographic keys and prime numbers.

#### Syntax

```bash
./random_keygen [OPTIONS]
```

#### Options

- `-k [size]` - Generate a hexadecimal key with specified bit size
- `-g [size]` - Generate two prime numbers of specified bit size

#### Examples

**Generate a 128-bit hexadecimal key:**
```bash
./random_keygen -k 128
```

**Generate two prime numbers for RSA (1024-bit):**
```bash
./random_keygen -g 1024
```

## Technical Implementation

### Languages

- **C**: Core implementation of AES algorithm and main encryption system for performance and portability
- **Python**: Command-line parser and implementations of XOR and AES algorithms
- **Rust**: Key generation available in the bonus section

### Reusable Components

The AES implementation in C is designed as a reusable library that can be integrated into other projects. \
The library provides a clean API for:
- Key expansion
- Block encryption/decryption
- Support for different modes of operation

## Resources

For more information about the implemented algorithms:
- [XOR Cipher - Wikipedia](https://en.wikipedia.org/wiki/XOR_cipher)
- [Advanced Encryption Standard - Wikipedia](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard)
- [RSA Cryptosystem - Wikipedia](https://en.wikipedia.org/wiki/RSA_(cryptosystem))
- [Pretty Good Privacy - Wikipedia](https://en.wikipedia.org/wiki/Pretty_Good_Privacy)
