#include <stdio.h>
#include <string.h>
#include "kereta.h"

void pilihJadwal(char* jadwal) {
    printf("\nPilih jadwal:\n");
    printf("1. Pagi\n");
    printf("2. Siang\n");
    printf("3. Malam\n");
    printf("Masukkan pilihan: ");
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
            printf("Pilihan tidak valid.\n");
            spaceToContinue();
            break;
    }
}

void inputDataDiri(Penumpang* penumpang) {
    printf("\nMasukkan nama: ");
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

int validasiSeat(char* seat, int kelasPilihan) {
    char seatColumn;
    int seatRow;
    if (sscanf(seat, "%c%d", &seatColumn, &seatRow) != 2) {
        return 0;
    }
    
    if (kelasPilihan == 1) {
        // Kelas Eksekutif: A1 - D12
        if (seatColumn >= 'A' && seatColumn <= 'D' && seatRow >= 1 && seatRow <= 12) {
            return 1;
        }
    } else if (kelasPilihan == 2) {
        // Kelas Ekonomi: A1 - D15
        if (seatColumn >= 'A' && seatColumn <= 'D' && seatRow >= 1 && seatRow <= 15) {
            return 1;
        }
    }
    return 0;
}

int cekKetersediaanSeat(const char* filename, const char* seat) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char seatLabel[10], status[50];
        sscanf(line, "%s %s", seatLabel, status);
        if (strcmp(seatLabel, seat) == 0) {
            fclose(file);
            return strcmp(status, "<empty>") == 0;
        }
    }
    fclose(file);
    return 0;
}

void pesanSeat(const char* filename, const char* seat, const char* namaPenumpang) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char lines[100][100];
    int lineCount = 0;
    while (fgets(lines[lineCount], sizeof(lines[lineCount]), file)) {
        lineCount++;
    }

    rewind(file);
    int i;
    for (i = 0; i < lineCount; i++) {
        char seatLabel[10], status[50];
        sscanf(lines[i], "%s %s", seatLabel, status);
        if (strcmp(seatLabel, seat) == 0) {
            fprintf(file, "%s %s\n", seatLabel, namaPenumpang);
        } else {
            fprintf(file, "%s", lines[i]);
        }
    }
    
    fclose(file);
}

void pilihSeat(char* seat, int* gerbong, Penumpang* penumpang, const char* jadwal) {
    int kelasPilihan;
	
	system("cls");
    printf("Pilih kelas:\n");
    printf("1. Kelas Eksekutif (Gerbong 1-3)\n");
    printf("2. Kelas Ekonomi (Gerbong 4-8)\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &kelasPilihan);

    if (kelasPilihan == 1) {
        printf("\nPilih gerbong (1-3): ");
        scanf("%d", gerbong);
        if (*gerbong < 1 || *gerbong > 3) {
            printf("Gerbong tidak valid untuk kelas eksekutif.\n");
            spaceToContinue();
            pilihSeat(seat, gerbong, penumpang, jadwal);
            return;
        }
    } else if (kelasPilihan == 2) {
        printf("\nPilih gerbong (4-8): ");
        scanf("%d", gerbong);
        if (*gerbong < 4 || *gerbong > 8) {
            printf("Gerbong tidak valid untuk kelas ekonomi.\n");
            spaceToContinue();
            pilihSeat(seat, gerbong, penumpang, jadwal);
            return;
        }
    } else {
        printf("Pilihan kelas tidak valid.\n");
        spaceToContinue();
        pilihSeat(seat, gerbong, penumpang, jadwal);
        return;
    }
    
    char filename[20];
    sprintf(filename, "database/gerbong%d_%s.txt", *gerbong, jadwal);

    while (1) {
    	if (kelasPilihan == 1) {
    		printf("\nTerdapat seat kolom A-D dan baris 1-12 di gerbong %d.\n", *gerbong);
		}
		else {
			printf("\nTerdapat seat kolom A-D dan baris 1-15 di gerbong %d.\n", *gerbong);
		}
		
        printf("Pilih seat (contoh: A1, B2, C3, ...): ");
        scanf("%s", seat);
        
        if (validasiSeat(seat, kelasPilihan) && cekKetersediaanSeat(filename, seat)) {
            pesanSeat(filename, seat, penumpang->nama);
            break;
        } else {
            printf("Seat tidak valid atau sudah terisi. Silakan coba lagi.\n");
            void spaceToContinue();
        }
    }
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

void inputStasiun(Tiket* tiket, int jenisKeretaPilihan) {
    while (1) {
    	if (jenisKeretaPilihan == 1) {
    		listKeretaLokal();
		}
		else {
			listKeretaAntarKota();
		}
		
        printf("Masukkan nama stasiun keberangkatan: ");
        scanf("%s", tiket->stasiunKeberangkatan);
        printf("Masukkan nama stasiun tujuan: ");
        scanf("%s", tiket->stasiunTujuan);
        
        if (validasiStasiun(tiket->stasiunKeberangkatan, jenisKeretaPilihan) && validasiStasiun(tiket->stasiunTujuan, jenisKeretaPilihan)) {
            break;
        } else {
            printf("Stasiun yang dipilih tidak valid untuk jenis kereta ini. Silakan coba lagi.\n");
            spaceToContinue();
        }
    }
}

void kosongkanSeat(const char* filename, const char* seat) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char lines[100][100];
    int lineCount = 0;
    while (fgets(lines[lineCount], sizeof(lines[lineCount]), file)) {
        lineCount++;
    }

    rewind(file);
    int i;
    for (i = 0; i < lineCount; i++) {
        char seatLabel[10], status[50];
        sscanf(lines[i], "%s %s", seatLabel, status);
        if (strcmp(seatLabel, seat) == 0) {
            fprintf(file, "%s <empty>\n", seatLabel);
        } else {
            fprintf(file, "%s", lines[i]);
        }
    }

    fclose(file);
}

int konfirmasiPembayaran(Tiket* tiket) {
    printf("Konfirmasi Pembayaran:\n");
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
    printf("Apakah anda ingin melanjutkan pemesanan?\n");
    printf("1. Iya\n");
    printf("2. Tidak\n");
    printf("Masukkan pilihan: ");
    int pilihan;
    scanf("%d", &pilihan);
    if (pilihan == 2 && strcmp(tiket->jenisKereta, "Kereta Antar Kota") == 0) {
        char filename[20];
    	sprintf(filename, "database/gerbong%d_%s.txt", tiket->gerbong, tiket->jadwal);
        kosongkanSeat(filename, tiket->seat);
    }
    return pilihan;
}

void listKeretaLokal() {
	printf("1. Stasiun Cicalengka\n");
	printf("2. Stasiun Bandung\n");
	printf("3. Stasiun Padalarang\n");
}

void listKeretaAntarKota() {
	printf("Stasiun awal: Manggarai | Stasiun akhir: Yogyakarta\n");
	printf("1. Stasiun Manggarai\n");
	printf("2. Stasiun Bandung\n");
	printf("3. Stasiun Yogyakarta\n");
}

void spaceToContinue() {
	printf("\n\nTekan spasi untuk melanjutkan");
    while(getch() != ' '); // menunggu user menekan spasi untuk melanjutkan
    system("cls");
}
