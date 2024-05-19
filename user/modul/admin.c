#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN_LENGTH 6
#define MAX_ROLE 5
#define ENCRYPTION_KEY 5
#define MAX_LENGTH 100
#define MAX_COUPON_LENGTH 10

#include "../Angel.h"
#include "../Jagad.h"

//hitung transaksi hotel
int transaksiHotel() {
    int totalHotel = 0; // Inisialisasi total pemasukan hotel

    FILE *files = fopen(dbsPemesanan, "r");
    if (files == NULL) {
        printf("Gagal membuka file.\n");
        return 0; // Kembalikan 0 jika gagal membuka file
    }

    printf("+--------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-10s | %-12s | %-12s | %-4s | %-21s | %-4s | %-21s | %-6s | %-10s |\n", "No", " Username", "  CheckIn", "  CheckOut", "Hari", "        Harga","Kupon", "        Total", "NoKamar", "status");
    printf("|-----+------------+--------------+--------------+------+-----------------------+-------+-----------------------+---------+------------|\n");

    char line[100];
    while (fgets(line, sizeof(line), files)) {
        char *dekripPemesanan = dekripsi(line);
        char *noOrder = strtok(dekripPemesanan, ",");
        char *namaCust = strtok(NULL, ",");
        char *CI = strtok(NULL, ",");
        char *CO = strtok(NULL, ",");
        char *hari = strtok(NULL, ",");
        char *harga = strtok(NULL, ",");
        char *ptgan = strtok(NULL, ",");
        char *total = strtok(NULL, ",");
        char *no = strtok(NULL, ",");
        char *status = strtok(NULL, ",");
        
        if (strcmp(status, "BERHASIL") == 0){
        // Hitung total hotel dan tambahkan ke totalHotel
        totalHotel += atoi(total);
		} 


        printf("| %-3s | %-10s | %-12s | %-12s | %-4s |", noOrder, namaCust, CI, CO, hari); printf("     Rp. "); disHarga(atoi(harga)); printf("\t| %-4s%% |", ptgan); printf("     Rp. "); disHarga(atoi(total)); printf("\t| %-7s | %-10s |\n", no, status);
    }
    printf("+--------------------------------------------------------------------------------------------------------------------------------------+\n");
    fclose(files);
    printf("Total transaksi hotel berhasil: Rp. "); // Cetak total pemasukan hotel
    disHarga(totalHotel);
    printf("\n");

    return totalHotel; // Kembalikan total pemasukan hotel
}

int transaksiPesawat() {
    int totalPesawat = 0;
    
    const char *dbsPesawat = "database/HistoryTiket.txt"; // Define the file name
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
                
				// Summing up the total purchase if the status is "BERHASIL"
        if (strcmp(status, "BERHASIL") == 0) {
            totalPesawat += atoi(total);
        }

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
	
	printf("Total transaksi tiket pesawat: Rp. ");
    disHarga(totalPesawat);
}


