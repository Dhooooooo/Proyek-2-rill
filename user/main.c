#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "payPrim.h"
#include "Jagad.h"
#include "Prima.h"
#include "Ridho.h"
#include "Hafidz.h"
#include "Angel.h"
#include "admin.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN 6
#define MAX_ROLE_LENGTH 5
#define ENCRYPTION_KEY 5

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char pin[MAX_PIN];
    char role[MAX_ROLE_LENGTH]; // Add role variable
    float harga, amount;
    int choice, lolos, backMenu, beli, profil;
    Tiket tiket;
    
    int pilihan, hotel, pulsa, totalHotel = 0, totalPesawat = 0, totalKereta = 0, totalPemasukan = 0;
    
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
                // Default role is user
                strcpy(role, "user");
                registerUser(username, password, pin, role);
                waitNext();
                //dataSaldoNew(username);
                break;
            case 2:
                // Login
                title();
                printf("Login\n");
                inputAkun(username, password, pin);
                if (loginUser(username, password, pin, role)) {
                    char storedRole[MAX_ROLE_LENGTH];
                    getUserRole(username, storedRole);
                    waitNext();
                    if (strcmp(role, "admin") == 0) { // Check if the user is an admin
                        int adminChoice;
                        do {
                            clearScreen();
                            title();
                            adminChoice = menuAdmin();
                            switch (adminChoice) {
                                case 1:
                                    clearScreen();
                                    printf("Riwayat pemesanan kamar hotel: \n");
                                    transaksiHotel();
                                    spaceToContinue();
                                    break;
                                case 2:
                                    clearScreen();
                                    printf("Riwayat pembelian tiket pesawat: \n");
                                    transaksiPesawat();
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
                                    totalHotel = transaksiHotel();
                                    printf("Transaksi pesawat: \n");
                                    totalPesawat = transaksiPesawat();
                                    printf("Transaksi kereta: \n");
                                    totalKereta = transaksiKereta();
                                    totalPemasukan = totalHotel + totalPesawat + totalKereta;
                                    printf("\nTotal transaksi pesawat dan hotel berhasil: Rp. ");
                                    disHarga(totalPemasukan);
                                    spaceToContinue();
                                    break;
                                case 5:
                                    // Registrasi admin
                                    clearScreen();
                                    printf("Registrasi Admin\n");
                                    inputAkun(username, password, pin);
                                    strcpy(role, "admin");
                                    registerUser(username, password, pin, role);
                                    waitNext();
                                    break;
                            	case 6:
                                    printf("Terima kasih!\n");
                                    waitNext();
                                    break;
                                case 7:
                                	printf("Approve pesanan");
                                	break;
                                case 8:
                                	printf("Riwayat pembelian tiket kereta");
                                	transaksiKereta();
									spaceToContinue();
                                	break;
                                default:
                                    printf("Pilihan tidak valid!");
                            }
                        } while (adminChoice != 6);
                    } else { // If not an admin, regular user
                        int userChoice;
                        do {
                            clearScreen();
                            title();
                            userChoice = displayMenuAfter();
                            switch (userChoice) {
                                case 1:
                                    do {
                                        clearScreen();
                                        title();
                                        beli = displayMenuPembelian();
                                        switch (beli) {
                                            case 1:
                                                printf("Anda akan memesan kamar hotel");
                                                pemesananHotel(username);
                                                spaceToContinue();
                                                break;
                                            case 2:
                                                printf("Anda akan membeli tiket pesawat");
                                                pembelianTiket(username);
                                                spaceToContinue();
                                                break;
                                            case 3:
	                                        	printf("Anda akan memesan tiket kereta");
	                                        	pemesananKereta(username);
	                                        	spaceToContinue();
	                                            break;
                                            default:
                                                printf("Pilihan tidak valid.");
                                        }
                                    } while (beli != 4);
                                    break;
                                case 2:
                                    // Top-up saldo e-wallet
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
                                case 4:
                                    // Profile
                                    do {
                                        clearScreen();
                                        title();
                                        showInfo(username);
                                        profil = displayMenuProfil();
                                        switch (profil) {
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
                                                printf("\nPemesanan Tiket Pesawat\n");
                                                printDecryptedFile(username);
                                                spaceToContinue();
                                                break;
                                            case 5:
                                                break;
                                            default:
                                                printf("Pilihan Tidak Valid");
                                        }
                                    } while (profil != 5);
                                    break;
                                case 5: // Logout
                                    waitNext();
                                    break;
                                default:
                                    printf("Pilihan tidak valid");
                            }
                        } while (userChoice != 5);
                    }
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
