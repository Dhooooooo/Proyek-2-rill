#include <stdio.h>
#include <string.h>

char char_set[] = "`1qaz2wsx3edc4rfv5tgb6yhn7ujm8ik,9ol.p;-['=]/~!QAZ@WSX#EDC$RFV%TGB^YHN&UJM*IK<(OL>)P:?_\{+}|";
int mod = sizeof(char_set)+1;
int i, j;
int MAXLENGTH = 1000;

char readCoupon(char coup);
char decryptCoupon();

char readCoupon(char coup) {
	FILE *listCoupon;
	listCoupon = fopen("List_coupon.txt", "r");
	
	if (!listCoupon) {
		printf("File tidak ada.");
	}
}

char decryptCoupon() {
	static char dekrip[100];
    for (i = 0; i < strlen(cipherText); i++) {
        int index = 0;
        if (cipherText[i] == ' ') {
            dekrip[i] = ' ';
        }
        if (cipherText[i] == '0') {
            dekrip[i] = '0';
        }
        for (j = 0; j < strlen(char_set); j++) {
            if (char_set[j] == cipherText[i]) {
                while ((index - 7) % 3 != 0){
                	index += mod;
				}
                int hasil = (index - 7) / 3;
                dekrip[i] = char_set[hasil];
                break;
            }
            index++;
        }
    }
    return dekrip;
}
}

int main() {
	char coupon;
	printf("Masukkan kode kupon: ");
	scanf("%s", &coupon);
	printf("%s", &coupon);
	readCoupon(coupon);
	return 0;
}	
