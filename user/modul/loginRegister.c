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
    rewind(file);
    while (fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin) == 3) {
        if (strcmp(password, storedPassword) == 0) {
            fclose(file);
            printf("====================\n");
    		printf("= Registrasi Gagal =\n");
    		printf("====================\n");
            printf("Password sudah digunakan.\n");
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
            encrypt(password);
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
void modifyPass(char *username, char *password) {
    // Melakukan enkripsi pada password baru sebelum disimpan
    encrypt(password);
    
    FILE *file = fopen("database/users.txt", "r+"); // Buka file untuk membaca
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
            fprintf(tempFile, "%s %s %s\n", storedUsername, password, storedPin); // Menulis informasi pengguna yang dimodifikasi
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
    
    printf("Password berhasil diubah\n");
}

void modifyPin(char *username, char *newPin) {
    // Melakukan enkripsi pada password baru sebelum disimpan
    int pinLength = strlen(newPin);
    if (pinLength != MAX_PIN) {
        printf("Panjang PIN harus 6 angka.\n");
        spaceToContinue();
        return; // PIN tidak valid
    }
    int i;
    for (i = 0; i < pinLength; i++) {
        if (newPin[i] < '0' || newPin[i] > '9') {
            printf("PIN hanya boleh terdiri dari angka.\n");
            spaceToContinue();
            return; // PIN tidak valid
        }
    }
    
    encrypt(newPin);
    
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
            fprintf(tempFile, "%s %s %s\n", storedUsername, storedPassword, newPin); // Menulis informasi pengguna yang dimodifikasi
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
    
    printf("PIN berhasil diubah\n");
}

void modifyUser(char *username, char *password) {
    // Melakukan enkripsi pada password baru sebelum disimpan
    //encrypt(password);
    char tempUser[MAX_USERNAME_LENGTH];
    
    FILE *file = fopen("database/users.txt", "r+"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    
    // Membaca file dan memeriksa apakah username baru sudah ada
    while (fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin) == 3) {
        if (strcmp(username, storedUsername) == 0) {
            fclose(file);
            printf("Username sudah digunakan.\n");
            strcpy(username, storedUsername);
            return;
        }
    }
    
    rewind(file);
    
    // Memeriksa apakah password yang diberikan valid
    int validPassword = 0;
    while (fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin) == 3) {
    	//printf("%s\n", password);
    	//printf("%s\n", storedPassword);
        if (strcmp(password, storedPassword) == 0) {
            validPassword = 1;
            strcpy(tempUser, storedUsername);
            break;
        }
    }
    if (!validPassword) {
        fclose(file);
        printf("Password salah.\n");
        return;
    }
    
    // Mengupdate file saldoUsers.txt
    FILE *files = fopen("database/saldoUsers.txt", "r");
    if (files == NULL) {
        fclose(file);
        printf("Gagal membuka file.\n");
        return; //gagal
    }
    
    FILE *tempFiles = fopen("database/saldoUsersTemp.txt", "w");
    if (tempFiles == NULL) {
        fclose(files);
        fclose(file);
        printf("Gagal membuka file.\n");
        return; //gagal
    }
    float saldo;
    while (fscanf(files, "%s %f", storedUsername, &saldo) == 2) {
        if (strcmp(tempUser, storedUsername) == 0) {
            fprintf(tempFiles, "%s %f\n", username, saldo);
        } else {
            fprintf(tempFiles, "%s %f\n", storedUsername, saldo);
        }
    }
    
    fclose(files);
    fclose(tempFiles);

    if (remove("database/saldoUsers.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return; //gagal
    }
    if (rename("database/saldoUsersTemp.txt", "database/saldoUsers.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return; //gagal
    }
    
    rewind(file);
    
    FILE *tempFile = fopen("database/temp.txt", "w"); // Buka file sementara untuk menulis
    if (tempFile == NULL) {
        fclose(file);
        printf("Gagal membuka file sementara.\n");
        return;
    }
    
    // Membaca file dan menyalin informasi pengguna ke file sementara
    while (fscanf(file, "%s %s %s", storedUsername, storedPassword, storedPin) == 3) {
        if (strcmp(tempUser, storedUsername) == 0) {
            fprintf(tempFile, "%s %s %s\n", username, storedPassword, storedPin); // Menulis informasi pengguna yang dimodifikasi
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
    
    printf("Username berhasil diubah\n");
}
