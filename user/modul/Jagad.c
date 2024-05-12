#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "../payPrim.h"
#include "../Jagad.h"
#include "../Hafidz.h"

// harga hotel per malam
int hargaPerMalam = 1000000;

// nomor kamar mulai dari 100 sampai 300
#define minKamar 100
#define maxKamar 300

// File penyimpanan
char dbsPemesanan[] = "database/pemesananHotel.txt";
struct Node* head = NULL;
// Fungsi untuk memvalidasi tanggal yang diinputkan, berlaku untuk tanggal Check In ataupun tanggal Check Out
bool* isTglValid(char *tanggal) { 
	// Deklrasi Variabel
	int i;
	bool *valid = (bool*)malloc(sizeof(bool));
	int bln31[] = {1,3,5,7,8,10,12};
	int bln30[] = {4,6,9,11};
    char delim[] = "/";    
    
    bool hariValid = true;
    bool bulanValid = true;
    bool tahunValid = true;    
	
	bool bulan31 = false;
    bool bulan30 = false;
    bool bulanKabisat = false;
    
	char originalTanggal[100];
	strcpy(originalTanggal, tanggal); // Menyimpan nilai asli tanggal
    
    // Mendeklarasikan variabel untuk menyimpan informasi tanggal dan waktu
    time_t now;
    struct tm *local;

    // Mendapatkan waktu saat ini
    now = time(NULL);

    // Mengkonversi waktu saat ini ke waktu lokal
    local = localtime(&now);
    
    // Simpan waktu saat ini ke variabel
    int tahunSkrg = local->tm_year + 1900;
    
    // Memisahkan hari bulan tahun dari parameter
    int hari = atoi(strtok(originalTanggal, delim));
    int bulan = atoi(strtok(NULL, delim));
    int tahun = atoi(strtok(NULL, delim));
    

    // Cek apakah bulan yang diinputkan memiliki 31 hari
    for (i = 0; i < sizeof(bln31) / sizeof(bln31[0]); i++) {
        if (bulan == bln31[i]) {
            bulan31 = true;
            break; // Keluar dari loop setelah menemukan kecocokan
        }
    }
    
    // Cek apakah bulan yang diinputkan memiliki 30 hari
    if(!bulan31){
    	for (i = 0; i < sizeof(bln30) / sizeof(bln30[0]); i++) {
	        if (bulan == bln30[i]) {
	            bulan30 = true;
	            break; // Keluar dari loop setelah menemukan kecocokan
	        }
	    }
	}
	
	// Cek jika bulan februari apakah dai tahun kabisat atau bukan
	else{
		if(tahun % 4 == 0 && tahun % 100 != 0){
			bulanKabisat = true;
		}
	}
	
	//mengecek apakah tanggal valid atau tidak, syaratnya tidak bisa menginput sebelum tanggal hari ini dan hanya bisa memesan maksmial satu tahun kedepan
    if(tahun < tahunSkrg || tahun > tahunSkrg+1){
    	tahunValid = false;
	}
    else if(bulan>12 || bulan <1){
    	bulanValid = false;
	}
	else {
		if(bulan31){
			if(hari > 31){ // kalo bulan 31 apakah tanggal lebih dari 31
				hariValid = false;
			}
		}
		else if(bulan30){
			if(hari > 30){
				hariValid = false;
			}
		}
		else{ // untuk bulan februari
			if(bulanKabisat){
				if(hari > 29){ // jika februari di tahun kabisat
					hariValid = false;
				}
			}
			else{
				if(hari >28){ // jika februari bukan di tahun kabisat
					hariValid = false;
				}
			}
		}
	}
	
	// Mengambil kesimpulan apakah tanggal yang diinputkan sesuai syarat atau tidak dengan menggunakan AND
	*valid = tahunValid && bulanValid && hariValid;
	return valid;
}

