#include "coupon.h"

void readCoupon(char *coupon, int *discount) {
    FILE *listCoupon;
    listCoupon = fopen("List_coupon.txt", "r");
    if (!listCoupon) {
        printf("File tidak ada.\n");
        return;
    }

    char storedCoupon[MAX_COUPON_LENGTH];
    int storedDiscount;
    int found = 0;
    long int position;
    
    // Dekripsi kupon yang diinput
    decryptCoupon(coupon);
    
    // Mencari kupon di database
    while (!feof(listCoupon)) {
        position = ftell(listCoupon);
        fscanf(listCoupon, "%s %d", storedCoupon, &storedDiscount);
        if (strcmp(coupon, storedCoupon) == 0) {
            fseek(listCoupon, position, SEEK_SET);
            *discount = storedDiscount;
            found = 1;
            break;
        }
    }

    fclose(listCoupon);

    if (found) {
        printf("Selamat! Anda mendapatkan diskon sebesar %d persen\n", *discount);
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

int kupon(char *coupon) {
    int discount;
    
    readCoupon(coupon, &discount);
    int potongan = discount;
    
    return potongan;
}
