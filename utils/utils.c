#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


// Fungsi untuk clearscreen pada terminal
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi logo memakai ANSI-C Art
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

// Fungsi untuk membuat BST seimbang dari array terurut secara rekursif 
void insertBalancedBST(P_Node* root, tempProfesi arr[], int start, int end) {
    if (start > end) {
        return;
    }
    // Mencari elemen tengah untuk dijadikan root atau parent nya
    int mid = (start + end) / 2;

    // Memasukkan nilai tengah kedalam BST memakai fungsi insertProfession
    *root = insertProfession (*root, arr[mid].id, arr[mid].nama, arr[mid].sp);

    // Mengulangi proses yang sama untuk membelah bagian kiri array
    insertBalancedBST (root, arr, start, mid - 1);
    
    // Mengulangi proses yang sama untuk membelah bagian kanan array
    insertBalancedBST (root, arr, mid + 1, end);
}

// Fungsi untuk membaca file data
void loadDataToSystem(P_Node* rootBST, GraphPtr graph) {
    FILE *file = fopen("Data/datasp.txt", "r");
    if (file == NULL) {
        printf(RED "[Error] Gagal memuat file Data/datasp.txt! Pastikan berada di folder yang benar.\n" RESET);
        return;
    }
    char line[256];
    int mode = 0; // 1 = Profesi Target, 2 = Kursus Keterampilan

    // Penyimpanan data profesi sementara dalam array
    tempProfesi arrayProfesi [250];
    int jumlahProfesi = 0;

    while (fgets(line, sizeof(line), file)) {
        // Hapus karakter 'enter' (Linux/Windows) di akhir baris
        line[strcspn(line, "\r\n")] = 0; 
        
        if (strlen(line) == 0) continue; // Skip baris kosong

        // Cek label header untuk mengubah mode parsing
        if (strstr(line, "[PROFESI_TARGET]")) { mode = 1; continue; }
        if (strstr(line, "[KURSUS_KETERAMPILAN]")) { mode = 2; continue; }
        if (strstr(line, "[PROFESI_TERDAMPAK]")) { mode = 3; continue; }

        // PARSING 1: Mengolah teks menjadi Binary Search Tree
        if (mode == 1) {
            int id_angka, sp;
            char nama[100];
            // Potong huruf 'P' lalu ambil angka, nama, dan SP
            if (sscanf(line, "P%d,%[^,],%d", &id_angka, nama, &sp) == 3) {
                arrayProfesi[jumlahProfesi].id = id_angka;
                
                strcpy(arrayProfesi[jumlahProfesi].nama, nama);
                
                arrayProfesi[jumlahProfesi].sp = sp;
                jumlahProfesi++;
            }
        } 

        // PARSING 2: Mengolah teks menjadi Graph & Edge
        else if (mode == 2) {
            char tempLine[256];
            strcpy(tempLine, line);
            
            // Pisahkan teks berdasarkan koma
            char *token_id = strtok(tempLine, ",");
            char *token_nama = strtok(NULL, ",");
            char *token_sp = strtok(NULL, ",");
            char *token_syarat = strtok(NULL, ",");

             if (token_id && token_nama && token_sp && token_syarat) {
                int id = atoi(token_id);
                int sp = atoi(token_sp);
                
                // Tambahkan node kursus ke Graph
                addCourse(graph, id, id, token_nama, sp);
                
                // Jika syaratnya BUKAN "NONE", pecah berdasarkan titik koma ';'
                if (strcmp(token_syarat, "NONE") != 0) {
                    char *syarat = strtok(token_syarat, ";");
                    while (syarat != NULL) {
                        int id_syarat = atoi(syarat);
                        addEdge(graph, id_syarat, id); // Sambungkan edge
                        syarat = strtok(NULL, ";");
                    }
                }
            }
        }
    }
    fclose(file);

    // Setelah file data dibaca bagi dan belah array profesi sehingga BST seimbang
    if (jumlahProfesi > 0) {
        insertBalancedBST(rootBST, arrayProfesi, 0, jumlahProfesi - 1);
    }
}