#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../payPrim.h"

int readCoupon(char *coupon, int discount) {
    FILE *listCoupon;
    listCoupon = fopen("database/List_coupon.txt", "r");
    if (!listCoupon) {
        printf("File tidak ada.\n");
        return;
    }

    char storedCoupon[MAX_COUPON_LENGTH];
    int storedDiscount;
    int found = 0;
    long int position;
    
    // Dekripsi kupon yang diinput
    
    decrypt(coupon);
    
    // Mencari kupon di database
    while (!feof(listCoupon)) {
        position = ftell(listCoupon);
        fscanf(listCoupon, "%s %d", storedCoupon, &storedDiscount);
        if (strcmp(coupon, storedCoupon) == 0) {
            fseek(listCoupon, position, SEEK_SET);
            discount = storedDiscount;
            found = 1;
            break;
        }
    }

    fclose(listCoupon);

    if (found) {
        printf("Selamat! Anda mendapatkan diskon sebesar %d persen\n", discount);
        spaceToContinue();
    } else {
        printf("Kode kupon tidak valid.\n");
        spaceToContinue();
    }
    return discount;
}

int kupon(char *coupon) {
	printf("Masukkan kode kupon: ");
	scanf("%s", coupon);
    int discount = readCoupon(coupon, discount);
    
    int potongan = discount;
    
    return potongan;
}

void checkCoupon (char *username[]) {
	char coupon[MAX_COUPON_LENGTH];
	int discount;
	
	printf("Masukkan kode kupon: ");
    scanf("%s", coupon);
    
    FILE *listCoupon;
    listCoupon = fopen("database/List_coupon.txt", "r");
    if (!listCoupon) {
        printf("File tidak ada.\n");
        return;
    }

    char storedCoupon[MAX_COUPON_LENGTH];
    int storedDiscount;
    int found = 0;
    long int position;
    
    // Dekripsi kupon yang diinput
    
    decrypt(coupon);
    
    // Mencari kupon di database
    while (!feof(listCoupon)) {
        position = ftell(listCoupon);
        fscanf(listCoupon, "%s %d", storedCoupon, &storedDiscount);
        if (strcmp(coupon, storedCoupon) == 0) {
            fseek(listCoupon, position, SEEK_SET);
            discount = storedDiscount;
            found = 1;
            break;
        }
    }

    fclose(listCoupon);

    if (found) {
        printf("Kupon tersedia! Kupon ini memiliki diskon sebesar %d persen\n", discount);
    } else {
        printf("Kode kupon tidak valid.\n");
    }
}
