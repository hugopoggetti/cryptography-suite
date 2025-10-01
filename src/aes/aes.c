/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "./aes.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

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
    char ***blocks = NULL;

    message = padd_message(message, block_mode, &size);
    blocks = dispatch_to_blocks(message, size);
    display_blocks((const char ***)blocks);
    display_array(keys);
    free_list((char **)keys);

    free((void *)message);
    return "encrypt";
}

const char *aes_decrypt
(const char *message, const char *key, bool block_mode)
{
    (void)message;
    (void)key;
    (void)block_mode;
    return "decrypt";
}
