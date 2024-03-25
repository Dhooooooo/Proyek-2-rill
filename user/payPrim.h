#ifndef payPrim_h
#define payPrim_h

#include <stdbool.h>

/* modul yang dipakai di banyak header*/
// Tekan spasi untuk melanjutkan
void spaceToContinue();
// Untuk menampilkan harga yang dipisahkan dengan .
void disHarga(int harga);
// Fungsi untuk enkripsi plaintext/teks biasa diubah bentuknya
char *enkripsi(char plainText[]);
// Fungsi untuk dekripsi ciphertext/menubah teks yang sudah diubah bentuknya menjadi teks sebelum diubah
char *dekripsi(char cipherText[]);



//enkrip Dekrip
void encrypt(char *text);
void decrypt(char *text);

//Akun Register Login
void registerUser(char *username, char *password, char *pin);
int loginUser(char *username, char *password, char *pin);
void modifyPass(char *username, char *password);
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
void inputEditUser(char *username, char *password);
int displayMenu();
int displayMenuAfter();
int displayMenuPembelian();
int displayMenuProfil();
void clearScreen();


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

// Fungsi untuk melakukan readCoupon
int readCoupon(char *coupon, int discount);

// Fungsi untuk memanggil fitur kupon
int kupon(char *coupon);

// Prosedur untuk melakukan cek kupon
void checkCoupon (char *username[]);

/*TOPUP*/
void topUpSaldo(char *username, float amount);

#endif
