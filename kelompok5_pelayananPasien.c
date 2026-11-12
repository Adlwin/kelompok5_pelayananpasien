#include <stdio.h>

// Array 2D untuk menyimpan daftar nama penyakit
char penyakitDalam[3][30] = {"Maag / Asam Lambung", "Diabetes", "Asma"};
float hargaDalam[3] = {80000, 150000, 120000};

char penyakitLuar[3][30] = {"Luka Bakar", "Bisul", "Jamur Kulit"};
float hargaLuar[3] = {60000, 50000, 40000};

// Fungsi mengembalikan pointer teks dosis
char* menentukanDosis(int umur, char kelamin) {
    if (umur < 12) {
        return "Dosis Anak (1/2 Tablet)";
    } else if (umur <= 60) {
        if (kelamin == 'L' || kelamin == 'l') {
            return "Dosis Dewasa Pria (1 Tablet)";
        } else {
            return "Dosis Dewasa Wanita (1 Tablet)";
        }
    } else {
        return "Dosis Lansia (1/2 Tablet)";
    }
}

// Prosedur cetak struk pembayaran
void cetakStruk(char nama[], int umur, char kelamin, char namaPenyakit[], 
                char dosis[], int kodeBPJS, float hargaAwal, float diskon, float totalBayar) {
    printf("\n==================================================\n");
    printf("              STRUK PEMBAYARAN OBAT               \n");
    printf("==================================================\n");
    printf(" Nama Pasien     : %s\n", nama);
    printf(" Umur            : %d Tahun\n", umur);
    printf(" Jenis Kelamin   : %c\n", kelamin);
    printf(" Diagnosa        : %s\n", namaPenyakit);
    printf(" Aturan Dosis    : %s\n", dosis);
    printf(" Kode BPJS       : %d\n", kodeBPJS);
    printf("--------------------------------------------------\n");
    printf(" Harga Obat      : Rp %.0f\n", hargaAwal);
    printf(" Diskon BPJS     : %.0f%%\n", diskon * 100);
    printf(" Potongan        : Rp %.0f\n", hargaAwal * diskon);
    printf("--------------------------------------------------\n");
    printf(" TOTAL BAYAR     : Rp %.0f\n", totalBayar);
    printf("==================================================\n");
}

int main() {
    char nama[50], kelamin;
    char *dosis, *namaPenyakit;
    int umur, kategori, pilihPenyakit, kodeBPJS;
    float hargaAwal = 0, diskon = 0, totalBayar = 0;
    char ulang;

    do {
        printf("=== PROGRAM PEMERIKSAAN & PEMBAYARAN OBAT ===\n");
        printf("Masukkan Nama          : ");
        scanf(" %[^\n]", nama);
        
        printf("Masukkan Umur          : ");
        // Validasi input angka umur & pembersihan buffer
        while (scanf("%d", &umur) != 1 || umur <= 0) {
            printf("Input harus berupa angka positif! Masukkan Umur kembali: ");
            while (getchar() != '\n'); 
        }
        while (getchar() != '\n'); 

        // Validasi input gender (L/P)
        while (1) {
            printf("Jenis Kelamin (L/P)    : ");
            scanf(" %c", &kelamin);
            if (kelamin == 'L' || kelamin == 'l' || kelamin == 'P' || kelamin == 'p') {
                break;
            }
            printf("Input salah! Masukkan L atau P.\n");
        }

        // Panggil fungsi penentu dosis
        dosis = menentukanDosis(umur, kelamin);

        // Validasi Kategori Penyakit (Harus 1 atau 2)
        while (1) {
            printf("\nPilih Kategori Penyakit:\n");
            printf("1. Penyakit Dalam\n");
            printf("2. Penyakit Luar\n");
            printf("Pilihan (1/2): ");
            
            if (scanf("%d", &kategori) == 1 && (kategori == 1 || kategori == 2)) {
                break; // Keluar dari loop jika input 1 atau 2
            }
            printf("Kategori tidak valid! Silakan masukkan angka 1 atau 2.\n");
            while (getchar() != '\n'); // Membersihkan sisa input di buffer
        }

        // Switch Case untuk Pemilihan Penyakit Spesifik
        switch (kategori) {
            case 1:
                while (1) {
                    printf("\n--- Daftar Penyakit Dalam ---\n");
                    for (int i = 0; i < 3; i++) {
                        printf("%d. %s - Rp %.0f\n", i + 1, penyakitDalam[i], hargaDalam[i]);
                    }
                    printf("Pilih Penyakit (1-3): ");
                    
                    if (scanf("%d", &pilihPenyakit) == 1 && pilihPenyakit >= 1 && pilihPenyakit <= 3) {
                        break; // Keluar dari loop jika input 1, 2, atau 3
                    }
                    printf("Pilihan penyakit tidak valid! Silakan masukkan angka 1 sampai 3.\n");
                    while (getchar() != '\n');
                }
                
                namaPenyakit = penyakitDalam[pilihPenyakit - 1];
                hargaAwal = hargaDalam[pilihPenyakit - 1];
                break;

            case 2:
                while (1) {
                    printf("\n--- Daftar Penyakit Luar ---\n");
                    for (int i = 0; i < 3; i++) {
                        printf("%d. %s - Rp %.0f\n", i + 1, penyakitLuar[i], hargaLuar[i]);
                    }
                    printf("Pilih Penyakit (1-3): ");
                    
                    if (scanf("%d", &pilihPenyakit) == 1 && pilihPenyakit >= 1 && pilihPenyakit <= 3) {
                        break; // Keluar dari loop jika input 1, 2, atau 3
                    }
                    printf("Pilihan penyakit tidak valid! Silakan masukkan angka 1 sampai 3.\n");
                    while (getchar() != '\n');
                }
                
                namaPenyakit = penyakitLuar[pilihPenyakit - 1];
                hargaAwal = hargaLuar[pilihPenyakit - 1];
                break;
        }

        // Input Kode BPJS dalam bentuk angka
        printf("\nMasukkan Kode BPJS. (0 Jika tidak ada): ");
        scanf("%d", &kodeBPJS);

        // Logika IF-ELSE BPJS menggunakan operator ==
        if (kodeBPJS == 2026) {
            if (kategori == 1) {
                diskon = 0.50; // Diskon 50% untuk penyakit dalam
            } else if (kategori == 2) {
                diskon = 1.00; // Diskon 100% (gratis) untuk penyakit luar
            }
        } else {
            diskon = 0.00; // Tidak ada diskon
        }

        // Hitung Total Pembayaran
        totalBayar = hargaAwal - (hargaAwal * diskon);

        // Panggil Prosedur Cetak Struk
        cetakStruk(nama, umur, kelamin, namaPenyakit, dosis, kodeBPJS, hargaAwal, diskon, totalBayar);

      
        printf("\nProses pasien lain? (y jika ingin mengulang): ");
        scanf(" %c", &ulang);

    } while (ulang == 'y' || ulang == 'Y');

    printf("\nProgram selesai.\n");
    return 0;
}