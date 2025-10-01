/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "aes.h"
#include <stdio.h>

// dispatch to 4*4 block
unsigned char **dispatch_to_block(const char *message)
{
    unsigned char **block = malloc(sizeof(char *) * 5);
    int index = 0;

    for (size_t i = 0; i < 4; i++)
        block[i] = malloc(sizeof(char) * 4);
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            block[j][i] = (unsigned char)message[index];
            index++;
        }
    }
    block[4] = NULL;
    return block;
}

unsigned char ***dispatch_to_blocks(const char *message, size_t mess_size)
{
    size_t block_nb = mess_size / 16;
    unsigned char ***blocks = malloc(sizeof(char **) * (block_nb + 1));

    for (size_t i = 0; i < block_nb; i++) {
        blocks[i] = dispatch_to_block(message);
        message += 16;
    }
    blocks[block_nb] = NULL;
    return blocks;
}
