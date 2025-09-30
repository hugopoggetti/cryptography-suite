#include "aes.h"

unsigned char rcon(int round)
{
    return RCON[round];
}

unsigned char sub_byte(unsigned char val)
{
    return S_BOX[val];
}

void xor_rcon(char *word, int round)
{
    unsigned char first_byte = hex_pair_to_byte(word[0], word[1]);

    first_byte ^= rcon(round);
    byte_to_hex_pair(first_byte, word);
}

void sub_word(char *word) 
{
    for(int i = 0; i < 8; i += 2) {
        unsigned char b = hex_pair_to_byte(word[i], word[i + 1]);
        b = sub_byte(b);
        byte_to_hex_pair(b, word + i);
    }
}

unsigned char hex_char_to_val(char c) 
{
    if(c >= '0' && c <= '9') 
        return (unsigned char)(c - '0');
    if(c >= 'a' && c <= 'f') 
        return (unsigned char)(10 + (c - 'a'));
    if(c >= 'A' && c <= 'F')
        return (unsigned char)(10 + (c - 'A'));
    return 0;
}

unsigned char hex_pair_to_byte(char high, char low)
{
    return (hex_char_to_val(high) << 4) | hex_char_to_val(low);
}

char *xor_words(char *new, char *a, char *b)
{
    for (size_t i = 0; a[i]; i += 2) {
        unsigned char byte_a = hex_pair_to_byte(a[i], a[i+1]);
        unsigned char byte_b = hex_pair_to_byte(b[i], b[i+1]);
        unsigned char x = byte_a ^ byte_b;
        sprintf(new + i, "%02x", x);
    }
    return new;
}

void rot_word(char *word)
{
    char tmp[3];

    tmp[0] = word[0]; 
    tmp[1] = word[1];
    for(int i=0;i<6;i+=2) {
        word[i] = word[i+2];
        word[i+1] = word[i+3];
    }
    word[6] = tmp[0]; 
    word[7] = tmp[1];
}

void byte_to_hex_pair(unsigned char val, char *dest)
{
    static const char hex[] = "0123456789abcdef";

    dest[0] = hex[(val >> 4) & 0xF];
    dest[1] = hex[val & 0xF];
}
