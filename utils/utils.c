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
