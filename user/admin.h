#ifndef ADMIN_H
#define ADMIN_H

int mainMenu();
int menuadmin();
int transaksiHotel();
void createCoupon(char *coupon, int discount);
void displayCouponList();
void changeDiscount(char *coupon, int newDiscount);
void coupon();

// Fungsi untuk menampilkan file dari database
int transaksiPesawat();

#endif
