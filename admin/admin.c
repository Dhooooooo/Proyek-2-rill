#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "admin.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 5
#define MAX_LENGTH 100
#define MAX_COUPON_LENGTH 10


char char_set[] = "1qazZAQ2wsxXSW3edcCDE4rfvVFR5tgbBGT6yhnNHY7ujmMJU8ikKI9olLOpP";
int mod = sizeof(char_set);

//dekrip
char* dekripsi(char cipherText[]) {
	
    static char dekrip[100]; // assuming the length won't exceed 100 characters
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


// Fungsi untuk mengenkripsi password
void encrypt(char *text) {
    char *ptr = text;
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            *ptr = (*ptr + ENCRYPTION_KEY) % 126; // ASCII printable characters range
        }
        ptr++;
    }
}

// Fungsi untuk mendekripsi password
void decrypt(char *text) {
    char *ptr = text;
    while (*ptr != '\0') {
        if (*ptr != ' ') {
            *ptr = (*ptr - ENCRYPTION_KEY + 126) % 126; // ASCII printable characters range
        }
        ptr++;
    }
}

//file penyimpanan hotel
char dbsPemesanan[] = "../user/database/pemesananHotel.txt";
//menampilkan harga
void disHarga(int harga) {
   if (harga < 1000) {
       printf("%d", harga);
       return;
   }
   disHarga(harga / 1000);
   printf(".%03d", harga % 1000);
}
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

	


//file pulsa
char dbsPembelian[] = "../user/database/HistoryPulsa.txt";
//hitung transaksi pulsa
int printDecryptedFile(char *username) {
	int totalPembelian=0;
    FILE *file = fopen(dbsPembelian, "r");
    if (file == NULL) {
        printf("Gagal membuka file %s.\n", dbsPembelian);
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
//		char *space = " ";
		
		if (strcmp(status, "BERHASIL") == 0){
			totalPembelian += atoi(total);
		}
		
		
			
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
		
	printf("+-------------------------------------------------------------------------------------------------------------------------------------+\n");	
	printf("Total trasnsaksi pulsa berhasil: Rp. ", username);
    disHarga(totalPembelian); // Print the totalPembelian in proper format
    printf("\n");
    fclose(file);
    
    return totalPembelian;
};

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

int displayMenu() {
    int choice;
    printf("\nMENU\n");
    printf("1. Create coupon\n");
    printf("2. List coupon\n");
    printf("3. Change discount\n");
    printf("4. Exit\n");
    printf("Pilih menu: ");
    
    scanf("%d", &choice);
    
    return choice;
}

void waitNext() {
	printf("\nHarap tunggu");
	int i;
    for(i = 0; i < 3; i++){
    	printf(".");
    	sleep(1);
	}
};

void clearScreen(){
	system("cls");
}

void spaceToContinue(){
	printf("\n\nTekan spasi untuk melanjutkan");
    while(getch() != ' '); // menunggu user menekan spasi untuk melanjutkan
    system("cls");
};


void coupon() {
    char coupon[MAX_COUPON_LENGTH];
    int discount;
    int choice;
    
    // Main menu
    do {
        choice = displayMenu();
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
void registerAdmin(char *username, char *password) {
    // Melakukan enkripsi pada password sebelum disimpan
    
    FILE *file = fopen("admin.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    
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
    	
    	 file = fopen("admin.txt", "a");
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

//login admin
int loginAdmin(char *username, char *password) {
    FILE *file = fopen("admin.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }
    rewind(file);
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    
    while (!feof(file)) {
        fscanf(file, "%s %s \n", storedUsername, storedPassword);
        decrypt(storedPassword);
        
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(file);
            system("cls");
            printf("==================\n");
            printf("= Login berhasil =\n");
            printf("==================\n");
            return 1; // Login berhasil
        }
    }
    
    printf("===============\n");
    printf("= Login Gagal =\n");
	printf("===============\n");
    fclose(file);
    return 0; // Login gagal
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
	printf("2. Lihat riwayat pulsa\n");
	printf("3. Buat atau ubah kupon\n");
	printf("4. Pemasukan\n");
	printf("5. exit\n");
	printf("Pilih menu: \n");
	scanf("%d", &pil);
	return pil;
}

