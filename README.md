# my_pgp

## features

### xor 
- [x] encryption/decryption

### aes 
- [x] encryption/decryption
- [x] variable text length
- [x] support 128 bits/192 bits/ 256 bits key

### rsa
- [x] key generation
- [x] encryption/decryption

## TODO
- [ ] explain each algorithm in readme with schema 
- [x] fix results differing with pdf for xor ?
- [x] fix results differing with pdf for aes?
- [x] fix results differing with pdf for pgp?
- [x] unit test and test coding style with ci
- [x] check result when open libcipher.so
- [x] unit tests on parser maybe
- [x] rsa key gen / rsa cipher/decipher
- [x] pgp system

## To Fix
- [ ] Time out on missing arguments
- [ ] rsa key gen with -g 02 03
./my_pgp rsa -c -b 42
- [ ] rsa key gen with -g 00 00  
