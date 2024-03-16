#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ENCRYPTION_KEY 3


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

//hitung total hotel
void totalHotel(){
	
	
}


//hitung total pulsa
void totalPulsa(){
	
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
	FILE *pemesanan=fopen("pemesanan.txt", "r");
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

