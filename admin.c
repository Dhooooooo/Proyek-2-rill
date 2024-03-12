#include "admin.h"

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
