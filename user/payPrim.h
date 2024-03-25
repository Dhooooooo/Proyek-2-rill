#ifndef payPrim_h
#define payPrim_h

#include <stdbool.h>

/* modul yang dipakai di banyak header*/
// Tekan spasi untuk melanjutkan
void spaceToContinue();
// Untuk menampilkan harga yang dipisahkan dengan .
void disHarga(int harga);
// Fungsi untuk enkripsi plaintext/teks biasa diubah bentuknya
char *enkripsi(char plainText[]);
// Fungsi untuk dekripsi ciphertext/menubah teks yang sudah diubah bentuknya menjadi teks sebelum diubah
char *dekripsi(char cipherText[]);

//enkrip Dekrip
void encrypt(char *text);
void decrypt(char *text);

//Akun Register Login
void registerUser(char *username, char *password, char *pin);
int loginUser(char *username, char *password, char *pin);
void modifyPass(char *username, char *password);
void modifyPin(char *username, char *newPin);
void modifyUser(char *username, char *password);
void showInfo(char *username);

//Per e-Wallet an
void dataSaldoNew(char *username);
int isSaldoCukup(char *username, float totHarga);
int confirmPay(char *username);

//Buat Menu
void waitNext();
void title();
void inputAkun(char *username, char *password, char *pin);
void inputEdit(char *username, char *password);
void inputEditPin(char *username, char *newPin);
void inputEditUser(char *username, char *password);
int displayMenu();
int displayMenuAfter();
int displayMenuPembelian();
int displayMenuProfil();
void clearScreen();

#endif
