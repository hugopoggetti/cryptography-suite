/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "../include/aes.h"
#include <strings.h>

void reverse_round(unsigned char ***blocks, const char *key)
{
    inv_shift_rows(blocks);
    inv_sub_byte_to_blocks(blocks);
    add_round_key(blocks, key);
    inv_mix_columns(blocks);
}

void reverse_final_round(unsigned char ***blocks, const char *key)
{
    inv_shift_rows(blocks);
    inv_sub_byte_to_blocks(blocks);
    add_round_key(blocks, key);
}

const char *decrypt
(unsigned char ***blocks, const char **keys, int round_nb)
{
    const char *encrypted_data = NULL;
    
    add_round_key(blocks, keys[round_nb]);
    for (int i = round_nb - 1; i >= 1; --i)
        reverse_round(blocks, keys[i]);
    reverse_final_round(blocks, keys[0]);
    free_list((char **)keys);
    encrypted_data = concat_result(blocks, 0);
    free_blocks(blocks);
    return encrypted_data;
}
