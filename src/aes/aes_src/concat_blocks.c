/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "include/aes.h"
#include <stdio.h>

void format_data(char *buffer, int *c_index, unsigned char data, bool encrypt)
{
    if (encrypt) {
        sprintf(buffer + *c_index, "%02x", data);
        *c_index += 2;
    } else {
        buffer[*c_index] = (char)data;
        (*c_index)++;
    }
}

void fill_out_buffer(unsigned char **block, char *buffer, int *c_index, bool encrypt)
{
    for (size_t col = 0; col < 4; col++)
        for (size_t row = 0; row < 4; row++)
            format_data(buffer, c_index, block[row][col], encrypt);
}

const char *concat_result(unsigned char ***blocks, bool encrypt)
{
    size_t nb_blocks = 0;
    char *encrypted_data = NULL;
    size_t out_size = 0;
    int c_index = 0;

    if (encrypt)
        out_size = 32;
    else
        out_size = 16;
    while (blocks[nb_blocks])
        nb_blocks++;
    encrypted_data = malloc((sizeof(char) * (nb_blocks * out_size + 1)));
    for (size_t i = 0; i < nb_blocks; i++)
        fill_out_buffer(blocks[i], encrypted_data, &c_index, encrypt);
    encrypted_data[(nb_blocks * out_size)] = '\0';
    return ((const char *)encrypted_data);
}
