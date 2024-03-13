#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 3*5

// Fungsi untuk menampilkan menu

void waitNext() {
	printf("\nHarap tunggu");
    for(int i = 0; i < 3; i++){
    	printf(".");
    	fflush(stdout);
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

int displayMenu() {
    int choice;
    printf("\nMenu:\n");
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
	printf("1. Edit Password\n");
	printf("2. Bayar Listrik\n");
	printf("3. Beli Tiket\n");
	printf("4. Logout\n");
	printf("5. \n");
	printf("6. \n");
	printf("Pilih Menu : ");
	scanf("%d", &menu2);
	return menu2;
}
