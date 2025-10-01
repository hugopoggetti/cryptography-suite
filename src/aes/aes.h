/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#ifndef _AES_
    #define _AES_

    #include <stdlib.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <strings.h>

    #define BLOCK_SIZE 16

// Aes function definition for encryption/decryption
const char *aes_c_d
(const char *message, const char *key, bool encrypt, bool block_mode);
const char *aes_encrypt
(const char *message, const char *key, bool block_mode);
const char *aes_decrypt
(const char *message, const char *key, bool block_mode);

// Aes key expansion
const char **key_expansion(const char *key);
unsigned char sub_byte(unsigned char val);
unsigned char rcon(int round);
void xor_rcon(char *word, int round);
void sub_word(char *word);
void byte_to_hex_pair(unsigned char val, char *dest);
void rot_word(char *word);
char *xor_words(char *new, char *a, char *b);
unsigned char hex_pair_to_byte(char high, char low);
unsigned char hex_char_to_val(char c);

// Padding
const char *padd_message(const char *message, bool block_mode, size_t *size);

// Other
int get_aes_rounds_nb(const char *key);
void free_list(char **list);

#endif
