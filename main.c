#include <stdio.h>
#include "primaJasa.h"


int main() {
	
	char *prompt = (char *)malloc(10 * sizeof(char));
	int hargaPerMalam = 500000;
    char *tanggalCheckIn = inputTanggalCheckIn();     
    printf("Tanggal check-in: %s\n", tanggalCheckIn);
    
    char *tanggalCheckOut = inputTanggalCheckOut(tanggalCheckIn);    
    printf("Tanggal check-out: %s\n", tanggalCheckOut);
    
    int totalHariMenginap = hitungHariMenginap(tanggalCheckIn, tanggalCheckOut);
    int hargaMenginap = totalHariMenginap*hargaPerMalam;
    printf("\ntotal harga : Rp. %d \n", totalHariMenginap*hargaPerMalam);

    
    sprintf(prompt, "%s, %s, %d, %d", tanggalCheckIn, tanggalCheckOut, totalHariMenginap, hargaMenginap);   // Menggabungkan tanggal check-in dan check-out ke dalam variabel hasil

    printf("%s", prompt);

    char* pesan_terenkripsi = enkripsi(prompt);
    printf("\nPesan terenkripsi: %s\n", pesan_terenkripsi);
    char* pesan_terdekripsi = dekripsi(pesan_terenkripsi);

    printf("Pesan terdekripsi: %s\n", pesan_terdekripsi);
    
    FILE *file = fopen("pemesanan.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 1;
    }

    fprintf(file, "%s", pesan_terenkripsi);

    fclose(file);
    return 0;
}

