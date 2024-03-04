#include <stdio.h>
#include <string.h>

char char_set[] = "`1qaz2wsx3edc4rfv5tgb6yhn7ujm8ik,9ol.p;-['=]/~!QAZ@WSX#EDC$RFV%TGB^YHN&UJM*IK<(OL>)P:?_\{+}|";
int mod = sizeof(char_set)+1;
int i, j;
int MAXLENGTH = 1000;

void createCoupon(char cpn[8], int dsk);
char encryptCoupon();

typedef struct{
	char fcoupon[8];
	int fdiskon;
}A;

A a;

void createCoupon(char cpn[], int dsk) {
	printf("Masukkan kode voucher: ");
	scanf("%s", &cpn);
	printf("Masukkan diskon: ");
	scanf("%d", &dsk);
}

char encryptCoupon() {
	
}

int main() {
	FILE *couponList;
	couponList = fopen("List_coupon.txt", "a+");
	char coupon[8];
	int diskon;
	createCoupon(coupon, diskon);
	strcpy(a.fcoupon, coupon);
	a.fdiskon = diskon;
	fscanf("%s" "%d", &a.fcoupon, &a.fdiskon);
	fprintf(couponList, "%s" "%d", a.fcoupon, a.fdiskon);
	fclose(couponList);
}
