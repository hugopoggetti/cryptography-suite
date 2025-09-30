#pragma once

#include <stdlib.h>
#include <stdbool.h>

// Aes function definition for encryption/decryption
const char *aes_c_d
    (const char *message, const char *key, bool encrypt, bool block_mode);
const char *aes_encrypt
    (const char *message, const char *key);
const char *aes_decrypt
    (const char *message, const char *key);
