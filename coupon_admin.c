#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUPON_LENGTH 10
#define ENCRYPTION_KEY_LENGTH 8

void createCoupon(char *coupon, int discount);
void encryptCoupon(char *coupon);
void displayCouponList();
void changeDiscount(char *coupon, int newDiscount);

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

int main() {
    char coupon[MAX_COUPON_LENGTH];
    int discount;
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
                scanf("%d", &discount);
                
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
                // Change discount
                printf("Masukkan kode kupon yang ingin diubah diskonnya: ");
                scanf("%s", coupon);
                printf("Masukkan diskon baru: ");
                scanf("%d", &discount);
                changeDiscount(coupon, discount);
                printf("\nMasukkan nomor apapun untuk kembali ke menu: ");
                scanf("%d", &choice);
                system("cls");
                break;
            
            case 4:
                printf("\nEXIT\n");
                break;
        }
    } while (choice != 4);
    
    return 0;
}

