/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "../include/aes.h"

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

const char *encrypt
(unsigned char ***blocks, const char **keys, int round_nb)
{
    const char *encrypted_data = NULL;

    add_round_key(blocks, keys[0]);
    for (int i = 1; i < round_nb; i++)
        nround(blocks, keys[i]);
    final_round(blocks, keys[round_nb]);
    free_list((char **)keys);
    encrypted_data = concat_result(blocks, 1);
    free_blocks(blocks);
    return encrypted_data;
}
