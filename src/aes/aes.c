#include "./aes.h"
#include <stdio.h>

const char *aes_c_d
(const char *message, const char *key, bool encrypt, bool block_mode)
{
    if (encrypt)
        return aes_encrypt(message, key);
    else
        return aes_decrypt(message, key);
}

void display_array(const char **array)
{
    int i = 0;

    for (i = 0; array[i] != NULL; i++) {
        printf("%s\n", array[i]);
    }
    printf("i == %d\n", i);
}

const char *aes_encrypt
(const char *message, const char *key)
{
    const char **key_ex = key_expansion(key);

    display_array(key_ex);
    free_list((char **)key_ex);
    return "encrypt";
}

const char *aes_decrypt
(const char *message, const char *key)
{
    return "decrypt";
}
