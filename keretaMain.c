#include <stdio.h>
#include <string.h>
#include "kereta.h"

int main() {
    Tiket tiket;
    int jenisKeretaPilihan;

    // Pilih jenis kereta
    printf("Pilih jenis kereta:\n");
    printf("1. Kereta Lokal (Bandung Raya)\n");
    printf("2. Kereta Antar Kota\n");
    scanf("%d", &jenisKeretaPilihan);

    // Input stasiun keberangkatan dan tujuan
    printf("Masukkan stasiun keberangkatan: ");
    scanf("%s", tiket.stasiunKeberangkatan);
    printf("Masukkan stasiun tujuan: ");
    scanf("%s", tiket.stasiunTujuan);

    // Validasi jenis kereta berdasarkan stasiun tujuan
    if (jenisKeretaPilihan == 1) {
        strcpy(tiket.jenisKereta, "Kereta Lokal");
        if (!validasiStasiun(tiket.stasiunKeberangkatan, jenisKeretaPilihan) || !validasiStasiun(tiket.stasiunTujuan, jenisKeretaPilihan)) {
            printf("Stasiun yang dipilih tidak valid untuk Kereta Lokal.\n");
            return 1;
        }
    } else if (jenisKeretaPilihan == 2) {
        strcpy(tiket.jenisKereta, "Kereta Antar Kota");
        if (!validasiStasiun(tiket.stasiunKeberangkatan, jenisKeretaPilihan) || !validasiStasiun(tiket.stasiunTujuan, jenisKeretaPilihan)) {
            printf("Stasiun yang dipilih tidak valid untuk Kereta Antar Kota.\n");
            return 1;
        }
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
        pilihSeat(tiket.seat, &tiket.gerbong);
    }

    // Konfirmasi pembayaran
    konfirmasiPembayaran(&tiket);

    return 0;
}

