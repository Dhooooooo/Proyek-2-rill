#include <stdio.h>

void initializeGerbong(const char* filename, int maxSeatRow) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file: %s\n", filename);
        return;
    }

    char seatColumn;
    int seatRow;
    for (seatColumn = 'A'; seatColumn <= 'D'; seatColumn++) {
        for (seatRow = 1; seatRow <= maxSeatRow; seatRow++) {
            fprintf(file, "%c%d <empty>\n", seatColumn, seatRow);
        }
    }
    fclose(file);
}

int main() {
    const char* jadwal[] = {"pagi", "siang", "malam"};
	int i;
	int j;
    // Initialize gerbong 1-3 (kelas eksekutif)
    for (i = 1; i <= 3; i++) {
        for (j = 0; j < 3; j++) {
            char filename[30];
            sprintf(filename, "gerbong%d_%s.txt", i, jadwal[j]);
            initializeGerbong(filename, 12);
        }
    }

    // Initialize gerbong 4-8 (kelas ekonomi)
    for (i = 4; i <= 8; i++) {
        for (j = 0; j < 3; j++) {
            char filename[30];
            sprintf(filename, "gerbong%d_%s.txt", i, jadwal[j]);
            initializeGerbong(filename, 15);
        }
    }

    printf("All gerbong files have been initialized.\n");
    return 0;
}
