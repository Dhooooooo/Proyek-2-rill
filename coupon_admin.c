#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUPON_LENGTH 10
#define MAX_DISCOUNT_LENGTH 10
#define ENCRYPTION_KEY 8

void createCoupon(char *coupon, char *discount);
void encryptCoupon(char *coupon);

void createCoupon(char *coupon, char *discount) {
    FILE *couponList;
    couponList = fopen("List_coupon.txt", "a");

    fprintf(couponList, "%s %s\n", coupon, discount);
    
    fclose(couponList);
}

void encryptCoupon(char *coupon) {
    char *ptr = coupon;
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            *ptr = (*ptr + ENCRYPTION_KEY) % 126; // ASCII printable characters range
        }
        ptr++;
    }
}

int main() {
    char coupon[MAX_COUPON_LENGTH];
    char discount[MAX_DISCOUNT_LENGTH];
    
    printf("Masukkan kode kupon: ");
    scanf("%s", coupon);
    printf("Masukkan diskon: ");
    scanf("%s", discount);
    
    createCoupon(coupon, discount);
    encryptCoupon(coupon);
    printf("\nKode kupon: %s\n", coupon);
    
    return 0;
}
