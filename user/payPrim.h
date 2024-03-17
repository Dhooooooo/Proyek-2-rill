#ifndef payPrim_h
#define payPrim_h

#include <stdbool.h>

//enkrip Dekrip
void encrypt(char *text);
void decrypt(char *text);

//Akun Register Login
void registerUser(char *username, char *password, char *pin);
int loginUser(char *username, char *password, char *pin);
void modifyPass(char *username, char *newPassword);
void modifyPin(char *username, char *newPin);
void modifyUser(char *username, char *password);
void showInfo(char *username);

//Per e-Wallet an
void dataSaldoNew(char *username);
int isSaldoCukup(char *username, float totHarga);
int confirmPay(char *username);

//Buat Menu
void waitNext();
void title();
void inputAkun(char *username, char *password, char *pin);
void inputEdit(char *username, char *password);
void inputEditPin(char *username, char *newPin);
void inputEditUser(char *newUsername, char *password);
int displayMenu();
int displayMenuAfter();
int displayMenuPembelian();
int displayMenuProfil();
void clearScreen();

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

/*PULSA*/

#define MAX_LENGTH 100
#define ADMIN_FEE 1500

// Define struct for Transaction
typedef struct { 
    int orderNumber;
    char username[MAX_LENGTH];
    char topupType[MAX_LENGTH];
    char note[MAX_LENGTH];
    float originalPrice;
    int discount;
    float adminFee;
    float total;
    char status[MAX_LENGTH];
} Transaction;

// Define struct for Provider
typedef struct {
    char name[MAX_LENGTH];
    char code[5];
} Provider;

// Function prototypes
Transaction createTransaction(int orderNumber, const char* username, const char* topupType, const char* note, float originalPrice, float discount, float adminFee, float total, const char* status);

// Fungsi untuk mencari provider berdasarkan kode are
char* findProvider(char* phoneNumber, Provider providers[], int numProviders);

// Fungsi untuk menambahkan transaksi ke file HistoryPulsa.txt
void addTransactionToFile(Transaction transaction);

// Fungsi untuk mendapatkan nomor antrian terbaru dari file admin.txt
int getLastOrderNumber();

// Fungsi untuk menampilkan file dari database
void printDecryptedFile(char *username);

// Fungsi untuk memanggil fitur 
void pembelianPulsa(char *username);

/*COUPON*/

#define MAX_COUPON_LENGTH 10

// Prosedur untuk melakukan 
void readCoupon(char *coupon, int discount);

// Prosedur untuk memanggil fitur kupon
int kupon(char *coupon);

// Prosedur untuk melakukan cek kupon
void checkCoupon (char username[]);

/*TOPUP*/
void topUpSaldo(char *username, float amount);

#endif