int transaksiKereta(){
	int totalLokal =0, totalKota = 0, totalKereta = 0;
	FILE* file;
    printf("Kereta Lokal (Bandung Raya)\n");
    printf("| Nama                         | Stasiun Keberangkatan | Stasiun Tujuan         | Tanggal Keberangkatan | Jadwal  | Tarif      |\n");
    printf("|------------------------------|-----------------------|------------------------|-----------------------|---------|------------|\n");

    file = fopen("database/riwayatKeretaLokal.txt", "r");
    if (file != NULL) {
        char line[200];
        while (fgets(line, sizeof(line), file)) {
            char nama[50], nik[20], stasiunKeberangkatan[50], stasiunTujuan[50], tanggal[11], jadwal[20], jenisKereta[20];
            int tarif;
            sscanf(line, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], Rp %d", 
                   nama, nik, stasiunKeberangkatan, stasiunTujuan, tanggal, jadwal, jenisKereta, &tarif);
            printf("| %-28s | %-21s | %-22s | %-21s | %-7s | Rp %-10d |\n", 
                   nama, stasiunKeberangkatan, stasiunTujuan, tanggal, jadwal, tarif);
                   totalLokal += tarif;
        }
        fclose(file);
    }

    printf("\nKereta Antar Kota\n");
    printf("| Nama                         | Stasiun Keberangkatan | Stasiun Tujuan         | Tanggal Keberangkatan | Jadwal  | Kelas      | Gerbong | Seat  | Tarif      |\n");
    printf("|------------------------------|-----------------------|------------------------|-----------------------|---------|------------|---------|-------|------------|\n");

    file = fopen("database/riwayatKeretaAntarKota.txt", "r");
    if (file != NULL) {
        char line[200];
        while (fgets(line, sizeof(line), file)) {
            char nama[50], nik[20], stasiunKeberangkatan[50], stasiunTujuan[50], tanggal[11], jadwal[20], jenisKereta[20], seat[10];
            int kelas, gerbong, tarif;
            sscanf(line, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %d, %[^,], Rp %d", 
                   nama, nik, stasiunKeberangkatan, stasiunTujuan, tanggal, jadwal, jenisKereta, &kelas, seat, &tarif);
            printf("| %-28s | %-21s | %-22s | %-21s | %-7s | %-10s | %-7d | %-5s | Rp %-10d |\n", 
                   nama, stasiunKeberangkatan, stasiunTujuan, tanggal, jadwal, kelas == 1 ? "Eksekutif" : "Ekonomi", gerbong, seat, tarif);
                   totalKota += tarif;
        }
        fclose(file);
	}
    totalKereta = totalKota + totalLokal;
    printf("Total transaksi kereta lokal dan antarkota: Rp. ");
    disHarga(totalKereta);
}


//int printDecryptedFile(char *username) {
//    int totalPembelian = 0;
//    
//    const char *dbsPesawat = "database/HistoryTiket.txt"; // Define the file name
//    FILE *file = fopen(dbsPesawat, "r");
//    if (file == NULL) {
//        printf("Gagal membuka file %s.\n", dbsPesawat);
//        return 0;
//    }
//
//    // Print header
//    printf("+----------------------------------------------------------------------------------------------------------------------------------+\n");
//    printf("| %-3s | %-12s | %-11s | %-20s | %-20s | %-10s | %-10s | %-9s | %-7s | %-7s | %-12s | %-10s | %-10s | %-10s | %-10s |\n",
//           "No", "Username", "Pembelian", "Lokasi Awal", "Kota Tujuan", "Jam Brgkt", "Jam Kdt", "Jml Tiket", "Kelas", "Seat", "Harga", "Diskon", "Admin", "Total", "Status");
//    printf("+----------------------------------------------------------------------------------------------------------------------------------+\n");
//
//    char line[MAX_LENGTH];
//    while (fgets(line, sizeof(line), file)) {
//        char *dekripsiLine = dekripsi(line);
//        char *orderNumber = strtok(dekripsiLine, ",");
//        char *usernameField = strtok(NULL, ",");
//        char *topupType = strtok(NULL, ",");
//        char *lokasiAwal = strtok(NULL, ",");
//        char *kotaTujuan = strtok(NULL, ",");
//        char *jamKeberangkatan = strtok(NULL, ",");
//        char *jamKedatangan = strtok(NULL, ",");
//        char *jmlTiket = strtok(NULL, ",");
//        char *kelas = strtok(NULL, ",");
//        char *seat = strtok(NULL, ",");
//        char *originalPrice = strtok(NULL, ",");
//        char *discount = strtok(NULL, ",");
//        char *adminFee = strtok(NULL, ",");
//        char *total = strtok(NULL, ",");
//        char *status = strtok(NULL, ",");
//
//        // Check for NULL values and handle them
//        if (!orderNumber || !usernameField || !topupType || !lokasiAwal || !kotaTujuan || !jamKeberangkatan || !jamKedatangan || !jmlTiket || !kelas || !seat || !originalPrice || !discount || !adminFee || !total || !status) {
//            printf("Data tidak lengkap di baris: %s\n", line);
//            continue;
//        }
//
//        // Summing up the total purchase if the status is "BERHASIL"
//        if (strcmp(status, "BERHASIL") == 0) {
//            totalPembelian += atoi(total);
//        }
//
//        // Printing the transaction details
//        printf("| %-3s | %-12s | %-11s | %-20s | %-20s | %-10s | %-10s | %-9s | %-7s | %-7s |",
//               orderNumber, usernameField, topupType, lokasiAwal, kotaTujuan, jamKeberangkatan, jamKedatangan, jmlTiket, kelas, seat);
//        printf(" Rp. ");
//        disHarga(atoi(originalPrice));
//        printf(" | %-8s%% |", discount);
//        printf(" Rp. ");
//        disHarga(atoi(adminFee));
//        printf(" | Rp. ");
//        disHarga(atoi(total));
//        printf(" | %-10s |\n", status);
//    }
//
//    printf("+----------------------------------------------------------------------------------------------------------------------------------+\n");
//    printf("Total transaksi pesawat berhasil: Rp. ");
//    disHarga(totalPembelian); // Print the totalPembelian in proper format
//    printf("\n");
//    fclose(file);
//
//    return totalPembelian;
//}

