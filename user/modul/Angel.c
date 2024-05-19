#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../payPrim.h"
#include "../Hafidz.h"
#include "../Jagad.h"
#include "../Angel.h"
//#include "../admin.h"

#define MAX_LENGTH 100
#define ADMIN_FEE 1500

char dbsPesawat[] = "database/HistoryTiket.txt";
char dbsArt[] = "art/jeticsPlane.txt";

//char char_set[] = "1qazZAQ2wsxXSW3edcCDE4rfvVFR5tgbBGT6yhnNHY7ujmMJU8ikKI9olLOpP";
//int mod = sizeof(char_set);

char dbsPemesanan[] = "database/pemesananHotel.txt";


linkedListAntrean* pesananPesawat = NULL;
// Fungsi untuk Membuat Node Baru
struct Node* createNodes(int hargaMenginap, int adminFee, int discount) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->hargaMenginap = hargaMenginap;
    newNode->adminFee = adminFee;
    newNode->discount = discount;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fungsi untuk Menambahkan Node ke Pohon Biner
struct Node* insert(struct Node* root, int hargaMenginap, int adminFee, int discount) {
    if (root == NULL) {
        return createNodes(hargaMenginap, adminFee, discount);
    }
    return root;
}

// Fungsi untuk Mencari Diskon Berdasarkan Persentase
int calculateDiscount(int hargaMenginap, int adminFee, int potongan) {
    int totalCost = hargaMenginap + adminFee;
    int discount = (totalCost * potongan) / 100;
    return discount;
}

// Fungsi untuk Menghitung Total Biaya Transaksi
int calculateTotalCost(int hargaMenginap, int adminFee, int discount) {
    return hargaMenginap + adminFee - discount;
}

int calculate(int potongan, int *hargaMenginap) {
    // Biaya admin adalah 1500    
    int adminFee = 1500;

    // Hitung diskon berdasarkan persentase
    int discount = calculateDiscount(*hargaMenginap, adminFee, potongan);

    // Hitung total biaya transaksi
    int totalCost = calculateTotalCost(*hargaMenginap, adminFee, discount);

    // Output hasil
    //printf("Total biaya transaksi: Rp. %d\n", totalCost);

    return totalCost;
}

// Function to get user role
void getUserRole(const char *username, char *role) {
    FILE *file = fopen("database/users.txt", "r");
    if (file == NULL) {
        perror("Gagal membuka file");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char *savedUsername = strtok(line, ",");
        if (strcmp(savedUsername, username) == 0) {
            strtok(NULL, ","); // Skip password
            strtok(NULL, ","); // Skip pin
            char *savedRole = strtok(NULL, ",");
            if (savedRole != NULL) {
                strcpy(role, savedRole);
                // Remove newline character from role if present
                role[strcspn(role, "\n")] = '\0';
                // Decrypt role after reading
                decrypt(role);
            }
            break;
        }
    }
    fclose(file);
}

//// Fungsi untuk display transaksi
//void printTransaction(const Transaction* transaction) {
//    printf("Order Number: %d\n", transaction->orderNumber);
//    printf("Username: %s\n", transaction->username);
//    printf("Topup Type: %s\n", transaction->topupType);
//    printf("Lokasi Awal: %s\n", transaction->lokasiAwal);
//    printf("Kota Tujuan: %s\n", transaction->kotaTujuan);
//    printf("Jam Keberangkatan: %s\n", transaction->jamKeberangkatan);
//    printf("Jam Kedatangan: %s\n", transaction->jamKedatangan);
//    printf("Jumlah Tiket: %d\n", transaction->jmlTiket);
//    printf("Kelas: %c\n", transaction->kelas);
//    printf("Harga Asli: %.2f\n", transaction->originalPrice);
//    printf("Discount: %.2f\n", transaction->discount);
//    printf("Admin Fee: %.2f\n", transaction->adminFee);
//    printf("Total: %.2f\n", transaction->total);
//    printf("Status: %s\n", transaction->status);
//}

