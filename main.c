
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Deklarasi Kode Warna ANSI
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Fungsi untuk membersihkan layar terminal (Multi-OS)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi untuk menampilkan ASCII Art Logo
void printLogo() {
    printf(CYAN BOLD);
    printf("  ____  _____          _____ _  _____ _     _     \n");
    printf(" |  _ \\| ____|        / ____| |/ /_ _| |   | |    \n");
    printf(" | |_) |  _|   _____ | (___ | ' / | || |   | |    \n");
    printf(" |  _ <| |___ |_____| \\___ \\| . \\ | || |___| |___ \n");
    printf(" |_| \\_\\_____|        |_____/_|\\_\\___|_____|_____|\n");
    printf(RESET);
    printf(YELLOW "  Sistem Otomatisasi Transisi Karier Terdampak AI \n" RESET);
    printf("====================================================\n\n");
}

int main() {
    int pilihan;
    
    do {
        clearScreen();
        printLogo();
        
        printf(BOLD "MENU UTAMA:\n" RESET);
        printf("1. " BLUE "Lihat Daftar Profesi (BST)" RESET "\n");
        printf("2. " GREEN "Lihat Daftar Kursus & Prasyarat (Graph)" RESET "\n");
        printf("3. " MAGENTA "Kalkulator Transisi Karier (Reskilling)" RESET "\n");
        printf("4. " RED "Keluar" RESET "\n\n");
        
        printf("Masukkan pilihan Anda [1-4]: ");
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                clearScreen();
                printf(BLUE BOLD "=== DAFTAR PROFESI (TRAVERSAL BST) ===\n\n" RESET);
                printf("- Spesialis QA Software (95 SP)\n");
                printf("- Manajer Proyek Digital (110 SP)\n");
                printf("- Analis Data Junior (100 SP)\n\n");
                printf(YELLOW "[!] Fitur struktur data BST akan diintegrasikan di sini.\n" RESET);
                
                printf("\nTekan Enter untuk kembali...");
                getchar(); // Membersihkan buffer
                getchar(); // Menunggu input enter
                break;
                
            case 2:
                clearScreen();
                printf(GREEN BOLD "=== DAFTAR KURSUS (ADJACENCY LIST GRAPH) ===\n\n" RESET);
                printf("[0] Literasi Data & Spreadsheet (25 SP) -> Lanjut ke: [2]\n");
                printf("[1] Logika Pemrograman Dasar (20 SP) -> Lanjut ke: [2]\n");
                printf("[2] Visualisasi Data Bisnis (25 SP) -> Syarat: [0], [1]\n\n");
                printf(YELLOW "[!] Fitur struktur data Graph akan diintegrasikan di sini.\n" RESET);
                
                printf("\nTekan Enter untuk kembali...");
                getchar();
                getchar();
                break;
                
            case 3: {
                clearScreen();
                int poinBawaan = 0;
                int jawab;
                char profesi[50];
                
                printf(MAGENTA BOLD "=== KALKULATOR TRANSISI KARIER ===\n" RESET);
                printf(CYAN "Tahap 1: Asesmen Fundamental Era AI\n" RESET);
                printf("Jawab dengan angka " GREEN "[1] untuk YA" RESET " atau " RED "[0] untuk TIDAK" RESET ".\n\n");
                
                printf("1. Mudah beradaptasi dengan aplikasi/software baru? [1/0]: ");
                scanf("%d", &jawab);
                if(jawab == 1) poinBawaan += 10;
                
                printf("2. Terbiasa membaca data dari tabel/grafik laporan? [1/0]: ");
                scanf("%d", &jawab);
                if(jawab == 1) poinBawaan += 10;
                
                printf("3. Terbiasa memecah masalah rumit jadi langkah kecil? [1/0]: ");
                scanf("%d", &jawab);
                if(jawab == 1) poinBawaan += 15;
                
                printf("4. Pernah menggunakan AI (ChatGPT/Gemini) untuk bekerja? [1/0]: ");
                scanf("%d", &jawab);
                if(jawab == 1) poinBawaan += 15;
                
                printf("5. Berpengalaman dalam negosiasi/pelayanan manusia? [1/0]: ");
                scanf("%d", &jawab);
                if(jawab == 1) poinBawaan += 10;
                
                printf("\n" YELLOW "-> Modal Skill Points (SP) Anda: %d SP\n\n" RESET, poinBawaan);
                
                printf(CYAN "Tahap 2: Pemilihan Profesi Target\n" RESET);
                printf("Ketik profesi target (contoh: Analis): ");
                getchar(); // Clear buffer
                fgets(profesi, 50, stdin);
                profesi[strcspn(profesi, "\n")] = 0; // Hapus newline
                
                // Asumsi dummy target = 100 SP
                int targetSP = 100;
                int skillGap = targetSP - poinBawaan;
                
                printf("\n[Sistem Menganalisis...]\n");
                printf("Target Profesi : %s (" GREEN "100 SP" RESET ")\n", profesi);
                printf("Skill Gap Anda : " RED "%d SP\n\n" RESET, skillGap);
                
                if (skillGap <= 0) {
                    printf(GREEN BOLD "Keterampilan Anda sudah memenuhi syarat untuk profesi ini!\n" RESET);
                } else {
                    printf(CYAN "Tahap 3: Optimasi Jalur Reskilling (Max-Heap & Greedy)\n" RESET);
                    printf("Menyusun urutan kursus untuk menutupi %d SP...\n\n", skillGap);
                    
                    // Dummy Output Learning Path
                    printf(BOLD "Learning Path Optimal:\n" RESET);
                    printf("1. Pengantar Literasi Data & Spreadsheet (" GREEN "+25 SP" RESET ")\n");
                    printf("2. Logika Pemrograman Dasar (" GREEN "+20 SP" RESET ")\n");
                    printf("3. Visualisasi Data untuk Bisnis (" GREEN "+25 SP" RESET ")\n\n");
                    
                    printf(GREEN BOLD "[STATUS] Skill Gap Terpenuhi! Anda siap transisi karier.\n" RESET);
                }
                
                printf("\nTekan Enter untuk kembali ke Menu Utama...");
                getchar();
                break;
            }
                
            case 4:
                clearScreen();
                printLogo();
                printf(GREEN BOLD "\nTerima kasih telah menggunakan sistem Re-Skill!\n" RESET);
                printf("Semoga transisi karier Anda sukses.\n\n");
                break;
                
            default:
                printf(RED "\n[!] Pilihan tidak valid. Silakan coba lagi.\n" RESET);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                getchar();
                break;
        }
    } while(pilihan != 4);

    return 0;
}