//int printDecryptedFile(char *username) {
//    int totalPembelian = 0;
//    
//    const char *dbsPesawat = "database/HistoryTiket.txt"; // Define the file name
//    FILE *file = fopen(dbsPesawat, "r");
//    if (file == NULL) {
//        printf("Gagal membuka file %s.\n", dbsPesawat);
//        return 0;
//    }
//
//    // Print header
//    printf("+-------------------------------------------------------------------------------------------------------------------------------+\n");
//    printf("| %-3s | %-12s | %-11s | %-20s | %-20s | %-10s | %-10s | %-9s | %-7s | %-7s | %-12s | %-10s |  %-10s |  %-10s |  %-10s |\n",
//           "No", "Username", "Pembelian", "Lokasi Awal", "Kota Tujuan", "Jam Brgkt", "Jam Kdt", "Jml Tiket", "Kelas", "Seat", "Harga", "Dsikon", "Admin", "Total", "Status");
//    printf("+-------------------------------------------------------------------------------------------------------------------------------+\n");
//
//    char line[100];
//    while (fgets(line, sizeof(line), file)) {
//        char *dekripPesawat = dekripsi(line);
//        char *orderNumber = strtok(dekripPesawat, ",");
//        char *username = strtok(NULL, ",");
//        char *topupType = strtok(NULL, ",");
//        char *lokasiAwal = strtok(NULL, ",");
//        char *kotaTujuan = strtok(NULL, ",");
//        char *jamKeberangkatan = strtok(NULL, ",");
//        char *jamKedatangan = strtok(NULL, ",");
//        char *jmlTiket = strtok(NULL, ",");
//        char *kelas = strtok(NULL, ",");
//        char *seat = strtok(NULL, ",");
//        char *originalPrice = strtok(NULL, ",");
//        char *discount = strtok(NULL, ",");
//        char *adminFee = strtok(NULL, ",");
//        char *total = strtok(NULL, ",");
//        char *status = strtok(NULL, ",");
//
//        // Printing the transaction details
//        printf("| %-3s | %-12s | %-11s | %-20s | %-20s | %-10s | %-10s | %-9s | %-7s | %-5s |", 
//		orderNumber, username, topupType, lokasiAwal, kotaTujuan, jamKeberangkatan, jamKedatangan, jmlTiket, kelas, seat);    
//        printf(" Rp. ");
//		disHarga(atoi(originalPrice));
//		printf("\t| %-8s%% |", discount);
//		printf(" Rp. ");
//		disHarga(atoi(adminFee)); 
//		printf("\t  |");
//		printf(" Rp. ");
//		disHarga(atoi(total));
//		printf("\t | %-12s |\n", status);    
//    }
//
//    printf("+-------------------------------------------------------------------------------------------------------------------------------+\n");
//    fclose(file);
//
//    return totalPembelian;
//}


//fitur kupon
void createCoupon(char *coupon, int discount) {
    // Membuat atau overwrite file database
    FILE *couponList;
    couponList = fopen("../user/database/List_coupon.txt", "a");

    // Menyimpan kupon yang dibuat ke database
    fprintf(couponList, "%s %d\n", coupon, discount);
    
    fclose(couponList);
}

