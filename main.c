#include <stdio.h>
#include "primaJasa.h"

int main() {

	char *prompt = (char *)malloc(10 * sizeof(char)); // yang akan dituliskan ke dalam file
	int hargaPerMalam = 500000; // harga hotel per malam
	
    char *tanggalCheckIn = inputTanggalCheckIn();     
    printf("Tanggal check-in: %s\n", tanggalCheckIn);
    
    char *tanggalCheckOut = inputTanggalCheckOut(tanggalCheckIn);    
    printf("Tanggal check-out: %s\n", tanggalCheckOut);
    
    int totalHariMenginap = hitungHariMenginap(tanggalCheckIn, tanggalCheckOut);
    int hargaMenginap = totalHariMenginap*hargaPerMalam;
    printf("\ntotal harga : Rp. %d \n", totalHariMenginap*hargaPerMalam);
    
    int noKamar = kamar();

    sprintf(prompt, "%s, %s, %d, %d, %d\n", tanggalCheckIn, tanggalCheckOut, totalHariMenginap, hargaMenginap, noKamar);   // Menggabungkan tanggal check-in dan check-out ke dalam variabel hasil

    printf("%s", prompt);

    char* pesan_terenkripsi = enkripsi(prompt);
    printf("\nPesan terenkripsi: %s\n", pesan_terenkripsi);
    char* pesan_terdekripsi = dekripsi(pesan_terenkripsi);

    printf("Pesan terdekripsi: %s\n", pesan_terdekripsi);
    
    FILE *file = fopen("pemesanan.txt", "a"); // membuka dile dengan mode append atau mode menambahkan
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }

    fprintf(file, "%s", pesan_terenkripsi); // menulis ke file

    fclose(file);
    return 0;
}

