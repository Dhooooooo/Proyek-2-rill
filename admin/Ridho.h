#ifndef RIDHO_H
#define RIDHO_H

int mainMenu();
int menuadmin();
int loginAdmin(char *username, char *password);
int menuAdmin();
int transaksiHotel();
int transaksiPulsa(int pulsa, char *username);
void disHarga(int harga);
void waitNext();
void spaceToContinue();
int printDecryptedFile(char *username);
void clearScreen();
#endif
