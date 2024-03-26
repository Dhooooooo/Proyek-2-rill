#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Hafidz_admin.h"

//fitur kupon dibikin hafidz
void createCoupon(char *coupon, int discount) {
    // Membuat atau overwrite file database
    FILE *couponList;
    couponList = fopen("../user/database/List_coupon.txt", "a");

    // Menyimpan kupon yang dibuat ke database
    fprintf(couponList, "%s %d\n", coupon, discount);
    
    fclose(couponList);
}

void displayCouponList() {
    // Melakukan read file database
    FILE *couponList;
    couponList = fopen("../user/database/List_coupon.txt", "r");
    if (!couponList) {
        printf("File tidak ada.\n");
        return;
    }

    char storedCoupon[MAX_COUPON_LENGTH];
    int storedDiscount;

    printf("\nLIST COUPON\n");
    printf("============\n");
    
    // Menampilkan kupon yang ada di database
    while (fscanf(couponList, "%s %d", storedCoupon, &storedDiscount) != EOF) {
        printf("Kode Kupon: %s | Diskon: %d | ", storedCoupon, storedDiscount);
        encrypt(storedCoupon);
        printf("Kupon (setelah enkripsi): %s\n", storedCoupon);
    }

    fclose(couponList);
}

void changeDiscount(char *coupon, int newDiscount) {
    FILE *couponList;
    FILE *tempList;
    char tempCoupon[MAX_COUPON_LENGTH];
    int tempDiscount;
    int found = 0;

    couponList = fopen("../user/database/List_coupon.txt", "r");
    if (!couponList) {
        printf("File tidak ada.\n");
        return;
    }

    tempList = fopen("../user/database/temp_List_coupon.txt", "w");
    if (!tempList) {
        printf("File tidak ada.\n");
        fclose(couponList);
        return;
    }
	
	
    while (fscanf(couponList, "%s %d", tempCoupon, &tempDiscount) != EOF) {
        if (strcmp(coupon, tempCoupon) == 0) {
            fprintf(tempList, "%s %d\n", tempCoupon, newDiscount);
            found = 1;
        } else {
            fprintf(tempList, "%s %d\n", tempCoupon, tempDiscount);
        }
    }

    fclose(couponList);
    fclose(tempList);

    remove("../user/database/List_coupon.txt");
    rename("../user/database/temp_List_coupon.txt", "../user/database/List_coupon.txt");

    if (found) {
        printf("Diskon untuk kupon %s berhasil diubah menjadi %d\n", coupon, newDiscount);
    } else {
        printf("Kupon tidak ditemukan.\n");
    }
}

void coupon() {
    char coupon[MAX_COUPON_LENGTH];
    int discount;
    int choice;
    
    // Main menu
    do {
        choice = displayMenu();
        system("cls");
        switch (choice) {
            case 1:
                // create coupon
                printf("Masukkan kode kupon: ");
                scanf("%s", coupon);
                printf("Masukkan diskon: ");
                scanf("%d", &discount);
                
                // Prosedur menyimpan kupon ke database
                createCoupon(coupon, discount);
                
                // Prosedur enkripsi kupon yang diinput
                encrypt(coupon);
    
                printf("\nKode kupon: %s\n", coupon);
                spaceToContinue();
                clearScreen();
                break;
            
            case 2:
                // List coupon
                displayCouponList();
                spaceToContinue();
                clearScreen();
                break;
            
            case 3:
                // Change discount
                printf("Masukkan kode kupon yang ingin diubah diskonnya: ");
                scanf("%s", coupon);
                printf("Masukkan diskon baru: ");
                scanf("%d", &discount);
                changeDiscount(coupon, discount);
                spaceToContinue();
                clearScreen();
                break;
            
            case 4:
            	clearScreen();
                break;
        	default:
        		printf("Pilihan tidak valid\n");
        }
    } while (choice != 4);
}

