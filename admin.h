#ifndef admin_h
#define admin_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUPON_LENGTH 10
#define ENCRYPTION_KEY_LENGTH 8

void createCoupon(char *coupon, int discount);
void encryptCoupon(char *coupon);
void displayCouponList();
void changeDiscount(char *coupon, int newDiscount);

#endif
