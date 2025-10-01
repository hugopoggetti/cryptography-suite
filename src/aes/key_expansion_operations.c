/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "aes.h"

void xor_rcon(char *word, int round)
{
    unsigned char first_byte = hex_pair_to_byte(word[0], word[1]);

    first_byte ^= rcon(round);
    byte_to_hex_pair(first_byte, word);
}

void sub_word(char *word)
{
    unsigned char b = 0;

    for (int i = 0; i < 8; i += 2) {
        b = hex_pair_to_byte(word[i], word[i + 1]);
        b = sub_byte(b);
        byte_to_hex_pair(b, word + i);
    }
}

char *xor_words(char *new, char *a, char *b)
{
    unsigned char byte_a = 0;
    unsigned char byte_b = 0;
    unsigned char x = 0;

    for (size_t i = 0; a[i]; i += 2) {
        byte_a = hex_pair_to_byte(a[i], a[i + 1]);
        byte_b = hex_pair_to_byte(b[i], b[i + 1]);
        x = byte_a ^ byte_b;
        sprintf(new + i, "%02x", x);
    }
    return new;
}

void rot_word(char *word)
{
    char tmp[3];

    tmp[0] = word[0];
    tmp[1] = word[1];
    for (int i = 0; i < 6; i += 2) {
        word[i] = word[i + 2];
        word[i + 1] = word[i + 3];
    }
    word[6] = tmp[0];
    word[7] = tmp[1];
}
