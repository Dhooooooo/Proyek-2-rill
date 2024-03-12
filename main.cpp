#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pulsa.h"

int main() {
    // Mendapatkan nomor antrian terbaru
    int orderNumber = getLastOrderNumber();

    // Membaca data provider dari file pulsa.txt
    FILE *pulsaFile = fopen("pulsa.txt", "r");
    if (pulsaFile == NULL) {
        printf("Gagal membuka file pulsa.txt.\n");
        return 1;
    }

    int numProviders = 0;
    Provider providers[100]; // Maksimum 100 provider dalam database
    while (fscanf(pulsaFile, "%s %s", providers[numProviders].name, providers[numProviders].code) != EOF) {
        numProviders++;
    }
    fclose(pulsaFile);

    // Mendapatkan nomor telepon dari pengguna
    char phoneNumber[MAX_LENGTH];
    printf("Masukkan nomor telepon: ");
    scanf("%s", phoneNumber);

    // Mencari provider berdasarkan kode area nomor telepon
    char*providerName = findProvider(phoneNumber, providers, numProviders);
    printf("provider : %s\n", providerName);

    // Membuat transaksi dengan nilai default
    Transaction transaction;
    transaction.orderNumber = orderNumber;
    strcpy(transaction.topupType, "pulsa");
    strcpy(transaction.status, "progress");

    // Mengisi detail transaksi
    strcpy(transaction.username, phoneNumber); // Nomor telepon digunakan sebagai username
    strcpy(transaction.note, providerName); // Provider yang ditemukan digunakan sebagai catatan
    printf("Masukkan jumlah yang diinginkan: ");
    scanf("%f", &transaction.originalPrice);
    printf("Masukkan kode diskon (jika tidak ada, ketik 0): ");
    scanf("%f", &transaction.discount);

   	// Menghitung total biaya
	transaction.adminFee = ADMIN_FEE;
	transaction.total = transaction.originalPrice + transaction.discount + transaction.adminFee;

    // Menambahkan transaksi ke file admin.txt
    addTransactionToFile(transaction);

    printf("Transaksi berhasil diproses.\n");

	char filename[] = "admin.txt";
    printDecryptedFile(filename);
    
    return 0;
}
