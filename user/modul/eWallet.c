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
    float saldo; int ada; float saldoAwal = 0;
    
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
    
 
    	fprintf(file,"%s %.2f\n", username, saldoAwal);
    fclose(file);
}

int isSaldoCukup(char *username, float totHarga) {
    FILE *file = fopen("database/saldoUsers.txt", "r+");
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

void topUpSaldo(char *username, float amount) {

	printf("Masukkan jumlah saldo : ");
    scanf("%f", &amount);
    FILE *file = fopen("database/saldoUsers.txt", "r+");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    FILE *tempFile = fopen("database/saldoUsersTemp.txt", "w");
    if (tempFile == NULL) {
        printf("Gagal membuka file.\n");
        fclose(file);
        return;
    }

    char storedUsername[MAX_USERNAME_LENGTH];
    float saldo;
    int userFound = 0;
    int intAmount = (int)amount;
	
	clearScreen();
	title();
	printf("Anda akan menambah saldo Rp. ");disHarga(intAmount);printf("\n\n");
	if(confirmPay(username)){
    while (fscanf(file, "%s %f", storedUsername, &saldo) == 2) {
        if (strcmp(storedUsername, username) == 0) {
            userFound = 1;
            saldo += amount; // Menambahkan saldo
        }
        fprintf(tempFile, "%s %.2f\n", storedUsername, saldo);
    }

    if (!userFound) {
        printf("Pengguna tidak ditemukan\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    fclose(file);
    fclose(tempFile);

    if (remove("database/saldoUsers.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return;
    }
    if (rename("database/saldoUsersTemp.txt", "database/saldoUsers.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return;
    }

    printf("Saldo berhasil ditambahkan.\n");
} else{
	printf("Pengisian Saldo Dibatalkan");
	return;
}    
}

int confirmPay(char *username) {
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    char pin[MAX_PIN];
    int acc;
    FILE *file = fopen("database/users.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }

    do {
        printf("1. Konfirmasi Pembayaran \n");
        printf("2. Cancel\n");
        printf("Pilih Tindakan : ");
        scanf("%d", &acc);
    } while (acc != 1 && acc != 2);

    if (acc == 1) {
        printf("Masukkan PIN : ");
        scanf("%s", pin);
        encrypt(pin);

        int pinFound = 0; // Variabel penanda untuk mengetahui apakah PIN ditemukan
        while (fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin) == 3) {
            if (strcmp(username, storedUsername) == 0 && strcmp(pin, storedPin) == 0) {
                pinFound = 1; // Setel variabel penanda jika PIN ditemukan
                break; // Keluar dari loop setelah menemukan PIN yang cocok
            }
        }

        if (pinFound) {
            fclose(file);
            return 1;
        } else {
            printf("PIN Salah\n");
            fclose(file);
            return 0;
        }
    } else {
        printf("Pembelian Dibatalkan\n");
        fclose(file);
        return 0;
    }

    // Lakukan operasi pada file
    fclose(file); // Jangan lupa tutup file setelah digunakan
}