//// Fungsi untuk menambahkan transaksi ke file HistoryTiket.txt
//void addTransactionToFile(Transaction transaction) {
//    FILE *file = fopen(dbsPesawat, "a");
//    if (file == NULL) {
//        printf("Gagal membuka file database untuk penulisan.\n");
//        return;
//    }
//	
//	char *prompt = (char *)malloc(10 * sizeof(char)); // yang akan dituliskan ke dalam file
//    sprintf(prompt, "%d,%s,%s,%s,%s,%s,%s,%d,%s,%d,%f,%f,%f,%f,%s\n", 
//        transaction.orderNumber, transaction.username, transaction.topupType, transaction.lokasiAwal,
//        transaction.kotaTujuan, transaction.jamKeberangkatan, transaction.jamKedatangan,
//        transaction.jmlTiket, transaction.kelas, transaction.seat, transaction.originalPrice,
//        transaction.discount, transaction.adminFee, transaction.total, transaction.status);
//
//	char* enkripsiPesawat = enkripsi(prompt); // Enkripsi data sebelum ditulis ke file
//    
//	fprintf(file, "%s", enkripsiPesawat);
//	
//    fclose(file);
//}


// Fungsi untuk mendapatkan nomor antrian terbaru dari file HistoryPulsa.txt
int getLastOrderNumber() {
    FILE *file = fopen(dbsPesawat, "r");
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

Penerbangan* cariPenerbangan(Penerbangan penerbangan[], int numPenerbangan, int kodePenerbangan) {
    int i;
	for (i = 0; i < numPenerbangan; i++) {
        if (penerbangan[i].kode == kodePenerbangan) {
            return &penerbangan[i];
        }
    }
    return NULL;
}

void printFileContent(const char *filename) {
    FILE *file = fopen(filename, "r");  // Membuka file dalam mode read-only
    if (file == NULL) {
        printf("Gagal membuka file %s\n", filename);
        return;
    }
    
    system("cls");

    char buffer[256];  // Buffer untuk menyimpan baris yang dibaca dari file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);  // Mencetak isi buffer ke layar
    }

    fclose(file);  // Menutup file setelah selesai membaca
    printf("\n\n");
}

void displayScheduleFromFile(const char* filename, Penerbangan penerbangan[], int* numPenerbangan) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file %s.\n", filename);
        return;
    }

    printf("\n=== JADWAL PENERBANGAN ===\n");
    printf("KODE\tLOKASI AWAL\tKOTA TUJUAN\tKEBERANGKATAN\tKEDATANGAN\tHARGA KELAS EKONOMI\tHARGA KELAS BISNIS\n");

    *numPenerbangan = 0;
    while (fscanf(file, "%d %s %s %s %s %d %d",
                  &penerbangan[*numPenerbangan].kode,
                  penerbangan[*numPenerbangan].lokasiAwal,
                  penerbangan[*numPenerbangan].kotaTujuan,
                  penerbangan[*numPenerbangan].jamKeberangkatan,
                  penerbangan[*numPenerbangan].jamKedatangan,
                  &penerbangan[*numPenerbangan].hargaEkonomi,
                  &penerbangan[*numPenerbangan].hargaBisnis) != EOF) {
        printf("%d\t%-12s\t%-12s\t%-5s\t\t%-5s\t\t%-17d\t%-17d\n",
               penerbangan[*numPenerbangan].kode,
               penerbangan[*numPenerbangan].lokasiAwal,
               penerbangan[*numPenerbangan].kotaTujuan,
               penerbangan[*numPenerbangan].jamKeberangkatan,
               penerbangan[*numPenerbangan].jamKedatangan,
               penerbangan[*numPenerbangan].hargaEkonomi,
               penerbangan[*numPenerbangan].hargaBisnis);
        (*numPenerbangan)++;
    }

    fclose(file);
}

