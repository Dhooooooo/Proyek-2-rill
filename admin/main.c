#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h" 

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 5

int main() {
    int pilihan, hotel, pulsa, totalHotel, totalPembelian=0, totalPemasukan=10;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    do {
        pilihan = mainMenu();
        system("cls");

        switch (pilihan) {
            case 1:
                // Login
                printf("\nLogin\n");
                printf("Username Admin:");
                scanf("%s", username);
                printf("Password:");
                scanf(" %[^\n]", password);
                if (loginAdmin(username, password)) {
                    waitNext();
                    system("cls");
                    int pil;
                    do{
                    	pil=menuAdmin();
                    	switch (pil){
                    		case 1:
                    			clearScreen();
                    			printf("Riwayat hotel: \n");
                    			transaksiHotel();
                    			spaceToContinue();
                    			break;
                    		case 2:
                    			clearScreen();
                    			printf("Riwayat pembelian pulsa: \n");
                    			printDecryptedFile(username);
                    			spaceToContinue();
                    			break;
                    		case 3:
                    			clearScreen();
                    			coupon();
                    			break;
                    		case 4:
                    			clearScreen();
                    			printf("Informasi transaksi: \n");
                    			printf("Transaksi hotel: \n");
                    			totalHotel=transaksiHotel();
                    			printf("Transaksi pulsa: \n");
                    			totalPembelian=printDecryptedFile(username);
                    			totalPemasukan= totalHotel + totalPembelian;
                    			printf("\nTotal transaksi pulsa dan hotel berhasil: Rp. ");
                    			disHarga(totalPemasukan);
                    			spaceToContinue();
                    			break;
                    		case 5:
                    			printf("Terima kasih!\n");
                    			break;
                    		default:
                    			printf("Pilihan tidak valid!");
						}
					}while(pil != 5);
                } else {
                    printf("Login gagal. Periksa kembali username dan password.\n");
                }
                break;
            case 2:
                // Register
                printf("Registrasi admin\n");
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf(" %[^\n]", password); 
                registerAdmin(username, password);
                spaceToContinue();
                break;
            case 3:
                // Exit
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid\n");
        }
    } while (pilihan != 3);

    return 0;
}