bool *isTglCheckInValid(char *tanggalCheckIn){
	// Mendeklarasikan variabel untuk menyimpan informasi tanggal dan waktu
    time_t now;
    struct tm *local;

    // Mendapatkan waktu saat ini
    now = time(NULL);

    // Mengkonversi waktu saat ini ke waktu lokal
    local = localtime(&now);
    
    // Simpan waktu saat ini ke variabel
    int hariSkrg = local->tm_mday;
    int bulanSkrg = local->tm_mon + 1;
    int tahunSkrg = local->tm_year + 1900;
    
    int i;
	bool *valids = (bool*)malloc(sizeof(bool));

	int bln31[] = {1,3,5,7,8,10,12};
	int bln30[] = {4,6,9,11};

    char delim[] = "/";
    
    bool hariValid = true;
    bool bulanValid = true;
    bool tahunValid = true;
	bool valid;
    
    
    int hari = atoi(strtok(tanggalCheckIn, delim));
    int bulan = atoi(strtok(NULL, delim));
    int tahun = atoi(strtok(NULL, delim));
    
    bool bulan31 = false;
    bool bulan30 = false;
    bool bulanKabisat = false;
    
    for (i = 0; i < sizeof(bln31) / sizeof(bln31[0]); i++) {
        if (bulan == bln31[i]) {
            bulan31 = true;
            break; // Keluar dari loop setelah menemukan kecocokan
        }
    }
    if(!bulan31){
    	for (i = 0; i < sizeof(bln30) / sizeof(bln30[0]); i++) {
	        if (bulan == bln30[i]) {
	            bulan30 = true;
	            break; // Keluar dari loop setelah menemukan kecocokan
	        }
	    }
	}
	else{
		if(tahun % 4 == 0){
			bulanKabisat = true;
		}
	}

    if(tahun > tahunSkrg + 1){
    	tahunValid = false;
	}
    else if(bulan > 12 || bulan < 1){
    	bulanValid = false;
	}
	else {
		if(bulan31){
			if(hari > 31 ){ // kalo bulan 31 apakah tanggal lebih dari 31
				hariValid = false;
			}
		}
		else if(bulan30){
			if(hari > 30){
				hariValid = false;
			}
		}
		else{ // untuk bulan februari
			if(bulanKabisat){
				if(hari > 29){ // jika februari di tahun kabisat
					hariValid = false;
				}
			}
			else{
				if(hari >28){ // jika februari bukan di tahun kabisat
					hariValid = false;
				}
			}
		}
	}
	
	if(tahunValid && bulanValid && hariValid){
    	
    	
		if (tahun == tahunSkrg+1 && bulan == bulanSkrg && hari == hariSkrg){ // maksimal mesen setahun kemudian dari hari saat user mau mesen
			valid = true;
		}
		else if (tahun == tahunSkrg && bulan > bulanSkrg){
			valid = true;
		}
		else if (tahun == tahunSkrg && bulan == bulanSkrg && hari >= hariSkrg){
			valid = true;
		}
		else{
			valid = false;
		}
	}
	
	
//	printf("%d %d %d %d", tahunValid, bulanValid, hariValid, valid);
	*valids = tahunValid && bulanValid && hariValid && valid;
	return valids;
}

// Fungsi untuk memvalidasi tanggalCheckOut
bool *isTglCheckOutValid(char *tanggalCheckIn, char *tanggalCheckOut) {
	
    // Simpan salinan tanggalCheckIn
    char tempTanggalCheckIn[100];
    strcpy(tempTanggalCheckIn, tanggalCheckIn);

    // Pisahkan tanggalCheckOut menggunakan strtok
    char *token = strtok(tanggalCheckOut, "/");
    int hariCheckOut = atoi(token);
    token = strtok(NULL, "/");
    int bulanCheckOut = atoi(token);
    token = strtok(NULL, "/");
    int tahunCheckOut = atoi(token);

    // Pisahkan tanggalCheckIn menggunakan strtok
    token = strtok(tempTanggalCheckIn, "/");
    int hariCheckIn = atoi(token);
    token = strtok(NULL, "/");
    int bulanCheckIn = atoi(token);
    token = strtok(NULL, "/");
    int tahunCheckIn = atoi(token);

    // Periksa apakah tanggalCheckOut valid
    bool checkOutValid;
    if (tahunCheckOut > tahunCheckIn) {
        checkOutValid = true;
    } else if (tahunCheckOut == tahunCheckIn && bulanCheckOut > bulanCheckIn) {
        checkOutValid = true;
    } else if (tahunCheckOut == tahunCheckIn && bulanCheckOut == bulanCheckIn && hariCheckOut > hariCheckIn) {
        checkOutValid = true;
    } else {
        checkOutValid = false;
    }
    

    // Alamat memori statis untuk hasil boolean
    bool *result = (bool *)malloc(sizeof(bool));
    *result = checkOutValid;

    return result;
}

