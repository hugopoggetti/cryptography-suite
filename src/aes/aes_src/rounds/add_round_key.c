/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "../include/aes.h"

void xor_block_key(unsigned char **block, const char *key)
{
    int index = 0;

    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            block[j][i] =
                (unsigned char)block[j][i]
                ^ hex_pair_to_byte(key[index], key[index + 1]);
            index += 2;
        }
    }
}

void add_round_key(unsigned char ***blocks, const char *key)
{
    for (size_t i = 0; blocks[i]; i++) {
        xor_block_key(blocks[i], key);
    }
}
