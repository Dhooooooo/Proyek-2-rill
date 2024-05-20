#ifndef Hafidz_h
#define Hafidz_h

#include <time.h>
#define MAX_COUPON_LENGTH 10

// Struktur data untuk menyimpan entri riwayat login
struct LoginHistory {
    char username[50];
    time_t loginTime;
    struct LoginHistory *next;
};

typedef struct {
    char nama[50];
    char nik[20];
} Penumpang;

typedef struct {
    char stasiunKeberangkatan[50];
    char stasiunTujuan[50];
    char jenisKereta[20];
    char jadwal[20];
    char seat[10];
    int gerbong;
    int tarif;
    char tanggal[11];
    int kelas;
    int potongan;
    int total;
    Penumpang penumpang;
} Tiket;

/* COUPON */

// Fungsi untuk melakukan readCoupon
int readCoupon(char *coupon, int discount);

// Fungsi untuk memanggil fitur kupon
int kupon(char *coupon);

// Prosedur untuk melakukan cek kupon
void checkCoupon (char *username);

/* LOGIN HISTORY */

// Fungsi untuk menambahkan entri riwayat login baru ke linked list
void addLoginHistory(struct LoginHistory **head, const char *username);

// Fungsi untuk mencetak semua entri riwayat login
void printLoginHistory(struct LoginHistory *head);

// Fungsi untuk membebaskan memori yang dialokasikan untuk linked list
void freeLoginHistory(struct LoginHistory *head);

/* KERETA */

// Prosedur untuk memilih jadwal kereta
void pilihJadwal(char* jadwal);

// Prosedur untuk melakukan input data diri dalam pemesanan tiket kereta
void inputDataDiri(Penumpang* penumpang);

// Prosedur untuk memilih seat di kereta antar kota
void pilihSeat(char* seat, int* gerbong, Penumpang* penumpang, const char* jadwal);

// Fungsi untuk mengecek stasiun yang diinput sesuai dengan stasiun yang tersedia
int validasiStasiun(char* stasiun, int jenisKeretaPilihan);

// Prosedur untuk melakukan input stasiun keberangkatan dan stasiun tujuan
void inputStasiun(Tiket* tiket, int jenisKeretaPilihan);

// Fungsi untuk melakukan konfirmasi pembayaran
int konfirmasiPembayaran(Tiket* tiket);

// Fungsi untuk mengecek seat yang diinput sesuai dengan seat yang tersedia di gerbong
int validasiSeat(char* seat, int kelasPilihan);

// Fungsi untuk mengecek seat yang diinput masih kosong atau sudah terisi
int cekKetersediaanSeat(const char* filename, const char* seat);

// Prosedur untuk melakukan pemesanan seat
void pesanSeat(const char* filename, const char* seat, const char* namaPenumpang);

// Prosedur untuk memulai pemesanan tiket kereta
void pemesananKereta(char username[]);

bool isLeapYear(int year);
bool isValidDate(int day, int month, int year);
bool isDateNotInPast(int day, int month, int year);
void inputTanggal(char* tanggal);
void tentukanTarif(Tiket* tiket);
void simpanRiwayat(Tiket* tiket);
void tampilkanRiwayatPembelian();

/* MENU */
void listKeretaLokal();
void listKeretaAntarKota();
int menuPilihKelas();
int menuPilihJadwal();

#endif
