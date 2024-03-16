#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PIN 6

void topUpSaldo(char *username, float amount);

int main() {
    char username[MAX_USERNAME_LENGTH];
    float amount;

    // Input username dan jumlah saldo yang ingin ditambahkan
    printf("Masukkan username: ");
    scanf("%s", username);
    
    printf("Masukkan jumlah saldo yang ingin ditambahkan: ");
    scanf("%f", &amount);

    // Memanggil fungsi topUpSaldo
    topUpSaldo(username, amount);

    return 0;
}

void topUpSaldo(char *username, float amount) {
    FILE *file = fopen("database/saldoUsers.txt", "r");
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
}

