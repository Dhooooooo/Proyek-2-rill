#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../payPrim.h"
#include "../Hafidz.h"

/* COUPON */

int readCoupon(char *coupon, int discount) {
    FILE *listCoupon;
    listCoupon = fopen("database/List_coupon.txt", "r");
    if (!listCoupon) {
        printf("File tidak ada.\n");
        return;
    }

    char storedCoupon[MAX_COUPON_LENGTH];
    int storedDiscount;
    int found = 0;
    long int position;
    
    // Dekripsi kupon yang diinput
    
    decrypt(coupon);
    
    // Mencari kupon di database
    while (!feof(listCoupon)) {
        position = ftell(listCoupon);
        fscanf(listCoupon, "%s %d", storedCoupon, &storedDiscount);
        if (strcmp(coupon, storedCoupon) == 0) {
            fseek(listCoupon, position, SEEK_SET);
            discount = storedDiscount;
            found = 1;
            break;
        }
    }

    fclose(listCoupon);

    if (found) {
        printf("Selamat! Anda mendapatkan diskon sebesar %d persen\n", discount);
        spaceToContinue();
    } else {
        printf("Kode kupon tidak valid.\n");
        spaceToContinue();
    }
    return discount;
}

int kupon(char *coupon) {
	printf("Masukkan kode kupon: ");
	scanf("%s", coupon);
    int discount = readCoupon(coupon, discount);
    
    int potongan = discount;
    
    return potongan;
}

void checkCoupon (char *username) {
	FILE *couponList;
    couponList = fopen("database/List_coupon.txt", "r");
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
    	encrypt(storedCoupon);
        printf("Kode Kupon: %s | Diskon: %d ", storedCoupon, storedDiscount);
    }

    fclose(couponList);
}

/* LOGIN HISTORY */

void addLoginHistory(struct LoginHistory **head, const char *username) {
    // Membuat simpul baru untuk entri login
    struct LoginHistory *newLogin = (struct LoginHistory *)malloc(sizeof(struct LoginHistory));
    if (newLogin == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Mengisi data entri login
    strncpy(newLogin->username, username, sizeof(newLogin->username) - 1);
    newLogin->username[sizeof(newLogin->username) - 1] = '\0';
    newLogin->loginTime = time(NULL);
    newLogin->next = NULL;

    // Menambahkan entri login ke linked list
    if (*head == NULL) {
        *head = newLogin;
    } else {
        struct LoginHistory *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newLogin;
    }
}

// Fungsi untuk mencetak semua entri riwayat login
void printLoginHistory(struct LoginHistory *head) {
    printf("Login History:\n");
    while (head != NULL) {
        printf("Username: %s, Login Time: %s", head->username, asctime(localtime(&head->loginTime)));
        head = head->next;
    }
}

// Fungsi untuk membebaskan memori yang dialokasikan untuk linked list
void freeLoginHistory(struct LoginHistory *head) {
    while (head != NULL) {
        struct LoginHistory *temp = head;
        head = head->next;
        free(temp);
    }
}
