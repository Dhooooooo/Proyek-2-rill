#ifndef Hafidz_h
#define Hafidz_h

#include <time.h>
#define MAX_COUPON_LENGTH 10

// Struktur data untuk menyimpan entri riwayat login
struct LoginHistory {
    char username[50];
    time_t loginTime;
    struct LoginHistory *next;
};

/* COUPON */

// Fungsi untuk melakukan readCoupon
int readCoupon(char *coupon, int discount);

// Fungsi untuk memanggil fitur kupon
int kupon(char *coupon);

// Prosedur untuk melakukan cek kupon
void checkCoupon (char *username);

/* LOGIN HISTORY */

// Fungsi untuk menambahkan entri riwayat login baru ke linked list
void addLoginHistory(struct LoginHistory **head, const char *username);

// Fungsi untuk mencetak semua entri riwayat login
void printLoginHistory(struct LoginHistory *head);

// Fungsi untuk membebaskan memori yang dialokasikan untuk linked list
void freeLoginHistory(struct LoginHistory *head);

#endif