void displayCouponList() {
    // Melakukan read file database
    FILE *couponList;
    couponList = fopen("../user/database/List_coupon.txt", "r");
    if (!couponList) {
        printf("File tidak ada.\n");
        return;
    }

    char storedCoupon[MAX_COUPON_LENGTH];
    int storedDiscount;

    printf("\nLIST COUPON\n");
    printf("============\n");
    
    // Menampilkan kupon yang ada di database
    while (fscanf(couponList, "%s %d", storedCoupon, &storedDiscount) != EOF) {
        printf("Kode Kupon: %s | Diskon: %d | ", storedCoupon, storedDiscount);
        encrypt(storedCoupon);
        printf("Kupon (setelah enkripsi): %s\n", storedCoupon);
    }

    fclose(couponList);
}

void changeDiscount(char *coupon, int newDiscount) {
    FILE *couponList;
    FILE *tempList;
    char tempCoupon[MAX_COUPON_LENGTH];
    int tempDiscount;
    int found = 0;

    couponList = fopen("../user/database/List_coupon.txt", "r");
    if (!couponList) {
        printf("File tidak ada.\n");
        return;
    }

    tempList = fopen("../user/database/temp_List_coupon.txt", "w");
    if (!tempList) {
        printf("File tidak ada.\n");
        fclose(couponList);
        return;
    }
	
	
    while (fscanf(couponList, "%s %d", tempCoupon, &tempDiscount) != EOF) {
        if (strcmp(coupon, tempCoupon) == 0) {
            fprintf(tempList, "%s %d\n", tempCoupon, newDiscount);
            found = 1;
        } else {
            fprintf(tempList, "%s %d\n", tempCoupon, tempDiscount);
        }
    }

    fclose(couponList);
    fclose(tempList);

    remove("../user/database/List_coupon.txt");
    rename("../user/database/temp_List_coupon.txt", "../user/database/List_coupon.txt");

    if (found) {
        printf("Diskon untuk kupon %s berhasil diubah menjadi %d\n", coupon, newDiscount);
    } else {
        printf("Kupon tidak ditemukan.\n");
    }
}

void coupon() {
    char coupon[MAX_COUPON_LENGTH];
    int discount;
    int choice;
    
    // Main menu
    do {
        choice = menuKupon();
        system("cls");
        switch (choice) {
            case 1:
                // create coupon
                printf("Masukkan kode kupon: ");
                scanf("%s", coupon);
                printf("Masukkan diskon: ");
                scanf("%d", &discount);
                
                // Prosedur menyimpan kupon ke database
                createCoupon(coupon, discount);
                
                // Prosedur enkripsi kupon yang diinput
                encrypt(coupon);
    
                printf("\nKode kupon: %s\n", coupon);
                spaceToContinue();
                clearScreen();
                break;
            
            case 2:
                // List coupon
                displayCouponList();
                spaceToContinue();
                clearScreen();
                break;
            
            case 3:
                // Change discount
                printf("Masukkan kode kupon yang ingin diubah diskonnya: ");
                scanf("%s", coupon);
                printf("Masukkan diskon baru: ");
                scanf("%d", &discount);
                changeDiscount(coupon, discount);
                spaceToContinue();
                clearScreen();
                break;
            
            case 4:
            	clearScreen();
                break;
        	default:
        		printf("Pilihan tidak valid\n");
        }
    } while (choice != 4);
}

