#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../payPrim.h"
#include "../Hafidz.h"

Tiket tiket;

/* COUPON */

int readCoupon(char *coupon, int discount) {
    FILE *listCoupon;
    listCoupon = fopen("database/List_coupon.txt", "r");
    if (!listCoupon) {
        printf("File tidak ada.\n");
        return;
    }

    char storedCoupon[MAX_COUPON_LENGTH];
    int storedDiscount;
    int found = 0;
    long int position;
    
    // Dekripsi kupon yang diinput
    
    decrypt(coupon);
    
    // Mencari kupon di database
    while (!feof(listCoupon)) {
        position = ftell(listCoupon);
        fscanf(listCoupon, "%s %d", storedCoupon, &storedDiscount);
        if (strcmp(coupon, storedCoupon) == 0) {
            fseek(listCoupon, position, SEEK_SET);
            discount = storedDiscount;
            found = 1;
            break;
        }
    }

    fclose(listCoupon);

    if (found) {
        printf("Selamat! Anda mendapatkan diskon sebesar %d persen\n", discount);
        spaceToContinue();
    } else {
        printf("Kode kupon tidak valid.\n");
        spaceToContinue();
    }
    return discount;
}

int kupon(char *coupon) {
	printf("Masukkan kode kupon: ");
	scanf("%s", coupon);
    int discount = readCoupon(coupon, discount);
    
    int potongan = discount;
    
    return potongan;
}

void checkCoupon (char *username) {
	FILE *couponList;
    couponList = fopen("database/List_coupon.txt", "r");
    if (!couponList) {
        printf("File tidak ada.\n");
        return;
    }

    char storedCoupon[MAX_COUPON_LENGTH];
    int storedDiscount;

    printf("\nLIST COUPON\n");
    printf("============\n");
    
    // Menampilkan kupon yang ada di database
    while (fscanf(couponList, "%s %d", storedCoupon, &storedDiscount) != EOF) {
    	encrypt(storedCoupon);
        printf("Kode Kupon: %s | Diskon: %d ", storedCoupon, storedDiscount);
    }

    fclose(couponList);
}

/* LOGIN HISTORY */

void addLoginHistory(struct LoginHistory **head, const char *username) {
    // Membuat simpul baru untuk entri login
    struct LoginHistory *newLogin = (struct LoginHistory *)malloc(sizeof(struct LoginHistory));
    if (newLogin == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Mengisi data entri login
    strncpy(newLogin->username, username, sizeof(newLogin->username) - 1);
    newLogin->username[sizeof(newLogin->username) - 1] = '\0';
    newLogin->loginTime = time(NULL);
    newLogin->next = NULL;

    // Menambahkan entri login ke linked list
    if (*head == NULL) {
        *head = newLogin;
    } else {
        struct LoginHistory *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newLogin;
    }
}

// Fungsi untuk mencetak semua entri riwayat login
void printLoginHistory(struct LoginHistory *head) {
    printf("Login History:\n");
    while (head != NULL) {
        printf("Username: %s, Login Time: %s", head->username, asctime(localtime(&head->loginTime)));
        head = head->next;
    }
}

// Fungsi untuk membebaskan memori yang dialokasikan untuk linked list
void freeLoginHistory(struct LoginHistory *head) {
    while (head != NULL) {
        struct LoginHistory *temp = head;
        head = head->next;
        free(temp);
    }
}

/* KERETA */

void pilihJadwal(char* jadwal) {
    int pilihan = menuPilihJadwal();
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

    char seatLabel[10], status[50];
    while (fscanf(file, "%s %s", seatLabel, status) != EOF) {
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

    // Baca semua baris ke dalam array
    while (fgets(lines[lineCount], sizeof(lines[lineCount]), file)) {
        lineCount++;
    }

    rewind(file);

    // Tulis kembali ke file dengan perubahan
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
	clearScreen();
    int kelasPilihan = menuPilihKelas();

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
    
    char filename[40];
    sprintf(filename, "database/gerbong/gerbong%d_%s.txt", *gerbong, jadwal);

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
            break;
        } else {
            printf("Seat tidak valid atau sudah terisi. Silakan coba lagi.\n");
            spaceToContinue();
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
    if (pilihan == 1 && strcmp(tiket->jenisKereta, "Kereta Antar Kota") == 0) {
        char filename[40];
    	sprintf(filename, "database/gerbong/gerbong%d_%s.txt", tiket->gerbong, tiket->jadwal);
        pesanSeat(filename, tiket->seat, tiket->penumpang.nama);
    }
    return pilihan;
}

void pemesananKereta(char username[]) {
    int jenisKeretaPilihan;
    
    // Pilih jenis kereta
    clearScreen();
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
        pemesananKereta(username);
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
}

void listKeretaLokal() {
	printf("1. Stasiun Cicalengka\n");
	printf("2. Stasiun Kiaracondong\n");
	printf("3. Stasiun Bandung\n");
}

void listKeretaAntarKota() {
	printf("Stasiun awal: Manggarai | Stasiun akhir: Yogyakarta\n");
	printf("1. Stasiun Manggarai\n");
	printf("2. Stasiun Bandung\n");
	printf("3. Stasiun Yogyakarta\n");
}

int menuPilihKelas() {
	int kelasPilihan;
	printf("Pilih kelas:\n");
    printf("1. Kelas Eksekutif (Gerbong 1-3)\n");
    printf("2. Kelas Ekonomi (Gerbong 4-8)\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &kelasPilihan);
    return kelasPilihan;
}

int menuPilihJadwal() {
	int pilihan;
	printf("\nPilih jadwal:\n");
    printf("1. Pagi\n");
    printf("2. Siang\n");
    printf("3. Malam\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &pilihan);
    return pilihan;
}
