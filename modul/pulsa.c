#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../payPrim.h"

char dbsPembelian[] = "database/HistoryPulsa.txt";

// Function to create a transaction
//Transaction createTransaction(int orderNumber, const char* username, const char* topupType, const char* note, float originalPrice, float discount, float adminFee, float total, const char* status) {
//    Transaction transaction;
//    transaction.orderNumber = orderNumber;
//    strcpy(transaction.username, username);
//    strcpy(transaction.topupType, topupType);
//    strcpy(transaction.note, note);
//    transaction.originalPrice = originalPrice;
//    transaction.discount = discount;
//    transaction.adminFee = adminFee;
//    transaction.total = total;
//    strcpy(transaction.status, status);
//    return transaction;
//}

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

// Fungsi untuk menambahkan transaksi ke file HistoryPulsa.txt
void addTransactionToFile(Transaction transaction) {
    FILE *file = fopen(dbsPembelian, "a");
   if (file == NULL) {
        printf("Gagal membuka file admin.txt untuk penulisan.\n");
        return;
    }

    char prompt[MAX_LENGTH]; // Deklarasi variabel prompt
    sprintf(prompt, "%d,%s,%s,%s,%f,%d,%f,%f,%s,\n", 
        transaction.orderNumber, transaction.username, transaction.topupType,
        transaction.note, transaction.originalPrice, transaction.discount,
        transaction.adminFee, transaction.total, transaction.status);

    char* enkripsiPesanan = enkripsi(prompt); // Enkripsi data sebelum ditulis ke file

    fprintf(file, "%s", enkripsiPesanan); // Tulis data yang sudah dienkripsi ke file
    fclose(file);
}


