#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../payPrim.h"
#include "../Hafidz.h"
#include "../Angel.h"

char dbsPembelian[] = "database/HistoryPulsa.txt";

// Fungsi untuk display transaksi
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

// Fungsi untuk mencari provider berdasarkan 4 angka awal
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
        printf("Gagal membuka file database untuk penulisan.\n");
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


// Fungsi untuk mendapatkan nomor antrian terbaru dari file HistoryPulsa.txt
int getLastOrderNumber() {
    FILE *file = fopen(dbsPembelian, "rb");
    if (file == NULL) {
        printf("Gagal membuka file database.\n");
        return 0; // Jika file tidak ditemukan, mengembalikan nomor 0
    }

    int baris = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            baris++;
        }
    }

    fclose(file);
    return baris + 1; // Mengembalikan nomor antrian terbaru
}


void printDecryptedFile(char *username) {
    FILE *file = fopen(dbsPembelian, "r");
    if (file == NULL) {
        printf("Gagal membuka file database.\n", dbsPembelian);
        return;
    }
	
    printf("+-------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-12s | %-12s| %-25s | %-14s |%-7s| %-9s | %-16s | %-12s |\n", 
	        "No", " Username", "Pembelian", "  Catatan", "Harga Asli", " Kupon", "Admin", "   Total", "Status");
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
	
    // Membuat transaksi dengan nilai default
    Transaction transaction;
    
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
	bool notValid = false;
    char phoneNumber[MAX_LENGTH];
    char*providerName;
	do{
		printf("\nMasukkan nomor telepon :");
		scanf("%s", phoneNumber);
    	providerName = findProvider(phoneNumber, providers, numProviders);
    	int panjangNomor = strlen(phoneNumber);
    	if (!strcmp(providerName, "Unknown") || panjangNomor < 10 || panjangNomor > 13){
    		printf("NOMOR TIDAK VALID.\n");
    		notValid = true;
		}
		else{
			printf("provider %s\n", providerName);
			notValid = false;
		}
	}while(notValid); // selama masih unknown maka masih ngeloop
	
    transaction.orderNumber = orderNumber;
    strcpy(transaction.topupType, "pulsa");

    // Mengisi detail transaksi
    strcpy(transaction.username, username);
	sprintf(transaction.note, "%s (%s)", phoneNumber, providerName);
	float price;
	
	do{
		printf("\nMasukkan jumlah yang diinginkan: ");scanf("%f", &price);
		if(price < 0){
			printf("Nominal tidak bisa minus!\n");
			notValid = true;
		}
		else if(price > 1000000){
			printf("Nominal tidak boleh lebih dari Rp. 1.000.000\n");
			notValid = true;
		}
		else{
			notValid = false;
		}
	}while(notValid);
    transaction.originalPrice = price;
    
    char coupon[MAX_COUPON_LENGTH]; // % untuk kupon
    int pilihan;
    int potongan;
    printf("Apakah anda ingin menggunakan kupon?\n(1) Ya\n(2) Tidak\n");
    printf("Masukkan pilihan anda: ");
    scanf("%d", &pilihan);
    
    if (pilihan == 1) {
    	potongan = kupon(coupon); // melakukan read coupon
    	transaction.discount = potongan;
	}
    clearScreen();
    
    	// Mengatur biaya admin ke nilai konstan
	transaction.adminFee = ADMIN_FEE;
    
  	float originalPrice = transaction.originalPrice;
	float total = transaction.total;
	float adminFee = transaction.adminFee;
	
	// Mengkonversi harga asli dan biaya admin ke tipe data integer
	int intOriginalPrice = (int)originalPrice;
	int intAdminFee = (int)adminFee;
	
	// Menghitung total biaya tanpa diskon
	int tempTotal = transaction.originalPrice + transaction.adminFee;
	
	// Menghitung total biaya dengan diskon
	int intTotal = (int)tempTotal - ((int)tempTotal * transaction.discount / 100);
	
	// Mengatur total biaya setelah diskon ke nilai yang dihitung
	transaction.total = intTotal;
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
    
	printf("Berikut rincian pesanan anda\n\n");
	printf("Nomor (Provider)\t : %s\n", transaction.note);
	printf("Harga\t\t\t : Rp. ");disHarga(intOriginalPrice);
	printf("\nBiaya Admin\t\t : ");disHarga(intAdminFee);
	printf("\nPotongan\t\t : %d%%", transaction.discount);
	printf("\nTotal Harga\t\t : Rp. ");disHarga(intTotal);printf("\n\n");

	bool saldoCukup;
    if(confirmPay(username)){
	
	    if(isSaldoCukup(username, transaction.total)){ // cek apakah saldo cukup
	    	strcpy(transaction.status, "BERHASIL");
	    	saldoCukup = true;
		} else {
			saldoCukup = false;
			strcpy(transaction.status, "GAGAL");
		}
	
	} else { 
		strcpy(transaction.status, "GAGAL");
	}
	
    // Menambahkan transaksi ke file HistoryPulsa.txt
    addTransactionToFile(transaction);
   			
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
    
	printf("Berikut rincian pesanan anda\n\n");
	printf("Nomor (Provider)\t : %s\n", transaction.note);
	printf("Harga\t\t\t : Rp. ");disHarga(intOriginalPrice);
	printf("\nBiaya Admin\t\t : ");disHarga(intAdminFee);
	printf("\nPotongan\t\t : %d%%", transaction.discount);
	printf("\nTotal Harga\t\t : Rp. ");disHarga(intTotal);
	printf("\nStatus\t\t\t : %s", transaction.status);
	if (!saldoCukup){
		printf(". Saldo tidak cukup. Harap isi saldo terlebih dahulu");
	}
}
