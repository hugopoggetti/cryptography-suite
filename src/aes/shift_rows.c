/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "aes.h"

void shift_rows_block(unsigned char **block)
{
    unsigned char tmp[4];

    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tmp[j] = block[i][(j + i) % 4];
        }
        for (int j = 0; j < 4; j++) {
            block[i][j] = tmp[j];
        }
    }
}

void shift_rows(unsigned char ***blocks)
{
    for (size_t i = 0; blocks[i]; i++) {
        shift_rows_block(blocks[i]);
    }
}

void inv_shift_rows_block(unsigned char **block)
{
    unsigned char tmp[4];

    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tmp[j] = block[i][(j - i + 4) % 4];
        }
        for (int j = 0; j < 4; j++) {
            block[i][j] = tmp[j];
        }
    }
}

void inv_shift_rows(unsigned char ***blocks)
{
    for (size_t i = 0; blocks[i]; i++) {
        inv_shift_rows_block(blocks[i]);
    }
}