// Fungsi untuk mendapatkan nomor antrian terbaru dari file admin.txt
int getLastOrderNumber() {
    FILE *file = fopen(dbsPembelian, "rb");
    if (file == NULL) {
        printf("Gagal membuka file admin.txt.\n");
        return 0; // Jika file tidak ditemukan, mengembalikan nomor 0
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    int numLines = fileSize / MAX_LENGTH;

    fclose(file);
    return numLines + 2; // Mengembalikan nomor antrian terbaru
}


void printDecryptedFile(char *username) {
    FILE *file = fopen(dbsPembelian, "r");
    if (file == NULL) {
        printf("Gagal membuka file %s.\n", dbsPembelian);
        return;
    }
	
    printf("+-------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-12s | %-12s| %-25s | %-14s |%-7s| %-9s | %-16s | %-12s |\n", 
	        "No", " Username", "Pembelian", "  Catatan", "Harga Asli", "  Disc", "Admin", "   Total", " Keterangan");
    printf("|-----+--------------+-------------+---------------------------+----------------+-------+-----------+------------------+--------------|\n");
	
	char line[MAX_LENGTH];
	while (fgets(line, sizeof(line), file)) {
    	char *dekripsiLine = dekripsi(line);
		
    	char *orderNumber = strtok(dekripsiLine, ",");
    	char *namaCust = strtok(NULL, ",");
    	char *topupType = strtok(NULL, ",");
    	char *note = strtok(NULL, ",");
    	char *originalPrice = strtok(NULL, ",");
    	char *discount = strtok(NULL, ",");
    	char *adminFee = strtok(NULL, ",");
    	char *total = strtok(NULL, ",");
    	char *status = strtok(NULL, ",");
//		char *space = " ";
		
		if(!strcmp(username, namaCust)){
			printf("| %-3s | %-12s | %-11s | %-25s |",
			orderNumber, username, topupType, note);
			printf(" Rp.");
			disHarga(atoi(originalPrice));
			printf("\t| %-4s%% |", discount);
			printf(" Rp. ");
			disHarga(atoi(adminFee)); 
			printf(" |");
			printf(" Rp.");
			disHarga(atoi(total));
			printf("  \t| %-12s |\n", status);
		}
	    
	}
		
	printf("+-------------------------------------------------------------------------------------------------------------------------------------+\n");	
	
    fclose(file);
}

void pembelianPulsa(char *username) {
	system("cls");
	
    printf(" /$$$$$$$  /$$   /$$ /$$        /$$$$$$   /$$$$$$           /$$$$$ /$$$$$$$$ /$$$$$$$$ /$$$$$$  /$$$$$$   /$$$$$$ \n");
    printf("| $$__  $$| $$  | $$| $$       /$$__  $$ /$$__  $$         |__  $$| $$_____/|__  $$__/|_  $$_/ /$$__  $$ /$$__  $$\n");
    printf("| $$  \\ $$| $$  | $$| $$      | $$  \\__/| $$  \\ $$            | $$| $$         | $$     | $$  | $$  \\__/| $$  \\__/\n");
    printf("| $$$$$$$/| $$  | $$| $$      |  $$$$$$ | $$$$$$$$            | $$| $$$$$      | $$     | $$  | $$      |  $$$$$$ \n");
    printf("| $$____/ | $$  | $$| $$       \\____  $$| $$__  $$       /$$  | $$| $$__/      | $$     | $$  | $$       \\____  $$\n");
    printf("| $$      | $$  | $$| $$       /$$  \\ $$| $$  | $$      | $$  | $$| $$         | $$     | $$  | $$    $$ /$$  \\ $$\n");
    printf("| $$      |  $$$$$$/| $$$$$$$$|  $$$$$$/| $$  | $$      |  $$$$$$/| $$$$$$$$   | $$    /$$$$$$|  $$$$$$/|  $$$$$$/\n");
    printf("|__/       \\______/ |________/ \\______/ |__/  |__/       \\______/ |________/   |__/   |______/ \\______/  \\______/ \n");

	printf("--------------------------------------------------------------------------------------------------------------------\n\n");
	
    // Mendapatkan nomor antrian terbaru
    int orderNumber = getLastOrderNumber();

    // Membaca data provider dari file pulsa.txt
    FILE *pulsaFile = fopen("database/pulsa.txt", "r");
    if (pulsaFile == NULL) {
        printf("Gagal. \n");
   		return; 
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
	
	while (!strcmp(providerName, "Unknown")){ // selama masih unknown maka masih ngeloop
		printf("NOMOR SALAH\n");
		printf("Masukkan nomor telepon :");
		scanf("%s", phoneNumber);
		
    	char*providerName = findProvider(phoneNumber, providers, numProviders);
		if(strcmp(providerName, "Unknown")){
			break;
		}
	}
	
    // Membuat transaksi dengan nilai default
    Transaction transaction;
    transaction.orderNumber = orderNumber;
    strcpy(transaction.topupType, "pulsa");
    
    // Mengisi status pembelian
    bool isSaldoCukup = 1; // DISINI GANTI 1 JADI FUNCTION NGECEK SALDO isSaldoCukup(username, totHarga);
//    char status[8];
    
    if(isSaldoCukup){ // kalo saldo cukup artinya return true
    	strcpy(transaction.status, "BERHASIL");
	}
	else{
		strcpy(transaction.status, "GAGAL");
	}
	
    // Mengisi detail transaksi
    strcpy(transaction.username, username);
	sprintf(transaction.note, "%s (%s)", phoneNumber, providerName);
	printf("Masukkan jumlah yang diinginkan: ");
    scanf("%f", &transaction.originalPrice);
    printf("Masukkan kode diskon (jika tidak ada, ketik 0): ");
    scanf("%f", &transaction.discount);

   	// Menghitung total biaya
	transaction.adminFee = ADMIN_FEE;
	transaction.total = transaction.originalPrice + transaction.discount + transaction.adminFee;

    // Menambahkan transaksi ke file admin.txt
    addTransactionToFile(transaction);
    printf("Transaksi berhasil.\n");
   			
    system("cls");
    
    printf(" /$$$$$$$  /$$   /$$ /$$        /$$$$$$   /$$$$$$           /$$$$$ /$$$$$$$$ /$$$$$$$$ /$$$$$$  /$$$$$$   /$$$$$$ \n");
    printf("| $$__  $$| $$  | $$| $$       /$$__  $$ /$$__  $$         |__  $$| $$_____/|__  $$__/|_  $$_/ /$$__  $$ /$$__  $$\n");
    printf("| $$  \\ $$| $$  | $$| $$      | $$  \\__/| $$  \\ $$            | $$| $$         | $$     | $$  | $$  \\__/| $$  \\__/\n");
    printf("| $$$$$$$/| $$  | $$| $$      |  $$$$$$ | $$$$$$$$            | $$| $$$$$      | $$     | $$  | $$      |  $$$$$$ \n");
    printf("| $$____/ | $$  | $$| $$       \\____  $$| $$__  $$       /$$  | $$| $$__/      | $$     | $$  | $$       \\____  $$\n");
    printf("| $$      | $$  | $$| $$       /$$  \\ $$| $$  | $$      | $$  | $$| $$         | $$     | $$  | $$    $$ /$$  \\ $$\n");
    printf("| $$      |  $$$$$$/| $$$$$$$$|  $$$$$$/| $$  | $$      |  $$$$$$/| $$$$$$$$   | $$    /$$$$$$|  $$$$$$/|  $$$$$$/\n");
    printf("|__/       \\______/ |________/ \\______/ |__/  |__/       \\______/ |________/   |__/   |______/ \\______/  \\______/ \n");

	printf("--------------------------------------------------------------------------------------------------------------------\n\n");
	
	float originalPrice = transaction.originalPrice;
    float adminFee = transaction.adminFee;
    float total = transaction.total;
    int intOriginalPrice;
	int intAdminFee;
	int intTotal;
	intTotal = (int)total;
	intOriginalPrice = (int)originalPrice;
	intAdminFee = (int)adminFee;
    
	printf("Berikut rincian pesanan anda\n\n");
	printf("Nomor (Provider)\t : %s\n", transaction.note);
	printf("Harga\t\t\t : Rp. ");disHarga(intOriginalPrice);
	printf("\nBiaya Admin\t\t : ");disHarga(intAdminFee);
	printf("\nPotongan\t\t : %d%%", transaction.discount);
	printf("\nTotal Harga\t\t : Rp. ");disHarga(intTotal);
}