void pembelianTiket(char *username) {
    // Membuat transaksi dengan nilai default
    Transaction transaction;
    
    // Mendapatkan nomor antrian terbaru
    int orderNumber = getLastOrderNumber();
    
	Penerbangan penerbangan[100];
    int numPenerbangan;
	int kodePenerbangan, jumlahTiket;
    char kelas[10];
    Penerbangan *penerbanganTerpilih = NULL;

    printFileContent(dbsArt);
    
    displayScheduleFromFile("database/jadwalpenerbangan.txt", penerbangan, &numPenerbangan);
    
    // Mendapatkan detail penerbangan dari pengguna
    do {
        printf("\nMasukkan kode penerbangan: ");
        scanf("%d", &kodePenerbangan);
        penerbanganTerpilih = cariPenerbangan(penerbangan, numPenerbangan, kodePenerbangan);
        if (penerbanganTerpilih == NULL) {
            printf("Kode penerbangan tidak valid.\n");
        }
    } while (penerbanganTerpilih == NULL);

    printf("Masukkan jumlah tiket: ");
    scanf("%d", &jumlahTiket);

    do {
        printf("Masukkan kelas (E untuk Ekonomi, B untuk Bisnis): ");
        scanf(" %s", &kelas);
        if (!strcmp(kelas, "E") && !strcmp(kelas, "e") && !strcmp(kelas, "B") && !strcmp(kelas, "b")) {
            printf("Kelas tidak valid.\n");
        }
    } while (!strcmp(kelas, "E") && !strcmp(kelas, "e") && !strcmp(kelas, "B") && !strcmp(kelas, "b"));
	
	if(!strcmp(kelas, "E") || !strcmp(kelas, "e")){
		strcpy(kelas, "Ekonomi");
	}
	else if(!strcmp(kelas, "B") || !strcmp(kelas, "b")){
		strcpy(kelas, "Bisnis");
	}
	
	
    transaction.orderNumber = orderNumber;
    strcpy(transaction.username, username);
    strcpy(transaction.lokasiAwal, penerbanganTerpilih->lokasiAwal);
    strcpy(transaction.kotaTujuan, penerbanganTerpilih->kotaTujuan);
    strcpy(transaction.jamKeberangkatan, penerbanganTerpilih->jamKeberangkatan);
    strcpy(transaction.jamKedatangan, penerbanganTerpilih->jamKedatangan);
    transaction.jmlTiket = jumlahTiket;
    strcpy(transaction.kelas, kelas);
    transaction.seat = orderNumber;
    
	float hargaPerTiket;
	if (!strcmp(kelas, "Ekonomi")) {
    	hargaPerTiket = penerbanganTerpilih->hargaEkonomi;
	} else {
	    hargaPerTiket = penerbanganTerpilih->hargaBisnis;
	}
	
	transaction.originalPrice = hargaPerTiket * jumlahTiket;
    
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
	
	strcpy(transaction.status, "Dlm Antrian...");
    
	printFileContent(dbsArt);
    
	printf("Berikut rincian pesanan anda\n\n");
    printf("Lokasi Awal\t : %s\n", transaction.lokasiAwal);
    printf("Kota Tujuan\t : %s\n", transaction.kotaTujuan);
    printf("Jam Keberangkatan: %s\n", transaction.jamKeberangkatan);
    printf("Jam Kedatangan\t : %s\n", transaction.jamKedatangan);
    printf("Jumlah Tiket\t : %d\n", transaction.jmlTiket);
    printf("Kelas\t\t : %s\n", transaction.kelas);
    printf("Harga Asli\t : Rp. ");disHarga(intOriginalPrice);
    printf("\nDiscount\t : %.2f\n", transaction.discount);
    printf("Admin Fee\t : Rp. ");disHarga(intAdminFee);
    printf("\nTotal\t\t : Rp. ");disHarga(intTotal);printf("\n\n");

	bool saldoCukup;
	char prompt[MAX_LENGTH];
    sprintf(prompt, "%d,%s,%s,%s,%s,%s,%d,%s,%.0f,%.0f,%.0f,%.0f,%s", 
        transaction.orderNumber, transaction.username, transaction.lokasiAwal,
        transaction.kotaTujuan, transaction.jamKeberangkatan, transaction.jamKedatangan,
        transaction.jmlTiket, transaction.kelas, transaction.originalPrice,
        transaction.discount, transaction.adminFee, transaction.total, transaction.status);

    if(confirmPay(username)){
	
    	if(insertLinkedList(&pesananPesawat, prompt)){
			char* enkripsiPesawat = enkripsi(prompt); // Enkripsi data sebelum ditulis ke file
	    
		//    printf("\n%s", enkripsiPesawat);
			FILE *file = fopen(dbsPesawat, "a");
		    if (file == NULL) {
		        printf("Gagal membuka file.\n");
		    }
			
			fprintf(file, "%s,\n", enkripsiPesawat);
			
		    fclose(file);
		}
		else{
			strcpy(transaction.status, "Antrean penuh");
		}
	} else { 
		strcpy(transaction.status, "Dibatalkan");
	}
   			
    printFileContent(dbsArt);
    
	printf("Berikut rincian pesanan anda\n\n");
    printf("Lokasi Awal\t : %s\n", transaction.lokasiAwal);
    printf("Kota Tujuan\t : %s\n", transaction.kotaTujuan);
    printf("Jam Keberangkatan: %s\n", transaction.jamKeberangkatan);
    printf("Jam Kedatangan\t : %s\n", transaction.jamKedatangan);
    printf("Jumlah Tiket\t : %d\n", transaction.jmlTiket);
    printf("Kelas\t\t : %s\n", transaction.kelas);
    printf("Harga Asli\t : Rp. ");disHarga(intOriginalPrice);
    printf("\nDiscount\t : %.2f\n", transaction.discount);
    printf("Admin Fee\t : Rp. ");disHarga(intAdminFee);
    printf("\nTotal\t\t : Rp. ");disHarga(intTotal);
	printf("\nStatus\t\t : %s", transaction.status);

	
	// Menambahkan transaksi ke file HistoryTiket.txt
//    addTransactionToFile(transaction);
	
	
    printList(pesananPesawat, "pesawat");
	
}

