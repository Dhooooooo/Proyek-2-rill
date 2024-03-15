#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN 6
#define ENCRYPTION_KEY 5

void dataSaldoNew(char *username){
	
	FILE *file = fopen("database/saldoUsers.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    float saldo;
    
    while(!feof){
    	fscanf(file, "%s %f", storedUsername, saldo );
    	if(strcmp(storedUsername, username) == 0){
    		return;
		}
	}
	fclose(file);
	
	file = fopen("database/saldoUsers.txt", "w");
	if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    fprintf(file,"%s %.2f", username, saldo);
    fclose(file);
}
