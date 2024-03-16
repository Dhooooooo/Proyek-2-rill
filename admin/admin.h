#ifndef ADMIN_H
#define ADMIN_H

int mainMenu();
int menuadmin();
int loginAdmin(char *username, char *password);
int menuAdmin();
void totalHotel();
void totalPulsa();
void createCoupon(char *coupon, int discount);
void displayCouponList();
void changeDiscount(char *coupon, int newDiscount);
void coupon();

#endif
