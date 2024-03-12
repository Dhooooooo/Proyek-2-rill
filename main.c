#include "coupon.h"

int main() { 
    char coupon[MAX_COUPON_LENGTH];
    int potongan;
    int harga;

    printf("Masukkan kode kupon: ");
    scanf("%s", coupon);
    
    // Menggunakan fungsi kupon untuk mendapatkan potongan harga
    potongan = kupon(coupon);
    
    return 0;
}

