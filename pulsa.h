#ifndef PULSA_H
#define PULSA_H

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
void printTransaction(const Transaction* transaction);

char* encrypt(const char* plainText);
char* decrypt(const char* cipherText);

char* findProvider(char* phoneNumber, Provider providers[], int numProviders);
void addTransactionToFile(Transaction transaction);
int getLastOrderNumber();
void disHarga(int harga);
void printDecryptedFile(char* filename);

void pembelianPulsa(char *username);


#endif /* TRANSACTION_H */

