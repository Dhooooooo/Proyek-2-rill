#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUPON_LENGTH 10
#define MAX_DISCOUNT_LENGTH 10
#define ENCRYPTION_KEY_LENGTH 8

void readCoupon(char *coupon, char *discount);
void decryptCoupon(char *coupon);

void readCoupon(char *coupon, char *discount) {
    FILE *listCoupon;
    listCoupon = fopen("List_coupon.txt", "r");
    if (!listCoupon) {
        printf("File tidak ada.\n");
        return;
    }

    char storedCoupon[MAX_COUPON_LENGTH];
    char storedDiscount[MAX_DISCOUNT_LENGTH];
    int found = 0;
    long int position;
    
    // Dekripsi kupon yang diinput
	decryptCoupon(coupon);
	
	// Mencari kupon di database
    while (!feof(listCoupon)) {
    	position = ftell(listCoupon);
    	fscanf(listCoupon, "%s %s", storedCoupon, storedDiscount);
        if (strcmp(coupon, storedCoupon) == 0) {
        	fseek(listCoupon, position, SEEK_SET);
            strcpy(discount, storedDiscount);
            found = 1;
            break;
        }
    }

    fclose(listCoupon);

    if (found) {
        printf("Selamat! Anda mendapatkan diskon sebesar %s\n", discount);
    } else {
        printf("Kode kupon tidak valid.\n");
    }
}

void decryptCoupon(char *coupon) {
    char *ptr = coupon;
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            *ptr = (*ptr - ENCRYPTION_KEY_LENGTH + 126) % 126; // ASCII printable characters range
        }
        ptr++;
    }
}

int main() {
    char coupon[MAX_COUPON_LENGTH];
    char discount[MAX_DISCOUNT_LENGTH];

    printf("Masukkan kode kupon: ");
    scanf("%s", coupon);
    
    // Prosedur mencari kupon di database
    readCoupon(coupon, discount);

    return 0;
}

