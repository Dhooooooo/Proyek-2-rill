#ifndef RIDHO_H
#define RIDHO_H

int mainMenu();
int menuadmin();
int loginAdmin(char *username, char *password);
int menuAdmin();
int transaksiHotel();
int transaksiPulsa(int pulsa, char *username);
void createCoupon(char *coupon, int discount);
void displayCouponList();
void changeDiscount(char *coupon, int newDiscount);
void coupon();
void disHarga(int harga);
void waitNext();
void spaceToContinue();
int printDecryptedFile(char *username);
void clearScreen();
#endif