/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "./aes.h"
#include <stdio.h>

void free_list(char **list)
{
    char **tmp = list;

    while (*tmp) {
        free(*tmp);
        tmp++;
    }
    free(list);
}

int get_aes_rounds_nb(const char *key)
{
    int type = ((int)strlen(key) / 2) * 8;
    int round = 0;

    if (type == 128)
        round = 10;
    else if (type == 192)
        round = 12;
    else
        round = 14;
    return round;
}

void display_array(const char **array)
{
    for (int i = 0; array[i] != NULL; i++) {
        printf("%s\n", array[i]);
    }
}

static void display_block(unsigned const char **block)
{
    for (size_t j = 0; j < 4; j++) {
        printf("[");
        for (size_t n = 0; n < 4; n++) {
            printf("%02x", block[j][n]);
        }
        printf("]\n");
    }
}

void display_blocks(unsigned const char ***blocks)
{
    for (int i = 0; blocks[i]; i++) {
        printf("block %d\n", i);
        display_block(blocks[i]);
        printf("\n");
    }
}

void free_blocks(const char ***blocks)
{
    for (int i = 0; blocks[i]; i++) {
        free_list((char **)blocks[i]);
    }
}
