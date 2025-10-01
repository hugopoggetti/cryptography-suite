/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "aes.h"

char *padd_block_mode(const char *message, size_t *size)
{
    char *padded = NULL;
    size_t diff = 0;

    padded = malloc(sizeof(char) * BLOCK_SIZE);
    if (*size < BLOCK_SIZE) {
        diff = BLOCK_SIZE - *size;
        padded = malloc(sizeof(char) * BLOCK_SIZE);
        memcpy(padded, message, *size);
        memset(padded + *size, 0, diff);
        (*size) = BLOCK_SIZE;
    } else {
        memcpy(padded, message, BLOCK_SIZE);
        (*size) = BLOCK_SIZE;
    }
    return padded;
}

size_t find_next_size(size_t size)
{
    while (size % 16 != 0) {
        size++;
    }
    return size;
}

char *padd_to_block_size(const char *message, size_t *size)
{
    char *padded = NULL;
    size_t new_size = 0;

    if (*size % BLOCK_SIZE == 0) {
        padded = malloc(sizeof(char) * (*size));
        memcpy(padded, message, *size);
    } else {
        new_size = find_next_size(*size);
        padded = malloc(sizeof(char) * (new_size + 1));
        memcpy(padded, message, *size);
        memset(padded + *size, 0, new_size - (*size));
        (*size) = new_size;
    }
    return padded;
}

const char *padd_message(const char *message, bool block_mode, size_t *size)
{
    char *padded = NULL;

    if (block_mode) {
        padded = padd_block_mode(message, size);
    } else {
        padded = padd_to_block_size(message, size);
    }
    return (const char *)padded;
}
