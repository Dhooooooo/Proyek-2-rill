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
void pilihSeat(char* seat, int* gerbong);
int validasiStasiun(char* stasiun, int jenisKeretaPilihan);
void konfirmasiPembayaran(Tiket* tiket);

#endif

