#include "./aes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

static const unsigned char RCON[11] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

static const unsigned char S_BOX[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
    0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
    0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
    0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
    0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
    0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
    0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
    0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
    0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
    0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
    0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

unsigned char rcon(int round)
{
    return RCON[round];
}

unsigned char sub_byte(unsigned char val)
{
    return S_BOX[val];
}

char **get_words(const char *key, int words_nb)
{
    char **words = malloc(sizeof(char *) * (words_nb + 1));
    int char_in_word = strlen(key) / words_nb;
    int char_index = 0;
    int word_index = 0;
    
    words[word_index] = malloc(sizeof(char) * (char_in_word + 1));
    for (size_t i = 0; key[i]; i++) {
        if (char_index == char_in_word) {
            words[word_index][char_index] = '\0';
            words[++word_index] = malloc(sizeof(char) * (char_in_word + 1));
            char_index = 0;
        }
        words[word_index][char_index++] = key[i];
    }
    words[word_index][char_index] = '\0';
    words[word_index + 1] = NULL;
    return words;
}

unsigned char hex_char_to_val(char c) 
{
    if(c >= '0' && c <= '9') return c - '0';
    if(c >= 'a' && c <= 'f') return 10 + (c - 'a');
    if(c >= 'A' && c <= 'F') return 10 + (c - 'A');
    return 0;
}

unsigned char hex_pair_to_byte(char high, char low)
{
    return (hex_char_to_val(high) << 4) | hex_char_to_val(low);
}

char *xor_words(char *new, char *a, char *b)
{
    for (size_t i = 0; a[i]; i++) {
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
    for(int i=0;i<6;i+=2)
        word[i] = word[i+2], word[i+1] = word[i+3];
    word[6] = tmp[0]; 
    word[7] = tmp[1];
}

void byte_to_hex_pair(unsigned char val, char *dest)
{
    static const char hex[] = "0123456789abcdef";

    dest[0] = hex[(val >> 4) & 0xF];
    dest[1] = hex[val & 0xF];
}

void xor_rcon(char *word, int round)
{
    unsigned char first_byte = hex_pair_to_byte(word[0], word[1]);

    first_byte ^= rcon(round);
    byte_to_hex_pair(first_byte, word);
}

void sub_word(char *word) 
{
    for(int i=0; i<8; i+=2) {
        unsigned char b = hex_pair_to_byte(word[i], word[i+1]);
        b = sub_byte(b);
        byte_to_hex_pair(b, word + i);
    }
}

char **get_next_word(char **words_split, const char *key)
{
    words_split = realloc(words_split, sizeof(char *) * 45);
    
    for (size_t i = 4; i <= 44; i++) {
        words_split[i] = malloc(sizeof(char) * 9);
        if (i % 4 == 0) {
            words_split[i] = memcpy(words_split[i], words_split[i - 1], 8);
            rot_word(words_split[i]);
            sub_word(words_split[i]);
            xor_rcon(words_split[i], i/4);
        } else
           words_split[i] = xor_words(words_split[i], words_split[i - 4], words_split[i - 1]); 
        words_split[i][8] = '\0';
    }
    words_split[44] = NULL;
    return words_split;
}

const char **concat_list(char **word_list)
{
    int num_words = 0;
    while (word_list[num_words]) num_words++;

    int num_keys = (num_words + 3) / 4; 
    char **key_list = malloc(sizeof(char *) * (num_keys + 1));
    key_list[num_keys] = NULL;

    for (int k = 0; k < num_keys; k++) {
        key_list[k] = malloc(sizeof(char) * 33);
        key_list[k][0] = '\0';
        for (int j = 0; j < 4; j++) {
            int word_index = k*4 + j;
            if (word_index >= num_words) break;
            strcat(key_list[k], word_list[word_index]);
        }
    }
    return (const char **)key_list;
}

const char **key_expansion(const char *key)
{
    // TODO: temp 10 for aes 128
    int roun_nb = 10;
    int words_nb = ((strlen(key) / 2 ) / 4);
    char **words_split = get_words(key, words_nb);
    char **word_list = get_next_word(words_split, key);
    const char **key_list = concat_list(word_list);
    return (const char **)key_list;
}
