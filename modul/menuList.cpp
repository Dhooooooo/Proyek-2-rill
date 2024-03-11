#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../payPrim.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 3

// Fungsi untuk menampilkan menu
int displayMenu() {
    int choice;
    printf("\nMenu:\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Modify Password\n"); // Opsi baru
    printf("4. Exit\n");
    printf("Pilih menu: ");
    scanf("%d", &choice);
    return choice;
}

int displayMenuAfter(){
	int menu2;
	printf("Selamat Datang di PayPrim\n");
	printf("1. Pesan Tiket\n");
	printf("2. Bayar Listrik\n");
	printf("3. \n");
	printf("4. \n");
	printf("5. \n");
	printf("6. \n");
	scanf("%d", &menu2);
}
