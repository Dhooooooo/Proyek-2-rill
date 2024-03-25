#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../payPrim.h"
#include "../Jagad.h"
#include "../Hafidz.h"
#include "../Prima.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN 6
#define ENCRYPTION_KEY 5

/* LOGIN AND REGISTER */

void registerUser(char *username, char *password, char *pin) {
    // Melakukan enkripsi pada password sebelum disimpan
    
    FILE *file = fopen("database/users.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    
    // Membaca file dan memeriksa apakah username sudah ada
    while (fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin) == 3) {
        if (strcmp(username, storedUsername) == 0) {
            fclose(file);
            printf("====================\n");
    		printf("= Registrasi Gagal =\n");
    		printf("====================\n");
            printf("Username sudah digunakan.\n");
            spaceToContinue();
            return;
        }
    }
    rewind(file);
    while (fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin) == 3) {
        if (strcmp(password, storedPassword) == 0) {
            fclose(file);
            printf("====================\n");
    		printf("= Registrasi Gagal =\n");
    		printf("====================\n");
            printf("Password sudah digunakan.\n");
            spaceToContinue();
            return;
        }
    }
    
    fclose(file);
    
    file = fopen("database/users.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    // Memeriksa PIN
    int pinLength = strlen(pin);
    if (pinLength != MAX_PIN) {
    	printf("====================\n");
   		printf("= Registrasi Gagal =\n");
   		printf("====================\n");
        printf("Panjang PIN harus 6 angka.\n");
        spaceToContinue();
        return; // PIN tidak valid
    }
    int i;
    for (i = 0; i < pinLength; i++) {
        if (pin[i] < '0' || pin[i] > '9') {
        	printf("====================\n");
    		printf("= Registrasi Gagal =\n");
    		printf("====================\n");
            printf("PIN hanya boleh terdiri dari angka.\n");
            spaceToContinue();
            return; // PIN tidak valid
        }
    }
    
    encrypt(password);
    encrypt(pin);
    
    fprintf(file, "%s %s %s\n", username, password, pin);
    fclose(file);
    
    printf("=======================\n");
    printf("= Registrasi berhasil =\n");
    printf("=======================\n");
}

// Fungsi untuk login
int loginUser(char *username, char *password, char *pin) {
    FILE *file = fopen("database/users.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }
    rewind(file);
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    
    while (!feof(file)) {
        fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin);
        decrypt(storedPin);
        decrypt(storedPassword);
        
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0 && strcmp(pin, storedPin) == 0) {
            fclose(file);
            printf("==================\n");
            printf("= Login berhasil =\n");
            printf("==================\n");
            encrypt(password);
            return 1; // Login berhasil
        }
    }
    
    printf("===============\n");
    printf("= Login Gagal =\n");
	printf("===============\n");
	spaceToContinue();
    fclose(file);
    return 0; // Login gagal
}

