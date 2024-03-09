#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUPON_LENGHT 10
#define MAX_DISCOUNT_LENGHT 10

void readCoupon(char *coupon, char *diskon);

void readCoupon(char *coupon, char *diskon) {
	FILE *listCoupon;
	listCoupon = fopen("List_coupon.txt", "r+");
	
	if (!listCoupon) {
		printf("File tidak ada.");
	}
	rewind(listCoupon);
	
	char storedCoupon[MAX_COUPON_LENGHT];
	char storedDiskon[MAX_DISCOUNT_LENGHT];
	
	while (!feof(listCoupon)) {
        fscanf(listCoupon, "%s %s\n", storedCoupon, storedDiskon);
        if (strcmp(coupon, storedCoupon) == 0 && strcmp(diskon, storedDiskon) == 0) {
		fclose(listCoupon);
        }
    }
    return;
}

int main() {
	char coupon[MAX_COUPON_LENGHT];
	char diskon[MAX_DISCOUNT_LENGHT];
	printf("Masukkan kode kupon: ");
	scanf("%s", &coupon);
	readCoupon(coupon, diskon);
	printf("Selamat! Anda mendapatkan diskon sebesar %s", diskon);
	return 0;
}	
