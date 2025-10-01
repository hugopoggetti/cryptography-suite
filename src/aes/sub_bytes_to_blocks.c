/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "aes.h"

void sub_byte_to_block(unsigned char **block)
{
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            block[j][i] = sub_byte(block[j][i]);
        }
    }
}

void sub_byte_to_blocks(unsigned char ***blocks)
{
    for (size_t i = 0; blocks[i]; i++) {
        sub_byte_to_block(blocks[i]);
    }
}
