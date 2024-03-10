#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 3


void encrypt(char *text) {
    char *ptr = text;
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            *ptr = (*ptr + ENCRYPTION_KEY) % 126; // ASCII printable characters range
        }
        ptr++;
    }
}

void decrypt(char *text) {
    char *ptr = text;
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            *ptr = (*ptr - ENCRYPTION_KEY + 126) % 126; // ASCII printable characters range
        }
        ptr++;
    }
}

void registerUser(char *username, char *password) {
    encrypt(password);
    
    FILE *file = fopen("users.txt", "a");
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


    FILE *file = fopen("users.txt", "r");
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
    
    FILE *file = fopen("users.txt", "r+");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    rewind(file);
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    long int currentPosition;
    
    while (!feof(file)) {
        currentPosition = ftell(file);
        fscanf(file, "%s %s", storedUsername, storedPassword);
        if (strcmp(username, storedUsername) == 0) {
            fseek(file, currentPosition, SEEK_SET);
            fprintf(file, "\n%s %s\n", username, newPassword);
            fclose(file);
            printf("Password berhasil dimodifikasi.\n");
            return;
        }
    }
    
    fclose(file);
    printf("Pengguna tidak ditemukan.\n");
}

// Fungsi untuk menampilkan menu
int displayMenu() {
    int choice;
    printf("\nMenu:\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Modify Password\n"); // Opsi baru
    printf("4. Exit\n");
    printf("Pilih menu: ");
    scanf("%d", &choice);
    return choice;
}
