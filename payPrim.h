#ifndef payPrim_h
#define payPrim_h

#include <stdbool.h>

//enkrip Dekrip
void encrypt(char *text);
void decrypt(char *text);

//Akun Register Login
void registerUser(char *username, char *password, char *pin);
int loginUser(char *username, char *password, char *pin);
void modifyUser(char *username, char *newPassword, char *pin);

//Buat Menu
void waitNext();
void inputAkun(char *username, char *password, char *pin);
void inputEdit(char *username, char *password);
int displayMenu();
int displayMenuAfter();
int displayMenuPembelian();

// Tekan spasi untuk melanjutkan
void spaceToContinue();

/*HOTEL*/
// Fungsi untuk enkripsi plaintext/teks biasa diubah bentuknya
char *enkripsi(char plainText[]);

// Fungsi untuk dekripsi ciphertext/menubah teks yang sudah diubah bentuknya menjadi teks sebelum diubah
char *dekripsi(char cipherText[]);

// Fungsi untuk memvalidasi tanggal yang diinputkan, berlaku untuk tanggal Check In ataupun tanggal Check Out
bool *isTglValid(char *tanggal);

// Fungsi untuk memvalidasi tanggal yang diinputkan, berlaku untuk tanggal Check In ataupun tanggal Check Out
bool *isTglValid(char *tanggal);

// Fungsi untuk memvalidasi tanggalCheckOut
bool *isTglCheckOutValid(char *tanggalCheckIn, char *tanggalCheckOut);

// Fungsi untuk menginputkan tanggal Check In
char *inputTanggalCheckIn();

// Fungsi untuk menginputkan tanggal Check Out , tanggal Check In dibutuhkan untuk valdiasi tangal check out
char *inputTanggalCheckOut(char *tanggalCheckIn);

// Fungsi untuk mengetahui hari yang diinputkan hari ke berapa dalam satu tahun
int hariDalamTahun(char *tanggal);

// Fungsi untuk mengetahui total menginap berapa hari
int hitungHariMenginap(char *tanggalCheckIn, char *tanggalCheckOut);

// Fungsi untuk memberikan nomor kamar random
int kamar();

// Fungsi untuk memeriksa apakah nomor kamar sudah ada di dalam file
bool isKamarExists(int noKamar);

// Untuk menampilkan harga yang dipisahkan dengan .
void disHarga(int harga);

// Untuk menghitung ada berapa baris di file
int hitungBaris();

// Fungsi untuk memperbarui baris dengan nomor tertentu
void updateBaris(char *baris, int nomor);

// Prosedur untuk approval admin mana yang sudah berhasil mana yang belum
void adminApprove(int nomorDicari);

// Untuk tampilan yang dilihat oleh admin
void disPemesananAdmin();

// Prosedur ini untuk user memesan hotel
void pemesananHotel(char username[]);

// Prosedur untuk menampilkan pesanan ke user berdasarkan username
void disPemesananUser(char username[]);

#endif
