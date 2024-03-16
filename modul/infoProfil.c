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
    
    while(fscanf(file, "%s %f\n", storedUsername, &saldo) == 2){
    	if(strcmp(storedUsername, username) == 0){
    		printf("Username : %s\n", storedUsername);
    		printf("Saldo	 : %.2f\n", saldo);
    		fclose(file);
    		return;
		}
	}
}

/*void totalPengeluaran(char *username){
	FILE *file = fopen
}*/
