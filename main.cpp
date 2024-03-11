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
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf(" %[^\n]", password); // Membaca sampai karakter newline
                registerUser(username, password);
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
                    int menu2;
                    
                    do {
                    	menu2 = displayMenuAfter();
                    	system("cls");
                    	switch (menu2){
                    		case 1:
                    			break;
                   			case 2:
                   				break;
            				case 3:
            					break;	
						}
                    	
					}while (choice != 4);
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

