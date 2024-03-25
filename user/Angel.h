#ifndef Angel_h
#define Angel_h

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

/*TOPUP*/
void topUpSaldo(char *username, float amount);

#endif