//register admin
void registerAdmin(char *username, char *password, char *pin, char *role) {
    // Melakukan enkripsi pada password sebelum disimpan
    
    FILE *file = fopen("database/users.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN_LENGTH];
    char storedRole[MAX_ROLE];
    
    // Membaca file dan memeriksa apakah username sudah ada
    while (fscanf(file, "%s %s\n", storedUsername, storedPassword) == 2) {
        if (strcmp(username, storedUsername) == 0) {
            fclose(file);
            system("cls");
            printf("====================\n");
    		printf("= Registrasi Gagal =\n");
    		printf("====================\n");
            printf("Username sudah digunakan.\n");
            return;
        }
    }
    	fclose(file);
    	
    	file = fopen("", "a");
    	if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
        encrypt(password);
 
        fprintf(file, "%s %s \n", username, password);
	    fclose(file);
	    system("cls");
    
	    printf("=======================\n");
    	printf("= Registrasi berhasil =\n");
    	printf("=======================\n");
}


//menu utama
int mainMenu(){
	int pilihan;
	system("cls");
	printf("\n\tMenu\n");
	printf("1. Login\n");
	printf("2. Register\n");
	printf("3. Exit\n");
	printf("Pilih menu: ");
	scanf("%d", &pilihan);
	return pilihan;
}

//menu admin setelah login
int menuAdmin(){
	int pil;
	printf("\tMenu\n");
	printf("1. Lihat Riwayat hotel\n");
	printf("2. Lihat riwayat pesawat\n");
	printf("3. Buat atau ubah kupon\n");
	printf("4. Pemasukan\n");
	printf("5. Registrasi Admin\n");
	printf("6. exit\n");
	printf("7. Approve pesanan\n");
	printf("8. Lihat riwayat kereta\n");
	printf("Pilih menu: \n");
	scanf("%d", &pil);
	return pil;
}

int menuKupon() {
    int choice;
    printf("1. Create coupon\n");
    printf("2. List coupon\n");
    printf("3. Change discount\n");
    printf("4. Exit\n");
    printf("Pilih menu: ");
    
    scanf("%d", &choice);
    
    return choice;
}

//----------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------

////dekrip
//char* dekripsi(char cipherText[]) {
//	
//    static char dekrip[100]; // assuming the length won't exceed 100 characters
//    int i,j;
//    for (i = 0; i < strlen(cipherText); i++) {
//    	bool isCipherInChar = false;
//        int index = 0;
//        for (j = 0; j < strlen(char_set); j++) {
//            if (char_set[j] == cipherText[i]) {
//            	isCipherInChar = true;
//                while ((index - 7) % 3 != 0)
//                    index += mod;
//                int hasil = (index - 7) / 3;
//                dekrip[i] = char_set[hasil];
//                break;
//            }
//            index++;
//        }
//        if(!isCipherInChar){
//        	dekrip[i] = cipherText[i];
//		}
//    }
//    return dekrip;
//}

//// Fungsi untuk mengenkripsi password
//void encrypt(char *text) {
//    char *ptr = text;
//    while (*ptr != '\0') {
//        if (*ptr != ' ') {
//            *ptr = (*ptr + ENCRYPTION_KEY) % 126; // ASCII printable characters range
//        }
//        ptr++;
//    }
//}
//
//// Fungsi untuk mendekripsi password
//void decrypt(char *text) {
//    char *ptr = text;
//    while (*ptr != '\0') {
//        if (*ptr != ' ') {
//            *ptr = (*ptr - ENCRYPTION_KEY + 126) % 126; // ASCII printable characters range
//        }
//        ptr++;
//    }
//}

////menampilkan harga
//void disHarga(int harga) {
//   if (harga < 1000) {
//       printf("%d", harga);
//       return;
//   }
//   disHarga(harga / 1000);
//   printf(".%03d", harga % 1000);
//}

//int displayMenu() {
//    int choice;
//    printf("\nMENU\n");
//    printf("1. Create coupon\n");
//    printf("2. List coupon\n");
//    printf("3. Change discount\n");
//    printf("4. Exit\n");
//    printf("Pilih menu: ");
//    
//    scanf("%d", &choice);
//    
//    return choice;
//}

//void waitNext() {
//	printf("\nHarap tunggu");
//	int i;
//    for(i = 0; i < 3; i++){
//    	printf(".");
//    	sleep(1);
//	}
//};
//
//void clearScreen(){
//	system("cls");
//}
//
//void spaceToContinue(){
//	printf("\n\nTekan spasi untuk melanjutkan");
//    while(getch() != ' '); // menunggu user menekan spasi untuk melanjutkan
//    system("cls");
//};

