#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "admin.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 3
#define MAX_LENGTH 100


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
char dbsPemesanan[] = "database/pemesananHotel.txt";
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
int transaksiHotel(int hotel){
	int i, totalHotel;
    char line[100];
    
    FILE *files = fopen(dbsPemesanan, "r");
    if (files == NULL) {
        printf("Gagal membuka file.\n");
    }
    printf("\n\n<admin>\n");
	printf("+--------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-10s | %-12s | %-12s | %-4s | %-21s | %-4s | %-21s | %-6s | %-10s |\n", "No", " Username", "  CheckIn", "  CheckOut", "Hari", "        Harga","Kupon", "        Total", "NoKamar", "status");
    printf("|-----+------------+--------------+--------------+------+-----------------------+-------+-----------------------+---------+------------|\n");

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
    	
    	totalHotel += atoi(total);
    	hotel=totalHotel;
    	printf("| %-3s | %-10s | %-12s | %-12s | %-4s |",noOrder,namaCust, CI, CO, hari);printf("     Rp. ");disHarga(atoi(harga));printf("\t| %-4s%% |", ptgan);printf("     Rp. ");disHarga(atoi(total));printf("\t| %-7s | %-10s |\n", no, status);
    }
    printf("+--------------------------------------------------------------------------------------------------------------------------------------+\n");
	fclose(files);
	printf("Total pemasukan hotel: \n");
	printf("%d", &hotel);
	hotel=totalHotel;
	
	return hotel;
}
	


//file pulsa
char dbsPembelian[] = "database/HistoryPulsa.txt";
//hitung transaksi pulsa
int transaksiPulsa(int pulsa, char *username){
	int totalPulsa;
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
		totalPulsa += atoi(total);
		pulsa=totalPulsa;
		    
	}
		
	printf("+-------------------------------------------------------------------------------------------------------------------------------------+\n");	
	printf("Total transaksi pulsa: \n");
	printf("%d", &pulsa);
    fclose(file);
}


void totalpemasukan(int hotel, int pulsa){
	int totPemasukan;
	totPemasukan= hotel + pulsa;
	printf("Total pemasukan: \n");
	printf("%d", &totPemasukan);
	
}

//register admin
void registerAdmin(char *username, char *password) {
    // Melakukan enkripsi pada password sebelum disimpan
    
    FILE *file = fopen("database/admin.txt", "r"); // Buka file untuk membaca
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
            printf("====================\n");
    		printf("= Registrasi Gagal =\n");
    		printf("====================\n");
            printf("Username sudah digunakan.\n");
            return;
        }
    }
    	fclose(file);
    	
    	 file = fopen("database/admin.txt", "a");
    	if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
        encrypt(password);
 
        fprintf(file, "%s %s \n", username, password);
	    fclose(file);
    
	    printf("=======================\n");
    	printf("= Registrasi berhasil =\n");
    	printf("=======================\n");
}

//login admin
int loginAdmin(char *username, char *password) {
    FILE *file = fopen("database/admin.txt", "r");
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

void pemasukan(){
	FILE *pemesanan=fopen("database/pemesanan.txt", "r");
	if (pemesanan == NULL){
		printf("Gagal membuka file");
	}
}

//menu utama
int mainMenu(){
	int pilihan;
	printf("\tMenu\n");
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
	scanf("%d", &pil);
	return pil;
}

