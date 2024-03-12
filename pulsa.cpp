#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pulsa.h"

// Function to create a transaction
Transaction createTransaction(int orderNumber, const char* username, const char* topupType, const char* note, float originalPrice, float discount, float adminFee, float total, const char* status) {
    Transaction transaction;
    transaction.orderNumber = orderNumber;
    strcpy(transaction.username, username);
    strcpy(transaction.topupType, topupType);
    strcpy(transaction.note, note);
    transaction.originalPrice = originalPrice;
    transaction.discount = discount;
    transaction.adminFee = adminFee;
    transaction.total = total;
    strcpy(transaction.status, status);
    return transaction;
}

// Function to print a transaction
void printTransaction(const Transaction* transaction) {
    printf("Order Number: %d\n", transaction->orderNumber);
    printf("Username: %s\n", transaction->username);
    printf("Topup Type: %s\n", transaction->topupType);
    printf("Note: %s\n", transaction->note);
    printf("Original Price: %.2f\n", transaction->originalPrice);
    printf("Discount: %.2f\n", transaction->discount);
    printf("Admin Fee: %.2f\n", transaction->adminFee);
    printf("Total: %.2f\n", transaction->total);
    printf("Status: %s\n", transaction->status);
}

char char_set[] = "1qazZAQ2wsxXSW3edcCDE4rfvVFR5tgbBGT6yhnNHY7ujmMJU8ikKI9olLOpP";
int mod = sizeof(char_set);

char* enkripsi(char plainText[], int length) {	
    static char enkrip[100];
    int i, j;
    for (i = 0; i < length; i++) {
    	bool isPlainInChar = false;
        int index = 0;
        for (j = 0; j < strlen(char_set); j++) {
            if (char_set[j] == plainText[i]) {
            	isPlainInChar = true;
                int hasil = (index * 3 + 7) % mod;
                enkrip[i] = char_set[hasil];
                break;
            }
            index++;
        }
        if(!isPlainInChar){
        	enkrip[i] = plainText[i];
		}
    }
    return enkrip;
}

char* dekripsi(char cipherText[]) {
    static char dekrip[100];
    int i,j;
    for (i = 0; i < strlen(cipherText); i++) {
    	bool isCipherInChar = false;
        int index = 0;
        for (j = 0; j < strlen(char_set); j++) {
            if (char_set[j] == cipherText[i]) {
            	isCipherInChar = true;
                while ((index - 7) % 3 != 0)
                    index += mod;
                int hasil = (index - 7) / 3;
                dekrip[i] = char_set[hasil];
                break;
            }
            index++;
        }
        if(!isCipherInChar){
        	dekrip[i] = cipherText[i];
		}
    }
    return dekrip;
}

// Fungsi untuk mencari provider berdasarkan kode area
char* findProvider(char* phoneNumber, Provider providers[], int numProviders) {
    char areaCode[5];
    strncpy(areaCode, phoneNumber, 4); // Mengambil 4 digit pertama sebagai kode area
    areaCode[4] = '\0'; // Menambahkan null terminator
	
    int i;
    for (i = 0; i < numProviders; ++i) {
        if (strcmp(providers[i].code, areaCode) == 0) {
            return providers[i].name; // Mengembalikan nama provider
        }
    }
    return "Unknown"; // Jika provider tidak ditemukan
}

// Fungsi untuk menambahkan transaksi ke file admin.txt
void addTransactionToFile(Transaction transaction) {
    FILE *file = fopen("admin.txt", "a");
   if (file == NULL) {
        printf("Gagal membuka file admin.txt untuk penulisan.\n");
        return;
    }

    char prompt[MAX_LENGTH]; // Deklarasi variabel prompt
    sprintf(prompt, "%d,%s,%s,%s,%f,%d,%f,%f,%s,\n", 
        transaction.orderNumber, transaction.username, transaction.topupType,
        transaction.note, transaction.originalPrice, transaction.discount,
        transaction.adminFee, transaction.total, transaction.status);

    char* enkripsiPesanan = enkripsi(prompt, strlen(prompt)); // Enkripsi data sebelum ditulis ke file

    fprintf(file, "%s", enkripsiPesanan); // Tulis data yang sudah dienkripsi ke file
    fclose(file);
}


// Fungsi untuk mendapatkan nomor antrian terbaru dari file admin.txt
int getLastOrderNumber() {
    FILE *file = fopen("admin.txt", "rb");
    if (file == NULL) {
        printf("Gagal membuka file admin.txt.\n");
        return 0; // Jika file tidak ditemukan, mengembalikan nomor 0
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    int numLines = fileSize / MAX_LENGTH;

    fclose(file);
    return numLines + 1; // Mengembalikan nomor antrian terbaru
}

void disHarga(int harga) {
   if (harga < 1000) {
       printf("%d", harga);
       return;
   }
   disHarga(harga / 1000);
   printf(".%03d", harga % 1000);
}


void printDecryptedFile(char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file %s.\n", filename);
        return;
    }
	
    printf("+-----------------------------------------------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-12s | %-12s | %-12s | %-10s | %-10s| %-6s | %-12s | %-12s |\n", 
	        "No", " Username", "Pembelian", "  Catatan", "Harga Asli", "Diskon", "Biaya Admin", "   Total", " Keterangan");
    printf("|-----+--------------+--------------+--------------+------------+-----------+-------------+--------------+--------------|\n");
	
	char line[MAX_LENGTH];
	while (fgets(line, sizeof(line), file)) {
    	char *dekripsiLine = dekripsi(line);
    	
    	char *orderNumber = strtok(dekripsiLine, ",");
    	char *username = strtok(NULL, ",");
    	char *topupType = strtok(NULL, ",");
    	char *note = strtok(NULL, ",");
    	char *originalPrice = strtok(NULL, ",");
    	char *discount = strtok(NULL, ",");
    	char *adminFee = strtok(NULL, ",");
    	char *total = strtok(NULL, ",");
    	char *status = strtok(NULL, ",");
	
	    printf("| %-3s | %-12s | %-12s | %-12s |",
		orderNumber, username, topupType, note);
		printf(" Rp. ");
		disHarga(atoi(originalPrice));
		printf("\t| %-8s%% |", discount);
		printf(" Rp. ");
		disHarga(atoi(adminFee)); 
		printf("\t  |");
		printf(" Rp. ");
		disHarga(atoi(total));
		printf("\t | %-12s |\n", status);
	}

	printf("+-----------------------------------------------------------------------------------------------------------------------+\n");	

    fclose(file);
}

