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

int isSaldoCukup(char *username, float totHarga){
	
	FILE *file = fopen("database/saldoUsers.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    FILE *tempFile = fopen("database/saldoUsersTemp.txt", "w"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    float saldo; float lastSaldo;
    
    while(!feof){
    	fscanf(file, "%s %f\n", storedUsername, saldo);
 		if (strcmp(storedUsername, username) == 0){
			if (saldo >= totHarga){
				lastSaldo = saldo - totHarga;
			} else{
				printf("saldo tidak cukup");
				return 0; //gagal
			}
		} else{
			printf("Pengguna tidak ditemukan");
			return 0; //gagal
		}
	} 
	rewind(file);
	
	while (!feof){
		fscanf(file, "%s %f", storedUsername, saldo);
		if (strcmp(username, storedUsername) == 0) {
            fprintf(tempFile, "%s %f\n", username, lastSaldo); // Menulis informasi pengguna yang dimodifikasi
        } else {
            fprintf(tempFile, "%s %f\n", username, saldo); // Menyalin informasi pengguna lain tanpa modifikasi
        }
	}
	
	fclose(file);
    fclose(tempFile);
    
    // Menghapus file asli dan mengganti dengan file sementara
    if (remove("database/saldoUsers.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return;
    }
    if (rename("database/saldoUsersTemp.txt", "database/saldoUsers.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return;
    }
    
    return 1; //berhasil
}
