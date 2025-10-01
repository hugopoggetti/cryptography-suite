/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "./aes.h"

const char *aes_c_d
(const char *message, const char *key, bool encrypt, bool block_mode)
{
    if (encrypt)
        return aes_encrypt(message, key, block_mode);
    else
        return aes_decrypt(message, key, block_mode);
}

void display_array(const char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        printf("%s\n", array[i]);
    }
}

const char *aes_encrypt
(const char *message, const char *key, bool block_mode)
{
    size_t size = strlen(message);
    const char **keys = key_expansion(key);

    message = padd_message(message, block_mode, &size);
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
