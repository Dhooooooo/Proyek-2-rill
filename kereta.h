#ifndef kereta_h
#define kereta_h

typedef struct {
    char nama[50];
    char nik[20];
} Penumpang;

typedef struct {
    char stasiunKeberangkatan[50];
    char stasiunTujuan[50];
    char jenisKereta[20];
    char jadwal[20];
    char seat[10];
    int gerbong;
    Penumpang penumpang;
} Tiket;

void pilihJadwal(char* jadwal);
void inputDataDiri(Penumpang* penumpang);
void pilihSeat(char* seat, int* gerbong, Penumpang* penumpang, const char* jadwal);
int validasiStasiun(char* stasiun, int jenisKeretaPilihan);
void inputStasiun(Tiket* tiket, int jenisKeretaPilihan);
int konfirmasiPembayaran(Tiket* tiket);
int validasiSeat(char* seat, int kelasPilihan);
int cekKetersediaanSeat(const char* filename, const char* seat);
void pesanSeat(const char* filename, const char* seat, const char* namaPenumpang);
void kosongkanSeat(const char* filename, const char* seat);
void listKeretaLokal();
void listKeretaAntarKota();
void spaceToContinue();

#endif