// Fungsi untuk menginputkan tanggal Check In
char *inputTanggalCheckIn() {
	
	// Deklrasai variabel pointer memesan memori kosong dengan ukuran yang ditentukan sesuai kebutuhan
    char *tglInput = (char * )malloc(11 * sizeof(char)); // Alokasikan memori untuk menyimpan tanggal
    char *tglCheckIn = (char * )malloc(11 * sizeof(char));
    bool *checkInValid = (bool *)malloc(sizeof(bool));
    bool *tanggalValid = (bool *)malloc(sizeof(bool));
    
    // Jika yang diinputkan tidak valid, maka progra akan meminta user memasukkan tanggal yang valid
    while (true) {
        printf("Masukkan tanggal check-in (dd/mm/yyyy): ");
        scanf("%s", tglInput);
        
        // value nya disimpen dulu kaena pas proses di isTglValid maka pointer akan ngambil yang depannya doang
        strcpy(tglCheckIn, tglInput);
        tanggalValid = isTglValid(tglInput);
        
        checkInValid = isTglCheckInValid(tglInput);
        
        if (*checkInValid && *tanggalValid) {
            break;
        } else {
            printf("Tanggal yang anda masukkan tidak valid. Silakan coba lagi.\n");
        }
    }
    
    free(tglInput);
    return tglCheckIn;
}

// Fungsi untuk menginputkan tanggal Check Out , tanggal Check In dibutuhkan untuk valdiasi tangal check out
char *inputTanggalCheckOut(char *tanggalCheckIn){
	
	// Deklrasai variabel pointer memesan memori kosong dengan ukuran yang ditentukan sesuai kebutuhan
	char *tglCheckOut = (char * )malloc(11 * sizeof(char)); // Alokasikan memori untuk menyimpan tanggal
	char *tanggalCheckOut = (char * )malloc(11 * sizeof(char));
    bool *tanggalValid = (bool *)malloc(sizeof(bool));
    bool *checkOutValid = (bool *)malloc(sizeof(bool));
    
    // Jika yang diinputkan tidak valid, maka progra akan meminta user memasukkan tanggal yang valid
    // Syarat untuk valid yaitu tanggal valid dan pastikan tanggal CheckOut sesudah tanggal CheckIn
    while (true) {
        printf("Masukkan tanggal check-Out (dd/mm/yyyy): ");
        scanf("%s", tglCheckOut);
        
        // Menyimpan value tglCheckOut ke tanggalcheckout karena tglCheckOut bakal dipake
        strcpy(tanggalCheckOut, tglCheckOut); 
        
        tanggalValid = isTglValid(tglCheckOut);
        
        // Menyimpan value tglCheckOut ke tglCheckOut karena tanggalcheckout bakal dipake
        strcpy(tglCheckOut, tanggalCheckOut); 
        
        checkOutValid = isTglCheckOutValid(tanggalCheckIn, tanggalCheckOut);
        
    
        if (*tanggalValid && *checkOutValid) {
            break;
        } else {
            printf("Tanggal yang anda masukkan tidak valid. Silakan coba lagi.\n");
        }
    }
    
    // Yang di kembalikan yang disimpan terakhir karena valuenya tidak berubah
    return tglCheckOut;
}

