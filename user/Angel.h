#ifndef Angel_h
#define Angel_h

#define MAX_LENGTH 100
#define ADMIN_FEE 1500

// Struktur untuk menyimpan informasi transaksi
typedef struct {
    int orderNumber;
    char username[MAX_LENGTH];
    char topupType[MAX_LENGTH];
    char lokasiAwal[20];
    char kotaTujuan[20];
    char jamKeberangkatan[6];
    char jamKedatangan[6];
//    char tglKeberangkatan;
    int jmlTiket; 
    char kelas[10];
    int seat;
    float originalPrice;
    float discount;
    float adminFee;
    float total;
    char status[MAX_LENGTH];
} Transaction;

// Struktur untuk menyimpan informasi penerbangan
typedef struct {
    int kode;
    char lokasiAwal[20];
    char kotaTujuan[20];
    char jamKeberangkatan[6];
    char jamKedatangan[6];
    int hargaEkonomi;
    int hargaBisnis;
} Penerbangan;

// Fungsi untuk menambahkan transaksi ke file HistoryPulsa.txt
//void addTransactionToFile(Transaction transaction);

// Fungsi untuk mendapatkan nomor antrian terbaru dari file admin.txt
int getLastOrderNumber();

// Fungsi untuk memanggil fitur 
//void pesanTiket(char *username, Penerbangan penerbangan[], int numPenerbangan);
void pembelianTiket(char *username);

//-------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------

// Struktur Node untuk Pohon Biner
struct Node {
    int hargaMenginap;   // Biaya kamar per malam
    int adminFee;   // Biaya admin
    int discount;   // Persentase diskon
    struct Node* left;
    struct Node* right;
};

// Fungsi untuk Menambahkan Node ke Pohon Biner
struct Node* insert(struct Node* root, int hargaMenginap, int adminFee, int discount);

// Fungsi untuk Mencari Diskon Berdasarkan Persentase
int calculateDiscount(int hargaMenginap, int adminFee, int potongan);

// Fungsi untuk Menghitung Total Biaya Transaksi
int calculateTotalCost(int hargaMenginap, int adminFee, int discount);

int calculate(int potongan, int *hargaMenginap);

extern char char_set[];
extern int mod;
extern char dbsPemesanan[];

void getUserRole(const char *username, char *role);

void printTransaction(const Transaction* transaction);
Penerbangan* cariPenerbangan(Penerbangan penerbangan[], int numPenerbangan, int kodePenerbangan);
void printFileContent(const char *filename);

//void printDecryptedFile(char *username);

#endif