void printDecryptedFile(char *username) {    
    FILE *file = fopen(dbsPesawat, "r+");
    if (file == NULL) {
        printf("Gagal membuka file. \n");
    }

    // Print header
    printf("+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-12s | %-20s | %-20s | %-10s | %-10s | %-9s | %-7s | %-12s | %-10s | %-10s | %-10s | %-10s |\n",
           "No", "Username", "Lokasi Awal", "Kota Tujuan", "Jam Brgkt", "Jam Kdt", "Jml Tiket", "Kelas", "Harga", "Diskon", "Admin", "Total", "Status");
    printf("|--------------------+----------------------+----------------------+------------+------------+-----------+----------------------------------------------------------------------------|\n");

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {
//    	printf("%s", line);
        char *dekripsiLine = dekripsi(line);
//        printf("Decrypted Line: %s\n", dekripsiLine);

        // Tokenizing decrypted line
        char *orderNumber = strtok(dekripsiLine, ",");
        char *usernameField = strtok(NULL, ",");
        char *lokasiAwal = strtok(NULL, ",");
        char *kotaTujuan = strtok(NULL, ",");
        char *jamKeberangkatan = strtok(NULL, ",");
        char *jamKedatangan = strtok(NULL, ",");
        char *jmlTiket = strtok(NULL, ",");
        char *kelas = strtok(NULL, ",");
//        char *seat = strtok(NULL, ",");
        char *originalPrice = strtok(NULL, ",");
        char *discount = strtok(NULL, ",");
        char *adminFee = strtok(NULL, ",");
        char *total = strtok(NULL, ",");
        char *status = strtok(NULL, ",");

        // Printing the transaction details
        printf("| %-3s | %-12s | %-20s | %-20s | %-10s | %-10s | %-9s | %-7s |",
            orderNumber, usernameField, lokasiAwal, kotaTujuan, jamKeberangkatan, jamKedatangan, jmlTiket, kelas);
        printf(" Rp. ");
        disHarga(atoi(originalPrice));
        printf(" | %-8s%% |", discount);
        printf(" Rp. ");
        disHarga(atoi(adminFee));
        printf(" | Rp. ");
        disHarga(atoi(total));
        printf(" | %-8s |\n", status);
    }

    printf("+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    fclose(file);
}