// Fungsi untuk mengetahui hari yang diinputkan hari ke berapa dalam satu tahun
int hariDalamTahun(char *tanggal) {
	
    // Simpan salinan tanggalCheckIn
    char tempTanggal[100];
    strcpy(tempTanggal, tanggal);
    int totHari = 0;
    int tempBulan = 0;
    int daftarBulanNonKabisat[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daftarBulanKabisat[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int *daftarBulan;

    int hari = atoi(strtok(tempTanggal, "/"));
    int bulan = atoi(strtok(NULL, "/"));
    int tahun = atoi(strtok(NULL, "/"));

    if (tahun % 4 == 0 && tahun % 100 != 0) {
        daftarBulan = daftarBulanKabisat;
    } else {
        daftarBulan = daftarBulanNonKabisat;
    }

    if (bulan != 1) {
        for (tempBulan = 0; tempBulan < bulan-1; tempBulan++) {
            totHari += daftarBulan[tempBulan];
        }
    }
    
    totHari += hari;
    return totHari;
}

// Fungsi untuk mengetahui total menginap berapa hari
int hitungHariMenginap(char *tanggalCheckIn, char *tanggalCheckOut){
	int jmlHari = 0;
	
	int jmlHariCheckIn = hariDalamTahun(tanggalCheckIn);
	int jmlHariCheckOut = hariDalamTahun(tanggalCheckOut);
	
	jmlHari = jmlHariCheckOut - jmlHariCheckIn;
	if(jmlHari < 0){
		jmlHari += 366; // karena 2024 kabisat jadi ditambah 266
	}
		
	return jmlHari;
}

// Fungsi untuk memeriksa apakah nomor kamar sudah ada di dalam file
bool isKamarExists(int noKamar) {
    FILE *file = fopen(dbsPemesanan, "r+");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        exit(1);
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        // Membaca nomor kamar dari setiap baris dalam file
        char *token = strtok(line, ",");
		token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        int kamar = atoi(dekripsi(token)); // ngambil nomor kamar, dekrip dan diubah ke bentuk int
        // Jika nomor kamar sudah ada dalam file, kembalikan true
        
        if (kamar == noKamar) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

// Fungsi untuk memberikan nomor kamar random
int kamar() {
    int noKmr;

    srand(time(NULL)); // Inisialisasi generator nomor acak

    do {
        noKmr = rand() % (maxKamar - minKamar + 1) + minKamar;
    } while (isKamarExists(noKmr));

    return noKmr;
}

// Untuk menampilkan harga yang dipisahkan dengan .
void disHarga(int harga) {
   if (harga < 1000) {
       printf("%d", harga);
       return;
   }
   disHarga(harga / 1000);
   printf(".%03d", harga % 1000);
}


// Untuk menghitung ada berapa baris di file
int hitungBaris() {
    FILE *file = fopen("database/pemesananHotel.txt", "r+");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }

    int baris = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            baris++;
        }
    }

    fclose(file);
    return baris;
}

// Fungsi untuk memperbarui baris dengan nomor tertentu
void updateBaris(char *baris, int nomor) {
    char *delim = ",";
    
    char *Nomer = strtok(baris, delim);
    char *Username = strtok(NULL, delim);
    char *CheckIn = strtok(NULL, delim);
    char *CheckOut = strtok(NULL, delim);
    char *Hari = strtok(NULL, delim);
    char *Harga = strtok(NULL, delim);
    char *Potongan = strtok(NULL, delim);
    char *Total = strtok(NULL, delim);
    char *NoKamar = strtok(NULL, delim);
    char *Stats = strtok(NULL, delim);

	if (atoi(Nomer) == nomor) { // Mengubah string ke integer dan membandingkan dengan nomor
	    strcpy(Stats, "SUKSES"); // Mengganti stats dengan "SUKSES"
	}
	sprintf(baris, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\n", Nomer, Username, CheckIn, CheckOut, Hari, Harga, Potongan, Total, NoKamar, Stats);
}

// Prosedur untuk approval admin mana yang sudah berhasil mana yang belum
void adminApprove(int nomorDicari){
	const char *namaFileInput = "database/pemesananHotel.txt";
    const char *namaFileOutput = "database/pemesananHotelTemp.txt";

    FILE *fileInput = fopen(namaFileInput, "r+");
    FILE *fileOutput = fopen(namaFileOutput, "w+");

    if (fileInput == NULL || fileOutput == NULL) {
        printf("Gagal membuka file.\n");
    }

    char baris[100];

    // Menulis hasil ke file output
    while (fgets(baris, sizeof(baris), fileInput)) {
        char *dekripPemesanan = dekripsi(baris);
        
        updateBaris(dekripPemesanan, nomorDicari); // Mencari nomor yang dicari
        char *enkripPemesanan = enkripsi(dekripPemesanan);
        char *test = dekripsi(enkripPemesanan);
        
        fprintf(fileOutput, "%s", enkripPemesanan);
    }

    fclose(fileInput);
    fclose(fileOutput);

    // Membuka kembali file input dalam mode write-only untuk menulis ulang isinya
    fileInput = fopen(namaFileInput, "w");
    fileOutput = fopen(namaFileOutput, "r+");

    // Menyalin isi file output ke file input
    while (fgets(baris, sizeof(baris), fileOutput)) {
        fprintf(fileInput, "%s", baris);
    }

    fclose(fileInput);
    fclose(fileOutput);
}

// Untuk tampilan yang dilihat oleh admin
void disPemesananAdmin(){
	int i;
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
    	printf("| %-3s | %-10s | %-12s | %-12s | %-4s |",noOrder,namaCust, CI, CO, hari);printf("     Rp. ");disHarga(atoi(harga));printf("\t| %-4s%% |", ptgan);printf("     Rp. ");disHarga(atoi(total));printf("\t| %-7s | %-10s |\n", no, status);
    }
    printf("+--------------------------------------------------------------------------------------------------------------------------------------+\n");
	fclose(files);
}

