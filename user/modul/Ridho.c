#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Ridho.h"
#include "../Jagad.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN 6
#define ENCRYPTION_KEY 5

void topUpSaldo(char *username, float amount) {

	printf("Masukkan jumlah saldo : ");
    scanf("%f", &amount);
    FILE *file = fopen("database/users.txt", "r+");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    FILE *tempFile = fopen("database/usersTemp.txt", "w");
    if (tempFile == NULL) {
        printf("Gagal membuka file.\n");
        fclose(file);
        return;
    }

    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    char storedRole[MAX_USERNAME_LENGTH];
    float saldo;
    int userFound = 0;
    int intAmount = (int)amount; 
	
	clearScreen();
	title();
	printf("Anda akan menambah saldo Rp. ");disHarga(intAmount);printf("\n\n");
	if(confirmPay(username)){
    while (fscanf(file, "%s %s %s %f %s\n", storedUsername,storedPassword,storedPin, &saldo, storedRole) == 5) {
        if (strcmp(storedUsername, username) == 0) {
            userFound = 1;
            saldo += amount; // Menambahkan saldo
        }
        fprintf(tempFile, "%s %s %s %.2f %s\n", storedUsername, storedPassword, storedPin, saldo, storedRole);
    }

    if (!userFound) {
        printf("Pengguna tidak ditemukan\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    fclose(file);
    fclose(tempFile);

    if (remove("database/users.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return;
    }
    if (rename("database/usersTemp.txt", "database/users.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return;
    }

    printf("Saldo berhasil ditambahkan.\n");
} else{
	printf("Pengisian Saldo Dibatalkan");
	return;
}    
}

int menuApprove(){
	int approve;
	printf("1. Hotel\n");
	printf("2. Pesawat\n");
	printf("3. Kereta\n");
	printf("Masukkan pilihan anda");
	scanf("%d", &approve);
}

void approveAdmin(int *approve){
	char p1[] = "hotel";
	char p2[] = "pesawat";
	char p3[] = "kereta";
	linkedListAntrean antri;
	switch (*approve){
		case 1:
			printf("List pemesanan hotel:\n");
			break;
		case 2:
			break;
		case 3:
			break;
	}		
}
