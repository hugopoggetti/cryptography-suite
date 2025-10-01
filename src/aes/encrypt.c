/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "aes.h"
#include <stdio.h>
#include <stdlib.h>

void nround(unsigned char ***blocks, const char *key)
{
    sub_byte_to_blocks(blocks);
    shift_rows(blocks);
    mix_columns(blocks);
    add_round_key(blocks, key);
}

void final_round(unsigned char ***blocks, const char *key)
{
    sub_byte_to_blocks(blocks);
    shift_rows(blocks);
    add_round_key(blocks, key);
}

void fill_out_buffer(unsigned char **block, char *buffer)
{
    int c_index = 0;

    for (size_t col = 0; col < 4; col++) {
        for (size_t row = 0; row < 4; row++) {
            sprintf(buffer + c_index, "%02x",block[row][col]);
            c_index += 2;
        }
    }
}

const char *concat_result(unsigned char ***blocks)
{
    size_t nb_blocks = 0;
    char *encrypted_data = NULL;

    while (blocks[nb_blocks])
        nb_blocks++;
    encrypted_data = malloc((sizeof(char) * (nb_blocks * 32 + 1)));
    for (size_t i = 0; i < nb_blocks; i++)
        fill_out_buffer(blocks[i], encrypted_data);
    encrypted_data[(nb_blocks * 32)] = '\0';
    return ((const char *)encrypted_data);
}

const char *encrypt
(unsigned char ***blocks, const char **keys, int round_nb)
{
    const char *encrypted_data = NULL;
    printf("key expansion list:\n");
    display_array(keys);
    printf("\n");
    display_blocks((unsigned const char ***)blocks);
    
    add_round_key(blocks, keys[0]);
    for (int i = 1; i < round_nb; i++)
        nround(blocks, keys[i]);
    final_round(blocks, keys[round_nb]);

    printf("After cipher operations:\n");
    display_blocks((unsigned const char ***)blocks);
    free_list((char **)keys);
    encrypted_data = concat_result(blocks);
    free_blocks((const char ***)blocks);
    return encrypted_data;
}