// Prosedur ini untuk user memesan hotel
void pemesananHotel(char username[]){
	char *prompt = (char *)malloc(10 * sizeof(char)); // yang akan dituliskan ke dalam file

	char coupon[MAX_COUPON_LENGTH]; // % untuk kupon 
	system("cls");
	printf(" /$$   /$$  /$$$$$$  /$$$$$$$$ /$$$$$$$$ /$$                /$$$$$ /$$$$$$$$ /$$$$$$$$ /$$$$$$$$ /$$   /$$  /$$$$$$ \n");
	printf("| $$  | $$ /$$__  $$|__  $$__/| $$_____/| $$               |__  $$| $$_____/|__  $$__/| $$_____/| $$  /$$/ /$$__  $$\n");
	printf("| $$  | $$| $$  \\ $$   | $$   | $$      | $$                  | $$| $$         | $$   | $$      | $$ /$$/ | $$  \\ $$\n");
	printf("| $$$$$$$$| $$  | $$   | $$   | $$$$$   | $$                  | $$| $$$$$      | $$   | $$$$$   | $$$$$/  | $$$$$$$$\n");
	printf("| $$__  $$| $$  | $$   | $$   | $$__/   | $$             /$$  | $$| $$__/      | $$   | $$__/   | $$  $$  | $$__  $$\n");
	printf("| $$  | $$| $$  | $$   | $$   | $$      | $$            | $$  | $$| $$         | $$   | $$      | $$\\  $$ | $$  | $$\n");
	printf("| $$  | $$|  $$$$$$/   | $$   | $$$$$$$$| $$$$$$$$      |  $$$$$$/| $$$$$$$$   | $$   | $$$$$$$$| $$ \\  $$| $$  | $$\n");
	printf("|__/  |__/ \\______/    |__/   |________/|________/       \\______/ |________/   |__/   |________/|__/  \\__/|__/  |__/\n");
	printf("Harga per malam : Rp. ");disHarga(hargaPerMalam);
	printf("\n\n");
	
	
    char *tanggalCheckIn = inputTanggalCheckIn();     
    printf("Tanggal check-in: %s\n", tanggalCheckIn);
    
    char *tanggalCheckOut = inputTanggalCheckOut(tanggalCheckIn);    
    printf("Tanggal check-out: %s\n", tanggalCheckOut);
    
    int pilihan;
    int potongan;
    printf("Apakah anda ingin menggunakan kupon?\n(1) Ya\n(2) Tidak\n");
    printf("Masukkan pilihan anda: ");
    scanf("%d", &pilihan);
    
    if (pilihan == 1) {
    	potongan = kupon(coupon); // melakukan read coupon
	}
    
    clearScreen();
    
    int totalHariMenginap = hitungHariMenginap(tanggalCheckIn, tanggalCheckOut);
    
	int hargaMenginap = totalHariMenginap*hargaPerMalam;
	//totHarga = hargaMenginap;
	
	int noKamar = 0;
	
	int jumlahBaris = hitungBaris();
    int no = jumlahBaris + 1;
    
    double hasil = hargaMenginap - (hargaMenginap*(double)potongan/100); // menghitung total harga setelah di diskon
    int totHarga = (int) hasil; // mengubah bentuk double ke int
    char stats[30] = "Dlm Antrian...";
    
    system("cls");
	printf(" /$$   /$$  /$$$$$$  /$$$$$$$$ /$$$$$$$$ /$$                /$$$$$ /$$$$$$$$ /$$$$$$$$ /$$$$$$$$ /$$   /$$  /$$$$$$ \n");
	printf("| $$  | $$ /$$__  $$|__  $$__/| $$_____/| $$               |__  $$| $$_____/|__  $$__/| $$_____/| $$  /$$/ /$$__  $$\n");
	printf("| $$  | $$| $$  \\ $$   | $$   | $$      | $$                  | $$| $$         | $$   | $$      | $$ /$$/ | $$  \\ $$\n");
	printf("| $$$$$$$$| $$  | $$   | $$   | $$$$$   | $$                  | $$| $$$$$      | $$   | $$$$$   | $$$$$/  | $$$$$$$$\n");
	printf("| $$__  $$| $$  | $$   | $$   | $$__/   | $$             /$$  | $$| $$__/      | $$   | $$__/   | $$  $$  | $$__  $$\n");
	printf("| $$  | $$| $$  | $$   | $$   | $$      | $$            | $$  | $$| $$         | $$   | $$      | $$\\  $$ | $$  | $$\n");
	printf("| $$  | $$|  $$$$$$/   | $$   | $$$$$$$$| $$$$$$$$      |  $$$$$$/| $$$$$$$$   | $$   | $$$$$$$$| $$ \\  $$| $$  | $$\n");
	printf("|__/  |__/ \\______/    |__/   |________/|________/       \\______/ |________/   |__/   |________/|__/  \\__/|__/  |__/\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n\n");
    
    printf("Berikut rincian pesanan anda\n\n");
	printf("Tanggal CheckIn\t : %s\nTanggal CheckOut : %s\nTotal menginap\t : %d hari\nNo kamar\t : -\n", tanggalCheckIn, tanggalCheckOut, totalHariMenginap);
	printf("Harga\t\t : Rp. ");disHarga(hargaMenginap);
	printf("\nPotongan\t : %d%%", potongan);
	printf("\nTotal Harga\t : Rp. ");disHarga(totHarga);printf("\n\n");

//    if(confirmPay(username)){
//	    if(isSaldoCukup(username, hasil)){ // cek apakah saldo cukup
//	    
//	    	strcpy(stats, "BERHASIL");
//	    	noKamar = kamar();
//		} else {
//			strcpy(stats, "GAGAL");
//		}
//	
//	} else { 
//		strcpy(stats, "GAGAL");
//	}
    
	system("cls");
	printf(" /$$   /$$  /$$$$$$  /$$$$$$$$ /$$$$$$$$ /$$                /$$$$$ /$$$$$$$$ /$$$$$$$$ /$$$$$$$$ /$$   /$$  /$$$$$$ \n");
	printf("| $$  | $$ /$$__  $$|__  $$__/| $$_____/| $$               |__  $$| $$_____/|__  $$__/| $$_____/| $$  /$$/ /$$__  $$\n");
	printf("| $$  | $$| $$  \\ $$   | $$   | $$      | $$                  | $$| $$         | $$   | $$      | $$ /$$/ | $$  \\ $$\n");
	printf("| $$$$$$$$| $$  | $$   | $$   | $$$$$   | $$                  | $$| $$$$$      | $$   | $$$$$   | $$$$$/  | $$$$$$$$\n");
	printf("| $$__  $$| $$  | $$   | $$   | $$__/   | $$             /$$  | $$| $$__/      | $$   | $$__/   | $$  $$  | $$__  $$\n");
	printf("| $$  | $$| $$  | $$   | $$   | $$      | $$            | $$  | $$| $$         | $$   | $$      | $$\\  $$ | $$  | $$\n");
	printf("| $$  | $$|  $$$$$$/   | $$   | $$$$$$$$| $$$$$$$$      |  $$$$$$/| $$$$$$$$   | $$   | $$$$$$$$| $$ \\  $$| $$  | $$\n");
	printf("|__/  |__/ \\______/    |__/   |________/|________/       \\______/ |________/   |__/   |________/|__/  \\__/|__/  |__/\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n\n");
    
	printf("Berikut rincian pesanan anda\n\n");
	printf("Tanggal CheckIn\t : %s\nTanggal CheckOut : %s\nTotal menginap\t : %d hari\nNo kamar\t : %d\n", tanggalCheckIn, tanggalCheckOut, totalHariMenginap, noKamar);
	printf("Harga\t\t : Rp. ");disHarga(hargaMenginap);
	printf("\nPotongan\t : %d%%", potongan);
	printf("\nTotal Harga\t : Rp. ");disHarga(totHarga);
	printf("\nStatus\t\t : %s", stats);

    // Menggabungkan tanggal check-in dan check-out ke dalam variabel prompt
	sprintf(prompt, "%d,%s,%s,%s,%d,%d,%d,%d,%d,%s", no,username,tanggalCheckIn, tanggalCheckOut, totalHariMenginap, hargaMenginap, potongan, totHarga, noKamar, stats);
	
	// Enkripsi prompt
    char* enkripsiPesanan = enkripsi(prompt);
    
    
	insert(&head, prompt);
	
    FILE *file = fopen(dbsPemesanan, "a"); // membuka dile dengan mode append atau mode menambahkan
    if (file == NULL) {
        printf("Gagal membuka file.\n");
    }
    
    fprintf(file, "%s,\n", enkripsiPesanan); // menulis ke file
    
	
    fclose(file);
    printf("\n");
    printList(head);
}

