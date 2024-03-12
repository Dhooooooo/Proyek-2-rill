#ifndef coupon_h
#define coupon_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUPON_LENGTH 10
#define ENCRYPTION_KEY_LENGTH 8

void readCoupon(char *coupon, int *discount);
void decryptCoupon(char *coupon);
int kupon(char *coupon);

#endif
