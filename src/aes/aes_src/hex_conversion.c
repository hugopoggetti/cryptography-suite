/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "include/aes.h"

unsigned char hex_char_to_val(char c)
{
    if (c >= '0' && c <= '9')
        return (unsigned char)(c - '0');
    if (c >= 'a' && c <= 'f')
        return (unsigned char)(10 + (c - 'a'));
    if (c >= 'A' && c <= 'F')
        return (unsigned char)(10 + (c - 'A'));
    return 0;
}

unsigned char hex_pair_to_byte(char high, char low)
{
    return (unsigned char)
        ((hex_char_to_val(high) << 4) | hex_char_to_val(low));
}

void byte_to_hex_pair(unsigned char val, char *dest)
{
    static const char hex[] = "0123456789abcdef";

    dest[0] = hex[(val >> 4) & 0xF];
    dest[1] = hex[val & 0xF];
}

unsigned const char *str_hex_to_str_val(const char *message, size_t *size)
{
    unsigned char *val_str = malloc(sizeof(char) * (strlen(message) / 2));
    size_t index = 0;

    for (size_t i = 0; message[i]; i += 2) {
        val_str[index] = hex_pair_to_byte(message[i], message[i + 1]);
        index++;
    }
    *size = index;
    return val_str;
}
