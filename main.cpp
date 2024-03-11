#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 3

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int choice;
    
    do {
        choice = displayMenu();
        system("cls");
        switch (choice) {
            case 1:
                // Registrasi
                printf("Registrasi\n");
                inputAkun(username, password); // Membaca sampai karakter newline
                registerUser(username, password);
                //system("cls");
                break;
            case 2:
                // Login
                printf("Login\n");
                inputAkun(username, password); // Membaca sampai karakter newline
                if (loginUser(username, password)) {
                    printf("Login berhasil.\n");
                } else {
                    printf("Login gagal. Periksa kembali username dan password.\n");
                }
                break;
            case 3:
                // Modifikasi Password
                printf("Edit Password\n");
                inputAkun(username, password); // Membaca sampai karakter newline
                modifyUser(username, password);
                break;
            case 4:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 4);
    
    return 0;
}