// Fungsi untuk memodifikasi password pengguna
void modifyPass(char *username, char *password) {
    // Melakukan enkripsi pada password baru sebelum disimpan
    encrypt(password);
    
    FILE *file = fopen("database/users.txt", "r+"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    FILE *tempFile = fopen("database/temp.txt", "w"); // Buka file sementara untuk menulis
    if (tempFile == NULL) {
        fclose(file);
        printf("Gagal membuka file sementara.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    
    // Membaca file dan menyalin informasi pengguna ke file sementara
    while (fscanf(file, "%s %s %s", storedUsername, storedPassword, storedPin) == 3) {
        if (strcmp(username, storedUsername) == 0) {
            fprintf(tempFile, "%s %s %s\n", storedUsername, password, storedPin); // Menulis informasi pengguna yang dimodifikasi
        } else {
            fprintf(tempFile, "%s %s %s\n", storedUsername, storedPassword, storedPin); // Menyalin informasi pengguna lain tanpa modifikasi
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    // Menghapus file asli dan mengganti dengan file sementara
    if (remove("database/users.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return;
    }
    if (rename("database/temp.txt", "database/users.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return;
    }
    
    printf("Password berhasil diubah\n");
}

void modifyPin(char *username, char *newPin) {
    // Melakukan enkripsi pada password baru sebelum disimpan
    int pinLength = strlen(newPin);
    if (pinLength != MAX_PIN) {
        printf("Panjang PIN harus 6 angka.\n");
        spaceToContinue();
        return; // PIN tidak valid
    }
    int i;
    for (i = 0; i < pinLength; i++) {
        if (newPin[i] < '0' || newPin[i] > '9') {
            printf("PIN hanya boleh terdiri dari angka.\n");
            spaceToContinue();
            return; // PIN tidak valid
        }
    }
    
    encrypt(newPin);
    
    FILE *file = fopen("database/users.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    
    FILE *tempFile = fopen("database/temp.txt", "w"); // Buka file sementara untuk menulis
    if (tempFile == NULL) {
        fclose(file);
        printf("Gagal membuka file sementara.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    
    // Membaca file dan menyalin informasi pengguna ke file sementara
    while (fscanf(file, "%s %s %s", storedUsername, storedPassword, storedPin) == 3) {
        if (strcmp(username, storedUsername) == 0) {
            fprintf(tempFile, "%s %s %s\n", storedUsername, storedPassword, newPin); // Menulis informasi pengguna yang dimodifikasi
        } else {
            fprintf(tempFile, "%s %s %s\n", storedUsername, storedPassword, storedPin); // Menyalin informasi pengguna lain tanpa modifikasi
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    // Menghapus file asli dan mengganti dengan file sementara
    if (remove("database/users.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return;
    }
    if (rename("database/temp.txt", "database/users.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return;
    }
    
    printf("PIN berhasil diubah\n");
}

void modifyUser(char *username, char *password) {
    // Melakukan enkripsi pada password baru sebelum disimpan
    //encrypt(password);
    char tempUser[MAX_USERNAME_LENGTH];
    
    FILE *file = fopen("database/users.txt", "r+"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    
    // Membaca file dan memeriksa apakah username baru sudah ada
    while (fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin) == 3) {
        if (strcmp(username, storedUsername) == 0) {
            fclose(file);
            printf("Username sudah digunakan.\n");
            strcpy(username, storedUsername);
            return;
        }
    }
    
    rewind(file);
    
    // Memeriksa apakah password yang diberikan valid
    int validPassword = 0;
    while (fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin) == 3) {
    	//printf("%s\n", password);
    	//printf("%s\n", storedPassword);
        if (strcmp(password, storedPassword) == 0) {
            validPassword = 1;
            strcpy(tempUser, storedUsername);
            break;
        }
    }
    if (!validPassword) {
        fclose(file);
        printf("Password salah.\n");
        return;
    }
    
    // Mengupdate file saldoUsers.txt
    FILE *files = fopen("database/saldoUsers.txt", "r");
    if (files == NULL) {
        fclose(file);
        printf("Gagal membuka file.\n");
        return; //gagal
    }
    
    FILE *tempFiles = fopen("database/saldoUsersTemp.txt", "w");
    if (tempFiles == NULL) {
        fclose(files);
        fclose(file);
        printf("Gagal membuka file.\n");
        return; //gagal
    }
    float saldo;
    while (fscanf(files, "%s %f", storedUsername, &saldo) == 2) {
        if (strcmp(tempUser, storedUsername) == 0) {
            fprintf(tempFiles, "%s %f\n", username, saldo);
        } else {
            fprintf(tempFiles, "%s %f\n", storedUsername, saldo);
        }
    }
    
    fclose(files);
    fclose(tempFiles);

    if (remove("database/saldoUsers.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return; //gagal
    }
    if (rename("database/saldoUsersTemp.txt", "database/saldoUsers.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return; //gagal
    }
    
    rewind(file);
    
    FILE *tempFile = fopen("database/temp.txt", "w"); // Buka file sementara untuk menulis
    if (tempFile == NULL) {
        fclose(file);
        printf("Gagal membuka file sementara.\n");
        return;
    }
    
    // Membaca file dan menyalin informasi pengguna ke file sementara
    while (fscanf(file, "%s %s %s", storedUsername, storedPassword, storedPin) == 3) {
        if (strcmp(tempUser, storedUsername) == 0) {
            fprintf(tempFile, "%s %s %s\n", username, storedPassword, storedPin); // Menulis informasi pengguna yang dimodifikasi
        } else {
            fprintf(tempFile, "%s %s %s\n", storedUsername, storedPassword, storedPin); // Menyalin informasi pengguna lain tanpa modifikasi
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    // Menghapus file asli dan mengganti dengan file sementara
    if (remove("database/users.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return;
    }
    if (rename("database/temp.txt", "database/users.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return;
    }
    
    printf("Username berhasil diubah\n");
}

/* E-WALLET */

void dataSaldoNew(char *username){
	
	FILE *file = fopen("database/saldoUsers.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    float saldo; int ada; float saldoAwal = 0;
    
    while(fscanf(file, "%s %f\n", storedUsername, &saldo) == 2){
    	if(strcmp(storedUsername, username) == 0){
    		fclose(file);
    		return;
		}
	}
	fclose(file);
	
	file = fopen("database/saldoUsers.txt", "a");
	if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
 
    	fprintf(file,"%s %.2f\n", username, saldoAwal);
    fclose(file);
}

int isSaldoCukup(char *username, float totHarga) {
    FILE *file = fopen("database/saldoUsers.txt", "r+");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0; //gagal
    }
    
    FILE *tempFile = fopen("database/saldoUsersTemp.txt", "w");
    if (tempFile == NULL) {
        printf("Gagal membuka file.\n");
        fclose(file);
        return 0; //gagal
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    float saldo, lastSaldo;
    int userFound = 0;

    while (fscanf(file, "%s %f", storedUsername, &saldo) == 2) {
        if (strcmp(storedUsername, username) == 0) {
            userFound = 1;
            if (saldo >= totHarga) {
                lastSaldo = saldo - totHarga;
            } else {
                fclose(file);
                fclose(tempFile);
                return 0; //gagal
            }
        }
    }

    if (!userFound) {
        printf("Pengguna tidak ditemukan\n");
        fclose(file);
        fclose(tempFile);
        return 0; //gagal
    }

    rewind(file);

    while (fscanf(file, "%s %f", storedUsername, &saldo) == 2) {
        if (strcmp(username, storedUsername) == 0) {
            fprintf(tempFile, "%s %f\n", username, lastSaldo);
        } else {
            fprintf(tempFile, "%s %f\n", storedUsername, saldo);
        }
    }
    
    fclose(file);
    fclose(tempFile);

    if (remove("database/saldoUsers.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return 0; //gagal
    }
    if (rename("database/saldoUsersTemp.txt", "database/saldoUsers.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return 0; //gagal
    }

    return 1; //berhasil
}

void topUpSaldo(char *username, float amount) {

	printf("Masukkan jumlah saldo : ");
    scanf("%f", &amount);
    FILE *file = fopen("database/saldoUsers.txt", "r+");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    FILE *tempFile = fopen("database/saldoUsersTemp.txt", "w");
    if (tempFile == NULL) {
        printf("Gagal membuka file.\n");
        fclose(file);
        return;
    }

    char storedUsername[MAX_USERNAME_LENGTH];
    float saldo;
    int userFound = 0;
    int intAmount = (int)amount;
	
	clearScreen();
	title();
	printf("Anda akan menambah saldo Rp. ");disHarga(intAmount);printf("\n\n");
	if(confirmPay(username)){
    while (fscanf(file, "%s %f", storedUsername, &saldo) == 2) {
        if (strcmp(storedUsername, username) == 0) {
            userFound = 1;
            saldo += amount; // Menambahkan saldo
        }
        fprintf(tempFile, "%s %.2f\n", storedUsername, saldo);
    }

    if (!userFound) {
        printf("Pengguna tidak ditemukan\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    fclose(file);
    fclose(tempFile);

    if (remove("database/saldoUsers.txt") != 0) {
        printf("Gagal menghapus file asli.\n");
        return;
    }
    if (rename("database/saldoUsersTemp.txt", "database/saldoUsers.txt") != 0) {
        printf("Gagal mengganti nama file sementara.\n");
        return;
    }

    printf("Saldo berhasil ditambahkan.\n");
} else{
	printf("Pengisian Saldo Dibatalkan");
	return;
}    
}

int confirmPay(char *username) {
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    char storedPin[MAX_PIN];
    char pin[MAX_PIN];
    int acc;
    FILE *file = fopen("database/users.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }

    do {
        printf("1. Konfirmasi Pembayaran \n");
        printf("2. Cancel\n");
        printf("Pilih Tindakan : ");
        scanf("%d", &acc);
    } while (acc != 1 && acc != 2);

    if (acc == 1) {
        printf("Masukkan PIN : ");
        scanf("%s", pin);
        encrypt(pin);

        int pinFound = 0; // Variabel penanda untuk mengetahui apakah PIN ditemukan
        while (fscanf(file, "%s %s %s\n", storedUsername, storedPassword, storedPin) == 3) {
            if (strcmp(username, storedUsername) == 0 && strcmp(pin, storedPin) == 0) {
                pinFound = 1; // Setel variabel penanda jika PIN ditemukan
                break; // Keluar dari loop setelah menemukan PIN yang cocok
            }
        }

        if (pinFound) {
            fclose(file);
            return 1;
        } else {
            printf("PIN Salah\n");
            fclose(file);
            return 0;
        }
    } else {
        printf("Pembelian Dibatalkan\n");
        fclose(file);
        return 0;
    }

    // Lakukan operasi pada file
    fclose(file); // Jangan lupa tutup file setelah digunakan
}

/* INFO PROFIL */

void showInfo(char *username){
	
	FILE *file = fopen("database/saldoUsers.txt", "r"); // Buka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    
    char storedUsername[MAX_USERNAME_LENGTH];
    float saldo;
    int intSaldo;
    
    while(fscanf(file, "%s %f\n", storedUsername, &saldo) == 2){
    	if(strcmp(username, storedUsername) == 0){
    		intSaldo = (int)saldo;
    		printf("Username : %s\n", storedUsername);
    		printf("Saldo	 : Rp. ");disHarga(intSaldo);printf("\n");
    		fclose(file);
    		return;
		}
	}
}

void title(){
	FILE *file = fopen("database/grafiti.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Gagal membuka file list_barang.txt.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
		printf(" %s", buffer);
    }
    printf("\n");

    fclose(file);
}

