#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printLogo() {
    printf(CYAN BOLD);
    printf("  __  __          __ _  ___ _     _     \n");
    printf(" |  _ \\| _|        / __| |/ / _| |   | |    \n");
    printf(" | |) |  _|   __ | (_ | ' / | || |   | |    \n");
    printf(" |  _ <| |_ |__| \\_ \\| . \\ | || |_| |__ \n");
    printf(" || \\\\__|        |_/|\\\\_|_|__|\n");
    printf(RESET);
    printf(YELLOW "  Sistem Otomatisasi Transisi Karier Terdampak AI \n" RESET);
    printf("====================================================\n\n");
}

void loadDataToSystem(P_Node* rootBST, GraphPtr graph) {
    FILE *file = fopen("Data/datasp.txt", "r");
    if (file == NULL) {
        printf(RED "[Error] Gagal memuat file Data/datasp.txt! Pastikan berada di folder yang benar.\n" RESET);
        return;
    }
    char line[256];
    int mode = 0; // 1 = Profesi Target, 2 = Kursus Keterampilan

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
                *rootBST = insertProfession(*rootBST, id_angka, nama, sp);
            }
        } 

          // PARSING 2: Mengolah teks menjadi Graph & Edge (Prasyarat)
        else if (mode == 2) {
            char tempLine[256];
            strcpy(tempLine, line);
            
            // Pisahkan teks berdasarkan koma
            char *token_id = strtok(tempLine, ",");
            char *token_nama = strtok(NULL, ",");
            char *token_sp = strtok(NULL, ",");
            char *token_syarat = strtok(NULL, ",");