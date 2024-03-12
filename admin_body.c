#include "admin.h"

void createCoupon(char *coupon, int discount) {
    // Membuat atau overwrite file database
    FILE *couponList;
    couponList = fopen("List_coupon.txt", "a");

    // Menyimpan kupon yang dibuat ke database
    fprintf(couponList, "%s %d\n", coupon, discount);
    
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
    int storedDiscount;

    printf("\nLIST COUPON\n");
    printf("============\n");
    
    // Menampilkan kupon yang ada di database
    while (fscanf(couponList, "%s %d", storedCoupon, &storedDiscount) != EOF) {
        printf("Kode Kupon: %s | Diskon: %d | ", storedCoupon, storedDiscount);
        encryptCoupon(storedCoupon);
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

    couponList = fopen("List_coupon.txt", "r");
    if (!couponList) {
        printf("File tidak ada.\n");
        return;
    }

    tempList = fopen("temp_List_coupon.txt", "w");
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

    remove("List_coupon.txt");
    rename("temp_List_coupon.txt", "List_coupon.txt");

    if (found) {
        printf("Diskon untuk kupon %s berhasil diubah menjadi %d\n", coupon, newDiscount);
    } else {
        printf("Kupon tidak ditemukan.\n");
    }
}

int displayMenu() {
    int choice;
    printf("\nMENU\n");
    printf("1. Create coupon\n");
    printf("2. List coupon\n");
    printf("3. Change discount\n");
    printf("4. Exit\n");
    printf("Pilih menu: ");
    
    scanf("%d", &choice);
    
    return choice;
}
