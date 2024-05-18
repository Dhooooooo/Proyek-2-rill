#include <stdio.h>
#include <string.h>
#include "kereta.h"

int main() {
    Tiket tiket;
    int jenisKeretaPilihan;
    
    // Pilih jenis kereta
    printf("Pilih Jenis Kereta:\n");
    printf("1. Kereta Lokal Bandung Raya\n");
    printf("2. Kereta Antar Kota\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &jenisKeretaPilihan);
    system("cls");

    // Input stasiun keberangkatan dan tujuan
    inputStasiun(&tiket, jenisKeretaPilihan);

    // Set jenis kereta
    if (jenisKeretaPilihan == 1) {
        strcpy(tiket.jenisKereta, "Kereta Lokal");
    } else if (jenisKeretaPilihan == 2) {
        strcpy(tiket.jenisKereta, "Kereta Antar Kota");
    } else {
        printf("Pilihan jenis kereta tidak valid.\n");
        return 1;
    }

    // Pilih jadwal
    pilihJadwal(tiket.jadwal);

    // Input data diri
    inputDataDiri(&tiket.penumpang);

    // Pilih seat jika kereta antar kota
    if (jenisKeretaPilihan == 2) {
        pilihSeat(tiket.seat, &tiket.gerbong, &tiket.penumpang, tiket.jadwal);
    }

    // Konfirmasi pembayaran
    system("cls");
    int konfirmasi = konfirmasiPembayaran(&tiket);
    if (konfirmasi == 1) {
        printf("Pembayaran berhasil. Tiket Anda telah dipesan.\n");
    } else {
        printf("Pemesanan dibatalkan.\n");
    }

    return 0;
}