// Prosedur untuk menampilkan pesanan ke user berdasarkan username
void disPemesananUser(char username[]){
	FILE *fileInput = fopen(dbsPemesanan, "r+");
	if (fileInput == NULL) {
        printf("Gagal membuka file.\n");
    }
    char baris[100];
    printf("+--------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| %-3s | %-10s | %-12s | %-12s | %-4s | %-21s | %-4s | %-21s | %-6s | %-10s |\n", "No", " Username", "  CheckIn", "  CheckOut", "Hari", "        Harga","Kupon", "        Total", "NoKamar", "status");
    printf("|-----+------------+--------------+--------------+------+-----------------------+-------+-----------------------+---------+------------|\n");

    while (fgets(baris, sizeof(baris), fileInput)) {
    	char *dekripPemesanan = dekripsi(baris);
    	
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
	
		if (!strcmp(namaCust, username)) {
	    	printf("| %-3s | %-10s | %-12s | %-12s | %-4s |",noOrder,namaCust, CI, CO, hari);printf("     Rp. ");disHarga(atoi(harga));printf("\t| %-4s%% |", ptgan);printf("     Rp. ");disHarga(atoi(total));printf("\t| %-7s | %-10s |\n", no, status);
    	}
	}
    printf("+--------------------------------------------------------------------------------------------------------------------------------------+\n");
	fclose(fileInput);
}

