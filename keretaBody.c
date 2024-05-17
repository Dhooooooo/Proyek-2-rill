#include <stdio.h>
#include <string.h>
#include "kereta.h"

void pilihJadwal(char* jadwal) {
    printf("Pilih jadwal:\n");
    printf("1. Pagi\n");
    printf("2. Siang\n");
    printf("3. Malam\n");
    int pilihan;
    scanf("%d", &pilihan);
    switch(pilihan) {
        case 1:
            strcpy(jadwal, "Pagi");
            break;
        case 2:
            strcpy(jadwal, "Siang");
            break;
        case 3:
            strcpy(jadwal, "Malam");
            break;
        default:
            printf("Pilihan tidak valid, memilih jadwal Pagi.\n");
            strcpy(jadwal, "Pagi");
            break;
    }
}

void inputDataDiri(Penumpang* penumpang) {
    printf("Masukkan nama: ");
    scanf("%s", penumpang->nama);
    
    while (1) {
        printf("Masukkan NIK (16 angka): ");
        scanf("%s", penumpang->nik);

        if (strlen(penumpang->nik) == 16) {
            int valid = 1;
            int i = 0;
            for (i = 0; i < 16; i++) {
                if (penumpang->nik[i] < '0' || penumpang->nik[i] > '9') {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                break;
            } else {
                printf("NIK harus berupa 16 angka.\n");
            }
        } else {
            printf("NIK harus tepat 16 angka.\n");
        }
    }
}

void pilihSeat(char* seat, int* gerbong) {
    int kelasPilihan;

    printf("Pilih kelas:\n");
    printf("1. Kelas Eksekutif (Gerbong 1-3)\n");
    printf("2. Kelas Ekonomi (Gerbong 4-8)\n");
    scanf("%d", &kelasPilihan);

    if (kelasPilihan == 1) {
        printf("Pilih gerbong (1-3): ");
        scanf("%d", gerbong);
        if (*gerbong < 1 || *gerbong > 3) {
            printf("Gerbong tidak valid untuk kelas eksekutif.\n");
            pilihSeat(seat, gerbong);
            return;
        }
    } else if (kelasPilihan == 2) {
        printf("Pilih gerbong (4-8): ");
        scanf("%d", gerbong);
        if (*gerbong < 4 || *gerbong > 8) {
            printf("Gerbong tidak valid untuk kelas ekonomi.\n");
            pilihSeat(seat, gerbong);
            return;
        }
    } else {
               printf("Pilihan kelas tidak valid.\n");
        pilihSeat(seat, gerbong);
        return;
    }

    printf("Pilih seat (contoh: A1, B2, C3, ...): ");
    scanf("%s", seat);
}

int validasiStasiun(char* stasiun, int jenisKeretaPilihan) {
    if (jenisKeretaPilihan == 1) {
        if (strcmp(stasiun, "Cicalengka") == 0 || strcmp(stasiun, "Kiaracondong") == 0 || strcmp(stasiun, "Bandung") == 0) {
            return 1;
        }
    } else if (jenisKeretaPilihan == 2) {
        if (strcmp(stasiun, "Bandung") == 0 || strcmp(stasiun, "Manggarai") == 0 || strcmp(stasiun, "Yogyakarta") == 0) {
            return 1;
        }
    }
    return 0;
}

void konfirmasiPembayaran(Tiket* tiket) {
    printf("\nKonfirmasi Pembayaran:\n");
    printf("Nama: %s\n", tiket->penumpang.nama);
    printf("NIK: %s\n", tiket->penumpang.nik);
    printf("Stasiun Keberangkatan: %s\n", tiket->stasiunKeberangkatan);
    printf("Stasiun Tujuan: %s\n", tiket->stasiunTujuan);
    printf("Jadwal: %s\n", tiket->jadwal);
    if (strcmp(tiket->jenisKereta, "Kereta Antar Kota") == 0) {
        printf("Gerbong: %d\n", tiket->gerbong);
        printf("Seat: %s\n", tiket->seat);
    }
    printf("Jenis Kereta: %s\n", tiket->jenisKereta);
    printf("Pembayaran berhasil. Tiket Anda telah dipesan.\n");
}

