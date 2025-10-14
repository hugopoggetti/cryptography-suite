/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "../include/aes.h"
#include <stdio.h>
#include <string.h>

const char *aes_c_d
(const char *message, const char *key, bool encrypt, bool block_mode)
{
    if (encrypt)
        return aes_encrypt(message, key, block_mode);
    else
        return aes_decrypt(message, key, block_mode);
}

const char *aes_encrypt
(const char *message, const char *key, bool block_mode)
{
    size_t size = strlen(message);
    const char **keys = key_expansion(key);
    int rounds = get_aes_rounds_nb(key);
    unsigned char ***blocks = NULL;

    message = padd_message(message, block_mode, &size);
    blocks = dispatch_to_blocks(message, size);
    free((void *)message);
    return encrypt(blocks, keys, rounds);
}

const char *aes_decrypt
(const char *message, const char *key, bool block_mode)
{
    (void)block_mode;
    size_t size = strlen(message);
    int rounds = get_aes_rounds_nb(key);
    const char **keys = key_expansion(key);
    const unsigned char *crypted_data = str_hex_to_str_val(message, &size);
    unsigned char ***blocks = NULL;

    blocks = dispatch_to_blocks((const char *)crypted_data, size);
    free((void *)crypted_data);
    return decrypt(blocks, keys, rounds);
}
