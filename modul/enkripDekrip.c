#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 5


void encrypt(char *text) {
    char *ptr = text;
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            *ptr = (*ptr + ENCRYPTION_KEY) % 126; // ASCII printable characters range
        }
        ptr++;
    }
}

void decrypt(char *text) {
    char *ptr = text;
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            *ptr = (*ptr - ENCRYPTION_KEY + 126) % 126; // ASCII printable characters range
        }
        ptr++;
    }
}

char char_set[] = "1qazZAQ2wsxXSW3edcCDE4rfvVFR5tgbBGT6yhnNHY7ujmMJU8ikKI9olLOpP";
int mod = sizeof(char_set);

char* enkripsi(char plainText[]) {	
    static char enkrip[100]; // assuming the length won't exceed 100 characters
    int i, j;
    for (i = 0; i < strlen(plainText); i++) {
    	bool isPlainInChar = false;
        int index = 0;
        for (j = 0; j < strlen(char_set); j++) {
            if (char_set[j] == plainText[i]) {
            	isPlainInChar = true;
                int hasil = (index * 3 + 7) % mod;
                enkrip[i] = char_set[hasil];
                break;
            }
            index++;
        }
        if(!isPlainInChar){
        	enkrip[i] = plainText[i];
		}
    }
    return enkrip;
}

char* dekripsi(char cipherText[]) {
	
    static char dekrip[100]; // assuming the length won't exceed 100 characters
    int i,j;
    for (i = 0; i < strlen(cipherText); i++) {
    	bool isCipherInChar = false;
        int index = 0;
        for (j = 0; j < strlen(char_set); j++) {
            if (char_set[j] == cipherText[i]) {
            	isCipherInChar = true;
                while ((index - 7) % 3 != 0)
                    index += mod;
                int hasil = (index - 7) / 3;
                dekrip[i] = char_set[hasil];
                break;
            }
            index++;
        }
        if(!isCipherInChar){
        	dekrip[i] = cipherText[i];
		}
    }
    return dekrip;
}

