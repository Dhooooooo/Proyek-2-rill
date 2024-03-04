#include <stdio.h>
#include <stdlib.h> // Untuk menggunakan fungsi system

// Deklarasi fungsi-fungsi untuk setiap jenis top up
void topup_listrik();
void topup_air();
void topup_pulsa();

int main() {
    int choice;
    char lanjut;

    do {
        // Menu utama
        printf("Selamat datang di layanan top up!\n");
        printf("Pilih jenis top up yang Anda inginkan:\n");
        printf("1. Top Up Listrik\n");
        printf("2. Top Up Air\n");
        printf("3. Top Up Pulsa\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);

        // Membersihkan layar
        system("cls"); // Untuk Windows
        //system("clear"); // Untuk Unix/Linux

        // Memanggil fungsi sesuai pilihan
        switch(choice) {
            case 1:
                topup_listrik();
                break;
            case 2:
                topup_air();
                break;
            case 3:
                topup_pulsa();
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

        // Menanyakan apakah pengguna ingin melanjutkan atau tidak
        printf("Apakah Anda ingin kembali ke menu utama? (y/n): ");
        scanf(" %c", &lanjut);

        // Membersihkan layar
        system("cls"); // Untuk Windows
        //system("clear"); // Untuk Unix/Linux
    } while (lanjut == 'y' || lanjut == 'Y');

    printf("Terima kasih telah menggunakan layanan kami. Sampai jumpa lagi!\n");

    return 0;
}

// Definisi fungsi untuk top up listrik
void topup_listrik() {
    float jumlah, token;
    printf("Masukkan ID token listrik anda: ");
    scanf("%f", &token);
    printf("Masukkan jumlah token listrik yang ingin Anda beli: ");
    scanf("%f", &jumlah);
    printf("Anda telah berhasil melakukan top up listrik sebesar %.2f kWh.\n", jumlah);
}

// Definisi fungsi untuk top up air
void topup_air() {
    float jumlah;
    printf("Masukkan jumlah meter air yang ingin Anda isi: ");
    scanf("%f", &jumlah);
    printf("Anda telah berhasil melakukan top up air sebesar %.2f M3.\n", jumlah);
}

// Definisi fungsi untuk top up pulsa
void topup_pulsa() {
    float jumlah, nomor;
    printf("Masukkan nomor yang anda tuju: ");
    scanf("%f", &nomor);
    printf("Masukkan jumlah pulsa yang ingin Anda isi: ");
    scanf("%f", &jumlah);
    printf("Anda telah berhasil melakukan top up pulsa sebesar Rp%.2f.\n", jumlah);
}

