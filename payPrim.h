#ifndef primaJasa_H
#define primaJasa_H

void encrypt(char *text);

void decrypt(char *text);

void registerUser(char *username, char *password);

int loginUser(char *username, char *password);

void modifyUser(char *username, char *newPassword);

int displayMenu();

//fungsi untuk enkripsi plaintext/teks biasa diubah bentuknya
char* enkripsi(char plainText[]);

//fungsi untuk dekripsi ciphertext/menubah teks yang sudah diubah bentuknya menjadi teks sebelum diubah
char* dekripsi(char cipherText[]);

#endif
