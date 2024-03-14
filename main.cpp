#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN 6
#define ENCRYPTION_KEY 5

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char pin[MAX_PIN];
    int choice; int lolos;
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
                    			//pembelian : jagad angel
                    			break;
                   			case 2:
                   				//top-up saldo e-wallet :ridho
                   				break;
            				case 3:
            					//cek kupon :hapiz
            					break;
							case 4:
								//edit profile :prima
								break;
							case 5:
								//logout
								system("cls");
								waitNext();
								system("cls");
								backMenu = 1;
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

