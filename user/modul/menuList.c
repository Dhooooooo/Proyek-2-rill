#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include "../payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 5

// Fungsi untuk menampilkan menu

void waitNext() {
	printf("\nHarap tunggu");
	int i;
    for(i = 0; i < 3; i++){
    	printf(".");
    	sleep(1);
	}
}

void inputAkun(char *username, char *password, char *pin){
 	printf("Username: ");
  	scanf("%s", username);
   	printf("Password: ");
    scanf(" %s", password);
    printf("Pin: ");
    scanf(" %s", pin);
}

void inputEdit(char *username, char *password){
   	printf("New Password: ");
    scanf(" %s", password);
}

void inputEditPin(char *username, char *newPin){
   	printf("New Pin: ");
    scanf(" %s", newPin);
}

void inputEditUser(char *username, char *password){
	 printf("New Username: ");
    scanf(" %s", username);
}

int displayMenu() {
    int choice;
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Pilih menu: ");
    scanf("%d", &choice);
    return choice;
}

int displayMenuAfter(){
	int menu2;
	printf("Selamat Datang di PayPrim\n");
	printf("1. Pembelian\n");
	printf("2. Top-up Saldo E-Wallet\n");
	printf("3. cek kupon\n");
	printf("4. profile\n");
	printf("5. logout\n");
	printf("Pilih Menu : ");
	scanf("%d", &menu2);
	return menu2;
}

int displayMenuPembelian(){
	int menuPembelian;
	printf("Silakan pilih menu Pembelian\n");
	printf("1. Pesan hotel\n");
	printf("2. Isi Pulsa\n");
	printf("3. Kereta Api\n");
	printf("4. Kembali\n");
	printf("Pilih Menu : ");
	scanf("%d", &menuPembelian);
	return menuPembelian;
}

int displayMenuProfil() {
    int profil;
    printf("\nMenu:\n");
    printf("1. Edit Username\n");
    printf("2. Edit Password\n");
    printf("3. Edit Pin\n");
    printf("4. Cek Histori Pembelian\n");
    printf("5. Kembali\n");
    printf("Pilih menu: ");
    scanf("%d", &profil);
    return profil;
}


void spaceToContinue(){
	printf("\n\nTekan spasi untuk melanjutkan");
    while(getch() != ' '); // menunggu user menekan spasi untuk melanjutkan
    system("cls");
}

void clearScreen(){
	system("cls");
}
