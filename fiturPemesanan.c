#include <stdio.h>
#include <locale.h>
#include "primaJasa.h"

int main() {
	char username[] = "nama0"; // ini untuk nampilin username user
	/*************** TAMPILAN USER SAAT MEMESAN **************/
	pemesananHotel(username);
    
    
    /*######### PEMESANAN HOTEL GABISA DIGABUNG SAMA DISPLAY ANTRIAN ###########*/
    
	/*************** TAMPILAN VERIF OLEH ADMIN **************/
    disPemesananAdmin();
	int noAntrian;
	printf("Nomor yang telah berhasil : ");scanf("%d", &noAntrian);
	adminApprove(noAntrian);
	system("cls");
	printf("<ADMIN>");
	disPemesananAdmin();

	/*************** TAMPILAN HISTORY USER **************/
	printf("\n\n<username : %s>\n", username);
    disPemesananUser(username);

    return 0;
}


