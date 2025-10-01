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
    #define mul2(x) (((x << 1) ^ (((x >> 7) & 1) * 0x1B)) & 0xFF)
    #define mul3(x) (mul2(x) ^ x)

// Aes function definition for encryption/decryption
const char *aes_c_d
(const char *message, const char *key, bool encrypt, bool block_mode);
const char *aes_encrypt
(const char *message, const char *key, bool block_mode);
const char *aes_decrypt
(const char *message, const char *key, bool block_mode);

// round function
const char *encrypt
(unsigned char ***blocks, const char **keys, int round_nb);
void sub_byte_to_blocks(unsigned char ***blocks);
void shift_rows(unsigned char ***blocks);
void mix_columns(unsigned char ***blocks);
void add_round_key(unsigned char ***blocks, const char *key);

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

// dispatch message to list of 4*4 block
unsigned char ***dispatch_to_blocks(const char *message, size_t mess_size);

// Padding
const char *padd_message(const char *message, bool block_mode, size_t *size);

// Other
int get_aes_rounds_nb(const char *key);
void display_array(const char **array);
void display_blocks(unsigned const char ***blocs);
void free_list(char **list);
void free_blocks(const char ***blocks);

#endif
