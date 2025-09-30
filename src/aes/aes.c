#include "./aes.h"

const char *aes_c_d
    (const char *message, const char *key, bool encrypt, bool block_mode)
{
    if (encrypt)
        return aes_encrypt(message, key);
    else
        return aes_decrypt(message,key);
}

const char *aes_encrypt
    (const char *message, const char *key)
{
    return "encrypt";
}

const char *aes_decrypt
    (const char *message, const char *key)
{
    return "decrypt";
}
