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
    float harga, amount;
    int choice, lolos, backMenu, beli, profil;
    
    do {
    	clearScreen();
    	title();
        choice = displayMenu();
        clearScreen();
        switch (choice) {
            case 1:
                // Registrasi
                title();
                printf("Registrasi\n");
                inputAkun(username, password, pin); 
                registerUser(username, password, pin);
                waitNext();
                dataSaldoNew(username);
                break;
            case 2:
                // Login
                title();
                printf("Login\n");
                inputAkun(username, password, pin); 
                if (loginUser(username, password, pin)) {
                    dataSaldoNew(username);
                    int menu2;
                    waitNext();
                    do {
                        clearScreen();
                        title();
                        menu2 = displayMenuAfter();
                        switch (menu2){
                            case 1:
                            	do {
                                clearScreen();
                                title();
                                beli = displayMenuPembelian();
                                    switch (beli){
                                        case 1:
                                            printf("Anda akan memesan kamar hotel");
                                            pemesananHotel(username);
                                            spaceToContinue();
                                            break;
                                        case 2:
                                            printf("Anda akan membeli pulsa");
                                            pembelianPulsa(username);
                                            spaceToContinue();
                                            break;
                                        case 3:
                                            
                                            waitNext();
                                            
                                            break;
                                        default:
                                            printf("Pilihan tidak valid.");
                                    }
                                } while (beli != 3);
                                break;
                            case 2:
                                //top-up saldo e-wallet :ridho
                                clearScreen();
                                title();
                            	topUpSaldo(username, amount);
                            	spaceToContinue();
                                break;
                            case 3:
                            	clearScreen();
                            	title();
                                printf("Cek Kupon\n");
            					checkCoupon(username);
            					spaceToContinue();
            					waitNext();
            					break; 
                            case 4://profile :prima
                                do{
                                	clearScreen();
                                	title();
                                	showInfo(username);
                                	profil = displayMenuProfil();
                                	switch (profil){
                                		case 1:
                                			clearScreen();
                               				title();
                               				inputEditUser(username, password);
                               				modifyUser(username, password);
                               				spaceToContinue();
                                			break;
                               			case 2:
                               				clearScreen();
                               				title();
                               				inputEdit(username, password);
                               				modifyPass(username, password);
                               				spaceToContinue();
                               				break;
                        				case 3:
                        					clearScreen();
                               				title();
                        					inputEditPin(username, pin);
                               				modifyPin(username, pin);
                               				spaceToContinue();
                        					break;
                       					case 4:
                       						clearScreen();
                                			printf("Pemesanan Hotel\n");
                                			disPemesananUser(username);
                                			printf("\nTop Up pulsa\n");
                                			printDecryptedFile(username);
                                			spaceToContinue();
                       						break;
       									case 5:
       										break;
       									default:
       										printf("Pilihan Tidak Valid");
									}
								} while(profil != 5);
                                break;
                            case 5: //logout
                                
                                waitNext();
                                
                                backMenu = 1;
                                break;
                            default:
                                printf("pilihan tidak valid");
                        }
                    } while (backMenu == 0); 
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
