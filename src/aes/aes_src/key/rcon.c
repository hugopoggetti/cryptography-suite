/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "../include/aes.h"

static const unsigned char RCON[11] =
{0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

unsigned char rcon(int round)
{
    return RCON[round];
}
