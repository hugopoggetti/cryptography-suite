/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "./aes.h"

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
