/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "aes.h"

#define mul2(x) (((x << 1) ^ (((x >> 7) & 1) * 0x1B)) & 0xFF)
#define mul3(x) (mul2(x) ^ x)

void mix_columns_block(unsigned char **block)
{
    unsigned char tmp[4][4] = {0};

    for(size_t i = 0; i < 4; i++) {
        tmp[0][i] = mul2(block[0][i]) ^ mul3(block[1][i]) ^ block[2][i] ^ block[3][i];
        tmp[1][i] = block[0][i] ^ mul2(block[1][i]) ^ mul3(block[2][i]) ^ block[3][i];
        tmp[2][i] = block[0][i] ^ block[1][i] ^ mul2(block[2][i]) ^ mul3(block[3][i]);
        tmp[3][i] = mul3(block[0][i]) ^ block[1][i] ^ block[2][i] ^ mul2(block[3][i]);
    }
    for(size_t i = 0; i < 4; i++)
        for(size_t j = 0; j < 4; j++)
          block[j][i] = tmp[j][i];
}

void mix_columns(unsigned char ***blocks) 
{
    for (size_t i = 0; blocks[i]; i++) {
        mix_columns_block(blocks[i]);
    }
}
