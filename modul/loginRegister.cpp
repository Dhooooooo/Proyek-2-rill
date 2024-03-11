#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 3

void registerUser(char *username, char *password) {
    // Melakukan enkripsi pada password sebelum disimpan
    encrypt(password);
    
    FILE *file = fopen("database/users.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    
    // Membaca file dan memeriksa apakah username sudah ada
    while (fscanf(file, "%s %s", storedUsername, storedPassword) == 2) {
        if (strcmp(username, storedUsername) == 0) {
            fclose(file);
            printf("Username sudah digunakan.\n");
            return;
        }
    }
    
    fclose(file);
    
    // Jika username belum ada, buka file untuk menulis dan tambahkan pengguna baru
    file = fopen("database/users.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    
    printf("Registrasi berhasil.\n");
}


// Fungsi untuk login
int loginUser(char *username, char *password) {


    FILE *file = fopen("database/users.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }
    rewind(file);
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    
    while (!feof(file)) {
        fscanf(file, "%s %s\n", storedUsername, storedPassword);
        decrypt(storedPassword);
        //printf("%s\n", storedPassword);
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(file);
            return 1; // Login berhasil
        }
    }
    
    fclose(file);
    return 0; // Login gagal
}

// Fungsi untuk memodifikasi password pengguna
void modifyUser(char *username, char *newPassword) {
    // Melakukan enkripsi pada password baru sebelum disimpan
    encrypt(newPassword);
    
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
    
    // Membaca file dan menyalin informasi pengguna ke file sementara
    while (fscanf(file, "%s %s", storedUsername, storedPassword) == 2) {
        if (strcmp(username, storedUsername) == 0) {
            fprintf(tempFile, "%s %s\n", username, newPassword); // Menulis informasi pengguna yang dimodifikasi
        } else {
            fprintf(tempFile, "%s %s\n", storedUsername, storedPassword); // Menyalin informasi pengguna lain tanpa modifikasi
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    // Menghapus file asli dan mengganti dengan file sementara
    if (remove("database/users.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return;
    }
    if (rename("temp.txt", "database/users.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return;
    }
    
    printf("Password berhasil dimodifikasi.\n");
}
