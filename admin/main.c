#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h" 

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 5

int main() {
    int pilihan;
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
                    printf("Login berhasil.\n");
                    int pil;
                    do{
                    	pil=menuAdmin();
                    	system("cls");
                    	switch (pil){
                    		case 1:
                    			printf("Riwayat hotel: \n");
                    			break;
                    		case 2:
                    			printf("Riwayat pembelian pulsa: \n");
                    			break;
                    		case 3:
                    			printf("Buat atau rubah kupon\n");
                    			coupon();
                    			break;
                    		case 4:
                    			printf("Informasi pemasukan: \n");
                    			int totalPemasukan;
                    			void totalHotel();
                    			void totalPulsa();
                    			int totHotel;
                    			int totPulsa;
                    			totalPemasukan=totHotel + totPulsa;
                    			printf("Total pemasukan:");
                    			printf("%s", totalPemasukan);
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
                system("cls");
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

