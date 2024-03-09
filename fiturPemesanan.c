#include <stdio.h>
#include <locale.h>
#include "primaJasa.h"

int main() {

	/*************** TAMPILAN USER **************/
	char *prompt = (char *)malloc(10 * sizeof(char)); // yang akan dituliskan ke dalam file
	int hargaPerMalam = 500000; // harga hotel per malam
	
    char *tanggalCheckIn = inputTanggalCheckIn();     
    printf("Tanggal check-in: %s\n", tanggalCheckIn);
    
    char *tanggalCheckOut = inputTanggalCheckOut(tanggalCheckIn);    
    printf("Tanggal check-out: %s\n", tanggalCheckOut);
    
    int totalHariMenginap = hitungHariMenginap(tanggalCheckIn, tanggalCheckOut);
    
	int hargaMenginap = totalHariMenginap*hargaPerMalam;
	
	int noKamar = kamar();
	
	// Menampilkan hasil ke user
	system("cls");
	printf("<user>\n");
	printf("Tanggal CheckIn\t : %s\nTanggal CheckOut : %s\nTotal menginap\t : %d hari\nNo kamar\t : %d\n", tanggalCheckIn, tanggalCheckOut, totalHariMenginap, noKamar);
	printf("Harga\t\t : Rp. ");disHarga(hargaMenginap);
    
    // Menggabungkan tanggal check-in dan check-out ke dalam variabel prompt
	sprintf(prompt, "%s,%s,%d,%d,%d,\n", tanggalCheckIn, tanggalCheckOut, totalHariMenginap, hargaMenginap, noKamar);   
	
	// Enkripsi prompt
    char* enkripsiPesanan = enkripsi(prompt);

    FILE *file = fopen("pemesanan.txt", "a"); // membuka dile dengan mode append atau mode menambahkan
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }
	// tulis pesanan ke file
    fprintf(file, "%s", enkripsiPesanan); // menulis ke file

    fclose(file);
    
    
    
    /*************** TAMPILAN ADMIN **************/
    int i;
    
    FILE *files = fopen("pemesanan.txt", "r");
    if (files == NULL) {
        printf("Gagal membuka file.\n");
        return 1;
    }

    printf("\n\n<admin>\n");
	printf("+-----------------------------------------------------------------+\n");
    printf("| %-12s | %-12s | %-4s | %-16s | %-6s |\n", "   CheckIn", "  CheckOut", "Hari", "     Harga", "NoKamar");
    printf("|--------------+--------------+------+------------------+---------|\n");

    char line[100];
    while (fgets(line, sizeof(line), files)) {
    	char *dekripPemesanan = dekripsi(line);
    	
    	char *CI = strtok(dekripPemesanan, ",");
    	char *CO = strtok(NULL, ",");
    	char *hari = strtok(NULL, ",");
    	char *harga = strtok(NULL, ",");
    	char *no = strtok(NULL, ",");
    	
    	printf("| %-12s | %-12s | %-4s |", CI, CO, hari);printf(" Rp. ");disHarga(atoi(harga));printf("\t| %-7s |\n", no);
    }
    printf("+-----------------------------------------------------------------+\n");
	fclose(files);
    return 0;
}

