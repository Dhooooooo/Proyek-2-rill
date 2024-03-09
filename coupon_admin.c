#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUPON_LENGHT 10
#define MAX_DISCOUNT_LENGHT 10
#define ENCRYPTION_KEY 8

void createCoupon(char *coupon, char *diskon);
void encryptCoupon(char *coupon);

void createCoupon(char *coupon, char *diskon) {
	FILE *couponList;
	couponList = fopen("List_coupon.txt", "a");
    fprintf(couponList, "%s %s\n", coupon, diskon);
    
    encryptCoupon(coupon);
    
    fclose(couponList);
}

void encryptCoupon(char *coupon) {
	char *ptr = coupon;
    while (*ptr != '\0') {
		if (*ptr != ' ') {
    		*ptr = (*ptr + ENCRYPTION_KEY) % 126; // ASCII printable characters range
        }
        ptr++;
    return;
	}
}

int main() {
	char coupon[MAX_COUPON_LENGHT];
	char diskon[MAX_DISCOUNT_LENGHT];
	
	printf("Masukkan kode kupon: ");
	scanf("%s", &coupon);
	printf("Masukkan diskon: ");
	scanf("%s", &diskon);
	
	createCoupon(coupon, diskon);
	
	printf("\nKode kupon: %s\n", coupon);
	
	return 0;
}
