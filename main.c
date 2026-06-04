#include "bst.h"
#include "graph.h"
#include "maxheap.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Inisialisasi Struktur data inti
    P_Node rootBST = NULL;
    GraphPtr graph = createGraph(TOTALKURSUS);

    // Memuat semua data ke memori langsung
    loadDataToSystem(&rootBST, graph); 

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
        if (scanf("%d", &pilihan) != 1) {
            printf("Input harus angka\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch(pilihan) {
            // Opsi 1 Menampilkan Daftar profesi yang tersedia dari data
            case 1:
                clearScreen();
                printf(BLUE BOLD "=== DAFTAR PROFESI ===\n\n" RESET);
                printf("- Spesialis QA Software (95 SP)\n");
                printf("- Manajer Proyek Digital (110 SP)\n");
                printf("- Analis Data Junior (100 SP)\n\n");
                printf(YELLOW "[!] Fitur struktur data BST akan diintegrasikan di sini.\n" RESET);
                if (rootBST != NULL) {
                    printInOrder(rootBST);
                } else {
                    printf (RED "Data basis profesi kosong atau gagal dimuat\n" RESET);
                }
                printf ("\nTekan enter untuk kembali ke menu utama");
                getchar(); 
                getchar();
                break;
                
            case 2:
                clearScreen();
                if (graph != NULL) {
                    displayGraph(graph);
                } else {
                    printf (RED "Data basis graf kosong\n" RESET);
                }
                
                printf("\nTekan Enter untuk kembali...");
                getchar();
                getchar();
                break;
                
            case 3: {
                clearScreen();
                int poinBawaan = 0;
                int jawab;
                char profesi[150];
                
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
                getchar();
                scanf(" %[^\n]", profesi);

                // Mencari data profesi di BST
                P_Node target = searchProfessionByName(rootBST, profesi);
                if (target == NULL) {
                    printf (RED "\n[!] Maaf, profesi '%s' tidak ditemukan dalam sistem database kami.\n" RESET, profesi);
                    printf ("Pastikan huruf besar dan kecil sesuai dengan data. Tekan enter...");
                    getchar();
                    break;
                }

                int skillGap = target->required_sp - poinBawaan;

                printf ("\n [Sistem Menganasilis...]\n");
                printf ("Target Profesi : %S (" GREEN "%d SP" RESET ") \n ", target->name, target->required_sp);

                if (skillGap <= 0 ) {
                    printf ("Skill Gap kamu : " GREEN "0 SP\n\n" RESET ")\n", target->name, target->required_sp);
                } else {
                    printf("Skill Gap Anda : " RED "%d SP\n\n" RESET, skillGap);
                    printf(CYAN "Tahap 3: Optimasi Jalur Reskilling (Kahn's + Max-Heap + Greedy Loop)\n" RESET);
                    printf("Menyusun urutan kursus prioritas terbalik untuk menutupi %d SP...\n\n", skillGap);
                    
                    int current_in_degree[TOTALKURSUS];
                    int is_entered_heap[TOTALKURSUS]; 
                    
                    // Melakukan copy in-degree agar graf utama tidak rusak atau terputus permanen
                    for (int i = 0; i < TOTALKURSUS; i++) {
                        current_in_degree[i] = graph->in_degree[i];
                        is_entered_heap[i] = 0;
                    }
                    // Membuat kapasistas struct Maxheap dinamis sebanyak jumlah kursus
                    MaxheapPtr heap = createMaxHeap(TOTALKURSUS);

                    // Memasukkan semua kursus dasar dengan in degree awal 0 kedalam Max-Heap
                    for (int i = 0; i < TOTALKURSUS; i++) {
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
                break;
            }
            
            // Opsi 4 Exit program dengan memfreekan memori
            case 4:
                clearScreen();
                printLogo();
                printf(GREEN BOLD "\nTerima kasih telah menggunakan sistem Re-Skill!\n" RESET);
                printf("Semoga transisi karier Anda sukses.\n\n");
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