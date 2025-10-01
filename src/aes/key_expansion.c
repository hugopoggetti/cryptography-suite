/*
** EPITECH PROJECT, 2025
** my_pgp
** File description:
** aes
*/

#include "./aes.h"

// return list of words
char **get_words(const char *key, int words_nb)
{
    char **words = malloc(sizeof(char *) * (unsigned long)(words_nb + 1));
    int c_in_word = (int)strlen(key) / words_nb;
    int char_index = 0;
    int word_index = 0;

    words[word_index] = malloc(sizeof(char) * (unsigned long)(c_in_word + 1));
    for (size_t i = 0; key[i]; i++) {
        if (char_index == c_in_word) {
            words[word_index][char_index] = '\0';
            word_index++;
            words[word_index] =
                malloc(sizeof(char) * (unsigned long)(c_in_word + 1));
            char_index = 0;
        }
        words[word_index][char_index] = key[i];
        char_index++;
    }
    words[word_index][char_index] = '\0';
    words[word_index + 1] = NULL;
    return words;
}

char **get_next_word(char **words, int nb_words)
{
    char tmp[9] = {0};

    words = realloc(words, sizeof(char *) * (unsigned long)(nb_words + 1));
    for (int i = 4; i <= nb_words; i++) {
        words[i] = malloc(sizeof(char) * 9);
        if (i % 4 == 0) {
            memcpy(tmp, words[i - 1], 9);
            rot_word(tmp);
            sub_word(tmp);
            xor_rcon(tmp, i / 4);
            words[i] =
                xor_words(words[i], words[i - 4], tmp);
        } else {
            words[i] =
                xor_words(words[i], words[i - 4], words[i - 1]);
        }
        words[i][8] = '\0';
    }
    words[nb_words] = NULL;
    return words;
}

const char **concat_list(char **word_list, int rounds)
{
    char **key_list = malloc(sizeof(char *) * (unsigned long)(rounds + 2));
    int key_i = 0;
    int index = 0;

    for (int i = 0; i < rounds + 2; i++) {
        key_list[i] = malloc(sizeof(char) * 33);
        key_list[i][0] = '\0';
    }
    for (size_t i = 0; word_list[i]; i++) {
        if (index == 4) {
            index = 0;
            key_i++;
        }
        strcat(key_list[key_i], word_list[i]);
        index++;
    }
    key_list[rounds + 1] = NULL;
    return (const char **)key_list;
}

// return list of all key for encryption/decryption
const char **key_expansion(const char *key)
{
    int round = get_aes_rounds_nb(key);
    int words_nb = ((int)(strlen(key) / 2) / 4);
    int total_words = (4 * (round + 1));
    char **word_list = get_next_word(get_words(key, words_nb), total_words);
    const char **key_list = concat_list(word_list, round);

    free_list(word_list);
    return (const char **)key_list;
}
