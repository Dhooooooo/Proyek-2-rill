#include "primaJasa.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>  // Library untuk fungsi getch() di Windows


int main(){


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
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf(" %[^\n]", password); // Membaca sampai karakter newline
                if (registerUser(username, password)){
                	printf("Registrasi Berhasil\n");
				} else {
					printf("Username Sudah Digunakan\n");
				}
                //system("cls");
                break;
            case 2:
                // Login
                printf("\nLogin\n");
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf(" %[^\n]", password); // Membaca sampai karakter newline
                if (loginUser(username, password)) {
                    printf("Login berhasil.\n");
                } else {
                    printf("Login gagal. Periksa kembali username dan password.\n");
                }
                break;
            case 3:
                // Modifikasi Password
                printf("\nModifikasi Password\n");
                printf("Username: ");
                scanf("%s", username);
                printf("New Password: ");
                scanf(" %[^\n]", password); // Membaca sampai karakter newline
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

