#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN 6
#define ENCRYPTION_KEY 5

void registerUser(char *username, char *password, char *pin) {
    // Melakukan enkripsi pada password sebelum disimpan
    
    FILE *file = fopen("database/users.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    
    // Membaca file dan memeriksa apakah username sudah ada
    while (fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin) == 3) {
        if (strcmp(username, storedUsername) == 0) {
            fclose(file);
            printf("====================\n");
    		printf("= Registrasi Gagal =\n");
    		printf("====================\n");
            printf("Username sudah digunakan.\n");
            spaceToContinue();
            return;
        }
    }
    
    fclose(file);
    
    file = fopen("database/users.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    // Memeriksa PIN
    int pinLength = strlen(pin);
    if (pinLength != MAX_PIN) {
    	printf("====================\n");
   		printf("= Registrasi Gagal =\n");
   		printf("====================\n");
        printf("Panjang PIN harus 6 angka.\n");
        spaceToContinue();
        return; // PIN tidak valid
    }
    int i;
    for (i = 0; i < pinLength; i++) {
        if (pin[i] < '0' || pin[i] > '9') {
        	printf("====================\n");
    		printf("= Registrasi Gagal =\n");
    		printf("====================\n");
            printf("PIN hanya boleh terdiri dari angka.\n");
            spaceToContinue();
            return; // PIN tidak valid
        }
    }
    
    encrypt(password);
    encrypt(pin);
    
    fprintf(file, "%s %s %s\n", username, password, pin);
    fclose(file);
    clearScreen();
    
    printf("=======================\n");
    printf("= Registrasi berhasil =\n");
    printf("=======================\n");
}

// Fungsi untuk login
int loginUser(char *username, char *password, char *pin) {
    FILE *file = fopen("database/users.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }
    rewind(file);
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    
    while (!feof(file)) {
        fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin);
        decrypt(storedPin);
        decrypt(storedPassword);
        
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0 && strcmp(pin, storedPin) == 0) {
            fclose(file);
            printf("==================\n");
            printf("= Login berhasil =\n");
            printf("==================\n");
            return 1; // Login berhasil
        }
    }
    
    printf("===============\n");
    printf("= Login Gagal =\n");
	printf("===============\n");
	spaceToContinue();
    fclose(file);
    return 0; // Login gagal
}

// Fungsi untuk memodifikasi password pengguna
void modifyPass(char *username, char *newPassword, char *pin) {
    // Melakukan enkripsi pada password baru sebelum disimpan
    encrypt(newPassword);
    encrypt(pin);
    
    FILE *file = fopen("database/users.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    FILE *tempFile = fopen("database/temp.txt", "w"); // Buka file sementara untuk menulis
    if (tempFile == NULL) {
        fclose(file);
        printf("Gagal membuka file sementara.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    
    // Membaca file dan menyalin informasi pengguna ke file sementara
    while (fscanf(file, "%s %s %s", storedUsername, storedPassword, storedPin) == 3) {
        if (strcmp(username, storedUsername) == 0) {
            fprintf(tempFile, "%s %s %s\n", username, newPassword, pin); // Menulis informasi pengguna yang dimodifikasi
        } else {
            fprintf(tempFile, "%s %s %s\n", storedUsername, storedPassword, storedPin); // Menyalin informasi pengguna lain tanpa modifikasi
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    // Menghapus file asli dan mengganti dengan file sementara
    if (remove("database/users.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return;
    }
    if (rename("database/temp.txt", "database/users.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return;
    }
    
    printf("Password berhasil dimodifikasi.\n");
}

