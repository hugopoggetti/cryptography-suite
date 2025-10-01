/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "./aes.h"
#include <stdio.h>

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
    // printf("size = %zu\n", size);
    // for (size_t i = 0; i < size; i++) {
    //     if (message[i] == 0)
    //         printf(".");
    //     else
    //         printf("%c", message[i]);
    // }
    // printf("\nsize = %zu\n", size);
    blocks = dispatch_to_blocks(message, size);
    free((void *)message);
    return encrypt(blocks, keys, rounds);
}

const char *aes_decrypt
(const char *message, const char *key, bool block_mode)
{
    (void)message;
    (void)key;
    (void)block_mode;
    return "decrypt";
}
