#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN 6
#define ENCRYPTION_KEY 3

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char pin[MAX_PIN];
    int choice;
    int backMenu;
    
    do {
        choice = displayMenu();
        system("cls");
        switch (choice) {
            case 1:
                // Registrasi
                printf("Registrasi\n");
                inputAkun(username, password, pin); 
                registerUser(username, password, pin);
                //system("cls");
                break;
            case 2:
                // Login
                printf("Login\n");
                inputAkun(username, password, pin); 
                if (loginUser(username, password, pin)) {
                    printf("Login berhasil.\n");
                    int menu2;
                    waitNext();
                    do {
                    	system("cls");
                    	backMenu = 0;
                    	menu2 = displayMenuAfter();
                    	switch (menu2){
                    		case 1:
                    			printf("Edit Password\n");
                				inputAkun(username, password, pin);
                				modifyUser(username, password);
                    			break;
                   			case 2:
                   				break;
            				case 3:
            					break;
							case 4:
								system("cls");
								waitNext();
								system("cls");
								backMenu = 1;
								break;
							default:
								printf("pilihan tidak valid");
						}
                    	
					}while ((menu2 != 4) && (backMenu = 0));
                } else {
                    printf("Login gagal. Periksa kembali username dan password.\n");
                }
                break;
            case 3:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 3);
    
    return 0;
}

