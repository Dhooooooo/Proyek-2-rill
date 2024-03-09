#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUPON_LENGTH 10
#define MAX_DISCOUNT_LENGTH 10
#define ENCRYPTION_KEY_LENGTH 8

void createCoupon(char *coupon, char *discount);
void encryptCoupon(char *coupon);
void displayCouponList();

void createCoupon(char *coupon, char *discount) {
	// Membuat atau overwrite file database
    FILE *couponList;
    couponList = fopen("List_coupon.txt", "a");

	// Menyimpan kupon yang dibuat ke database
    fprintf(couponList, "%s %s\n", coupon, discount);
    
    fclose(couponList);
}

void encryptCoupon(char *coupon) {
    char *ptr = coupon;
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            *ptr = (*ptr + ENCRYPTION_KEY_LENGTH) % 126; // ASCII printable characters range
        }
        ptr++;
    }
}

void displayCouponList() {
	// Melakukan read file database
    FILE *couponList;
    couponList = fopen("List_coupon.txt", "r");
    if (!couponList) {
        printf("File tidak ada.\n");
        return;
    }

    char storedCoupon[MAX_COUPON_LENGTH];
    char storedDiscount[MAX_DISCOUNT_LENGTH];

    printf("\nLIST COUPON\n");
    printf("============\n");
	
	// Menampilkan kupon yang ada di database
    while (fscanf(couponList, "%s %s", storedCoupon, storedDiscount) != EOF) {
		printf("Kode Kupon: %s | Diskon: %s | ", storedCoupon, storedDiscount);
		encryptCoupon(storedCoupon);
		printf("Kupon: %s\n", storedCoupon);
    }

    fclose(couponList);
}

int displayMenu() {
    int choice;
    printf("\nMENU\n");
    printf("1. Create coupon\n");
    printf("2. List coupon\n");
    printf("3. Exit\n");
    printf("Pilih menu: ");
    
    scanf("%d", &choice);
    
    return choice;
}

int main() {
    char coupon[MAX_COUPON_LENGTH];
    char discount[MAX_DISCOUNT_LENGTH];
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
                scanf("%s", discount);
    			
    			// Prosedur menyimpan kupon ke database
                createCoupon(coupon, discount);
                
                // Prosedur enkripsi kupon yang diinput
                encryptCoupon(coupon);
    
                printf("\nKode kupon: %s\n", coupon);
                printf("\nMasukkan nomor apapun untuk kembali ke menu: ");
                scanf("%d", &choice);
                system("cls");
                break;
            
            case 2:
                // List coupon
                displayCouponList();
                printf("\nMasukkan nomor apapun untuk kembali ke menu: ");
                scanf("%d", &choice);
                system("cls");
                break;
            
            case 3:
                printf("\nEXIT\n");
                break;
        }
    } while (choice != 3);
    
    return 0;
}
