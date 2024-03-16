#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN 6
#define ENCRYPTION_KEY 5

void showInfo(char *username){
	
	FILE *file = fopen("database/saldoUsers.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    float saldo;
    int intSaldo;
    
    while(fscanf(file, "%s %f\n", storedUsername, &saldo) == 2){
    	if(strcmp(storedUsername, username) == 0){
    		intSaldo = (int)saldo;
    		printf("Username : %s\n", storedUsername);
    		printf("Saldo	 : Rp. ");disHarga(intSaldo);printf("\n");
    		fclose(file);
    		return;
		}
	}
}

void title(){
	FILE *file = fopen("database/grafiti.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Gagal membuka file list_barang.txt.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
		printf(" %s", buffer);
    }
    printf("\n");

    fclose(file);
}