// Fungsi untuk menambahkan node baru ke linked list
void insert(struct Node** head_ref, char new_data[]) {
    // Alokasikan memori untuk node baru
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    strcpy(new_node->data, new_data); // Salin data ke node baru

    // Jika linked list kosong, atur node baru sebagai head dan membuatnya menunjuk ke dirinya sendiri
    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = *head_ref;
    } else {
        // Temukan node terakhir dalam linked list
        struct Node* last = *head_ref;
        while (last->next != *head_ref)
            last = last->next;

        // Tambahkan node baru di akhir dan atur next-nya menjadi head
        last->next = new_node;
        new_node->next = *head_ref;
    }
}

// Fungsi untuk menghapus node paling depan dari linked list
void deleteFront(struct Node** head_ref) {
    if (*head_ref == NULL) // Kosong
        return;

    struct Node* temp = *head_ref;
    // Jika linked list hanya memiliki satu node
    if (temp->next == *head_ref) {
        *head_ref = NULL;
        free(temp);
        return;
    }

    // Temukan node terakhir dan atur next-nya menjadi node kedua
    struct Node* last = *head_ref;
    while (last->next != *head_ref)
        last = last->next;
    last->next = (*head_ref)->next;

    // Pindahkan head ke node kedua dan hapus node pertama
    *head_ref = (*head_ref)->next;
    free(temp);
}

// Fungsi untuk mencetak isi linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    if (head != NULL) {
        do {
            printf("%s -> ", temp->data);
            temp = temp->next;
        } while (temp != head);
//        printf("Head\n");
    }
}
