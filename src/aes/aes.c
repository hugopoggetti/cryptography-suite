#include "./aes.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int i = 0;

    for (i = 0; array[i] != NULL; i++) {
        printf("%s\n", array[i]);
    }
    printf("i == %d\n", i);
}

const char *aes_encrypt
(const char *message, const char *key, bool block_mode)
{
    size_t size = strlen(message);
    const char **keys = key_expansion(key);
    message = padd_message(message, block_mode, &size);
 
    // Pading test
    for (int i = 0; i < size; i++) {
        if (!message[i])
            printf(".");
        else
            printf("%c", message[i]);
    }
    printf("\n"); 

    display_array(keys);
    free_list((char **)keys);
    return "encrypt";
}

const char *aes_decrypt
(const char *message, const char *key, bool block_mode)
{
    return "decrypt";
}
