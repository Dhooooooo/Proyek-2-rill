#include <stdio.h>
#include <string.h>
#include "primaJasa.h"

//char char_set[] = "`1qaz2wsx3edc4rfv5tgb6yhn7ujm8ik,9ol.p;-['=]/~!QAZ@WSX#EDC$RFV%TGB^YHN&UJM*IK<(OL>)P:?_\{+}|";
char char_set[] = "1qazZAQ2wsxXSW3edcCDE4rfvVFR5tgbBGT6yhnNHY7ujmMJU8ikKI9olLOpP0"

int mod = sizeof(char_set);


char* enkripsi(char plainText[]) {
	int i,j;
    static char enkrip[100]; // maksimal 100 karakter
    for (i = 0; i < strlen(plainText); i++) {
        int index = 0;
        if (plainText[i] == ' ') {
            enkrip[i] = ' ';
        }
        else{
			for (j = 0; j < strlen(char_set); j++) {
	            if (char_set[j] == plainText[i]) {
	                int hasil = (index * 3 + 7) % mod;
	                enkrip[i] = char_set[hasil];
	                break;
	            }
	            index++;
	        }
		}
    }
    return enkrip;
}

char* dekripsi(char cipherText[]) {
	int i,j;
    static char dekrip[100]; // maksimal 100 karakter
    for (i = 0; i < strlen(cipherText); i++) {
        int index = 0;
        if (cipherText[i] == ' ') {
            dekrip[i] = ' ';
        }
        else{
        	for (j = 0; j < strlen(char_set); j++) {
	            if (char_set[j] == cipherText[i]) {
	                while ((index - 7) % 3 != 0){
	                	index += mod;
					}
	                int hasil = (index - 7) / 3;
	                dekrip[i] = char_set[hasil];
	                break;
	            }
	            index++;
	        }
		}
    }
    return dekrip;
}
