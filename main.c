#include "DSA/bst.h"
#include "DSA/graph.h"
#include "DSA/maxheap.h"
#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Inisialisasi Struktur data inti
    P_Node rootBST = NULL;
    GraphPtr graph = NULL;

    // Memuat semua data ke memori langsung
    int totalKursus = loadDataToSystem(&rootBST, &graph);
    int pilihan;
    int poinBawaan = 0;
    char jawab;
    do {
        clearScreen();
        printLogo();
        
        printf(BOLD "MENU UTAMA:\n" RESET);
        printf("1. " BLUE "Lihat Daftar Profesi" RESET "\n");
        printf("2. " GREEN "Lihat Daftar Kursus & Prasyarat" RESET "\n");
        printf("3. " MAGENTA "Kalkulator Transisi Karier" RESET "\n");
        printf("4. " RED "Keluar" RESET "\n\n");
        
        printf("Masukkan pilihan Kamu [1-4]: ");
        if (scanf("%d", &pilihan) != 1) {
            printf("Input harus angka\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch(pilihan) {
            // Opsi 1 Menampilkan Daftar profesi yang tersedia dari data
            case 1:
                clearScreen();
                printf(BLUE BOLD "===================================== DAFTAR PROFESI =====================================\n" RESET);
                printf("==========================================================================================\n");
                printf("| ID   | Nama Profesi Target                                               |Skill Points |\n");
                printf("==========================================================================================\n");
                if (rootBST != NULL) {
                    printInOrder(rootBST);
                } else {
                    printf (RED "Data basis profesi kosong atau gagal dimuat\n" RESET);
                }

                printf("==========================================================================================\n");

                printf ("\nTekan enter untuk kembali ke menu utama...");
                getchar(); 
                getchar();
                break;
            
            // Opsi 2 Daftar list course yang tersedia
            case 2:
                clearScreen();
                printf(BLUE BOLD "========================================= COURSE =========================================\n" RESET);
                if (graph != NULL) {
                    displayGraph(graph);
                } else {
                    printf (RED "Data basis graf kosong\n" RESET);
                }

                printf("==========================================================================================\n");
                
                printf("\nTekan Enter untuk kembali...");
                getchar();
                getchar();
                break;
            // Opsi 3 Kalkulator Transisi Karier  
            case 3: {
                clearScreen();
                
                printf(MAGENTA BOLD "============= KALKULATOR TRANSISI KARIER =============\n" RESET);
                printf(CYAN "Tahap 1: Asesmen Fundamental Era AI\n" RESET);
                printf("Jawab dengan huruf " GREEN "[Y] untuk YA" RESET " atau " RED "[N] untuk TIDAK" RESET ".\n\n");
                
                // Menyimpan pertanyaan ke dalam Array
                const char *pertanyaan[5] = {
                    "1. Mudah beradaptasi dengan aplikasi/software baru? [Y/N]: ",
                    "2. Terbiasa membaca data dari tabel/grafik laporan? [Y/N]: ",
                    "3. Terbiasa memecah masalah rumit jadi langkah kecil? [Y/N]: ",
                    "4. Pernah menggunakan AI (ChatGPT/Gemini/Claude) untuk bekerja? [Y/N]: ",
                    "5. Berpengalaman dalam negosiasi/pelayanan manusia? [Y/N]: "
                };

                // Looping untuk menanyakan 5 soal
                for (int i = 0; i < 5; i++) {
                    // Looping yang tidak akan lanjut sebelum Y/N
                    while (1) {
                        printf("%s", pertanyaan[i]);
                        scanf(" %c", &jawab);

                        while(getchar() != '\n'); 

                        // Validasi Input user
                        if (jawab == 'Y' || jawab == 'y') {
                            poinBawaan += 10;
                            break;
                        } else if (jawab == 'N' || jawab == 'n') {
                            break;
                        } else {
                            // Jika input bukan y/n, program akan memperingati user dan mengulang soal yang sama
                            printf(RED "    [!] Input tidak valid! Hanya menerima huruf Y atau N.\n" RESET);
                        }
                    }
                }

                printf("\n" YELLOW "-> Modal Skill Points (SP) Anda: %d SP\n\n" RESET, poinBawaan);
                
                // Pemilihan profesi target
                printf(CYAN "Tahap 2: Pemilihan Profesi Target\n" RESET);
                
                char careerList;

                while (1) {
                    printf("Apakah Anda ingin menampilkan tabel daftar ID Profesi terlebih dahulu? [Y/N]: ");
                    scanf(" %c", &careerList);
                    while(getchar() != '\n');

                    if (careerList == 'Y' || careerList == 'y' || careerList == 'N' || careerList == 'n') {
                        break;
                    } else {
                        printf(RED "    [!] Input tidak valid! Hanya menerima huruf Y atau N.\n" RESET);
                    }
                }
                
                if (careerList == 'Y' || careerList== 'y') {
                    printf("\n==========================================================================================\n");
                    printf("| ID   | Nama Profesi Target                                               | Syarat Poin |\n");
                    printf("==========================================================================================\n");
                    
                    if (rootBST != NULL) {
                        printInOrder(rootBST);
                    } else {
                        printf("| " RED "Data basis profesi kosong atau gagal dimuat!" RESET "                                          |\n");
                    }
                    
                    printf("==========================================================================================\n\n");
                }
                
                int idTarget;
                P_Node target = NULL;

                while (1) {
                    printf("Masukkan " YELLOW "ID Profesi" RESET " target Anda (Contoh: 67): ");
                    
                    // Cek jika input gagal dibaca sebagai angka
                    if (scanf("%d", &idTarget) != 1) {
                        printf(RED "    [!] Input tidak valid! Masukkan format angka (Contoh: 67).\n" RESET);
                        while(getchar() != '\n');
                        continue;
                    }
                    
                    // Melakukan pencarian data profesi menggunakan fungsi ID 
                    target = searchProfession(rootBST, idTarget);
                    
                    // Cek jika angka ID tidak ada
                    if (target == NULL) {
                        printf(RED "    [!] Maaf, profesi dengan ID '%d' tidak ditemukan di sistem. Silakan coba lagi.\n" RESET, idTarget);
                        continue; 
                    }
                    break; 
                }
                int skillGap = target->required_sp - poinBawaan;

                printf ("\n[Sistem Menganasilis...]\n");
                printf ("Target Profesi : %s (" GREEN "%d SP" RESET ")\n", target->name, target->required_sp);

                if (skillGap <= 0 ) {
                    printf ("Skill Gap Kamu : " GREEN "0 SP\n\n" RESET);
                    printf (GREEN BOLD "Keterampilan Anda saat ini sudah memenuhi syarat mutlak untuk profesi ini!\n" RESET);
                } else {
                    printf ("Skill Gap Kamu : " RED "%d SP\n\n" RESET, skillGap);
                    printf (CYAN "Tahap 3: Optimasi Jalur Reskilling\n" RESET);
                    printf ("Menyusun urutan kursus prioritas terbalik untuk menutupi %d SP...\n\n", skillGap);
                    
                    int *current_in_degree = (int*)malloc(totalKursus * sizeof(int));
                    int *is_entered_heap = (int*)malloc(totalKursus * sizeof(int));
                    
                    // Melakukan copy in-degree agar graf utama tidak rusak atau terputus permanen
                    for (int i = 0; i < totalKursus; i++) {
                        current_in_degree[i] = graph->in_degree[i];
                        is_entered_heap[i] = 0;
                    }
                    // Membuat kapasistas struct Maxheap dinamis sebanyak jumlah kursus
                    MaxheapPtr heap = createMaxHeap(totalKursus);

                    // Memasukkan semua kursus dasar dengan in degree awal 0 kedalam Max-Heap
                    for (int i = 0; i < totalKursus; i++) {
                        if (current_in_degree[i] == 0) {
                            insertHeap(heap, i, graph->courses[i].sp_value);
                            is_entered_heap[i] = 1;
                        }
                    }
                    printf (BOLD "Learning Path Rekomendasi Optimal:\n" RESET);
                    int step = 1;

                    // Mengekstrak prioritas teratas agar SP terpenuhi
                    while (skillGap > 0 && !isEmptyHeap(heap)) {
                        HeapElement kursusTerbaik = extractMax(heap);
                        int id = kursusTerbaik.course_id;

                        printf (" %d. %s (" GREEN "+%d SP" RESET ")\n", step++, graph->courses[id].course_name, kursusTerbaik.sp_value);
                        skillGap -= kursusTerbaik.sp_value;

                        CourseNPtr neighborNode = graph->adjList[id];
                        while (neighborNode != NULL) {
                            int neighborId = neighborNode->course_id;
                            current_in_degree[neighborId]--;

                            // Jika in degree = 0 maka masuk ke Max-Heap
                            if (current_in_degree[neighborId] == 0 && !is_entered_heap[neighborId]) {
                                insertHeap(heap, neighborId, graph->courses[neighborId].sp_value);
                            }
                            neighborNode = neighborNode->next;
                        }
                    }
                    if (skillGap <= 0) {
                        printf(GREEN BOLD "\n[STATUS] Sukses! Skill Gap terpenuhi. Rencana transisi karier Anda valid.\n" RESET);
                    } else {
                            printf(RED BOLD "\n[STATUS] Perhatian: Jalur terhenti. Pilihan kurikulum tidak mencukupi target celah poin.\n" RESET);
                    }
                    freeMaxHeap(heap);
                }
                printf ("\n Tekan enter untuk kembali ke menu utama...");
                getchar();
                getchar();
                break;
            }
            
            // Opsi 4 Exit program dengan memfreekan memori
            case 4:
                clearScreen();
                printLogo();
                printf(GREEN BOLD "\nTerima kasih telah menggunakan sistem Re-Skill!\n" RESET);
                printf("Semoga transisi karier Anda sukses.\n");
                printf("Membebaskan alokasi memori internal dari sistem...\n");
                freeBST(rootBST);
                freeGraph(graph);
                printf("Selesai. Selamat bertransisi karier!\n\n");
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