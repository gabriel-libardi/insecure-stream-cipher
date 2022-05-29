#include <stdio.h>
#include <stdlib.h>


void Lerciphertext(char **primeira_linha, FILE *arquivo) {

    size_t linha_len = 50;
    size_t char_index = 0;
    *primeira_linha = malloc(sizeof(char)*linha_len);

    while (!feof(arquivo)) {
        if (linha_len == char_index) {
            linha_len *= 2;
            *primeira_linha = realloc(*primeira_linha, sizeof(char)*linha_len);
        }

        fscanf(arquivo, "%x", *primeira_linha + char_index);
        char_index++;
    }

    (*primeira_linha)[char_index - 1] = '\0';
}


void Ler(char **primeira_linha, FILE *arquivo) {

    size_t linha_len = 50;
    size_t char_index = 0;

    *primeira_linha = malloc(sizeof(char)*linha_len);

    while (!feof(arquivo) && (*primeira_linha)[char_index - 1] != '\n') {

        if (linha_len == char_index) {
            linha_len *= 2;
            *primeira_linha = realloc(*primeira_linha, sizeof(char)*linha_len);
        }

        (*primeira_linha)[char_index] = fgetc(arquivo);
        char_index++;
    }

    (*primeira_linha)[char_index - 1] = '\0';
}


void generate_key(char *ciphertext, char *guess, char *key) {
    unsigned char last_char = 0;

    for (int index = 0; index < strlen(guess); index++) {
        key[index] = guess[index]^ciphertext[index];
        last_char += key[index];
    }

    key[strlen(guess)] = last_char;
}


void decrypt(char *ciphertext, char *key) {
    unsigned char *plaintext = calloc(sizeof(unsigned char)*(strlen(ciphertext) + 1));
    key_size = strlen(key);

    for (int index = 0; index < strlen(ciphertext); index++) {
        plaintext[index] = ciphertext[index]^key[index%key_size];
    }
}


int main(int agrc, char **argv) {
    FILE *input = open("ciphertext_hex.txt");
    unsigned char *ciphertext;
    Lerciphertext(&ciphertext, input);
    
    unsigned char *guess;
    printf("Type a probable beggining for the message:\n");
    Ler(&guess, stdin);

    unsigned char *key = calloc(sizeof(unsigned char)*(strlen(guess) + 2));
    generate_key(ciphertext, guess, key);

    unsigned char *plaintext = decrypt(ciphertext, key);
    printf("%s\n", plaintext);
}