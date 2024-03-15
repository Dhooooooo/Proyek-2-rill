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
    float saldo; int ada;
    
    while(fscanf(file, "%s %f\n", storedUsername, &saldo) == 2){
    	if(strcmp(storedUsername, username) == 0){
    		fclose(file);
    		return;
		}
	}
	fclose(file);
	
	file = fopen("database/saldoUsers.txt", "a");
	if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
 
    	fprintf(file,"%s %.2f\n", username, saldo);
    fclose(file);
}

int isSaldoCukup(char *username, float totHarga) {
    FILE *file = fopen("database/saldoUsers.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0; //gagal
    }
    
    FILE *tempFile = fopen("database/saldoUsersTemp.txt", "w");
    if (tempFile == NULL) {
        printf("Gagal membuka file.\n");
        fclose(file);
        return 0; //gagal
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    float saldo, lastSaldo;
    int userFound = 0;

    while (fscanf(file, "%s %f", storedUsername, &saldo) == 2) {
        if (strcmp(storedUsername, username) == 0) {
            userFound = 1;
            if (saldo >= totHarga) {
                lastSaldo = saldo - totHarga;
            } else {
                fclose(file);
                fclose(tempFile);
                return 0; //gagal
            }
        }
    }

    if (!userFound) {
        printf("Pengguna tidak ditemukan\n");
        fclose(file);
        fclose(tempFile);
        return 0; //gagal
    }

    rewind(file);

    while (fscanf(file, "%s %f", storedUsername, &saldo) == 2) {
        if (strcmp(username, storedUsername) == 0) {
            fprintf(tempFile, "%s %f\n", username, lastSaldo);
        } else {
            fprintf(tempFile, "%s %f\n", storedUsername, saldo);
        }
    }
    
    fclose(file);
    fclose(tempFile);

    if (remove("database/saldoUsers.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return 0; //gagal
    }
    if (rename("database/saldoUsersTemp.txt", "database/saldoUsers.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return 0; //gagal
    }

    return 1; //berhasil
}


