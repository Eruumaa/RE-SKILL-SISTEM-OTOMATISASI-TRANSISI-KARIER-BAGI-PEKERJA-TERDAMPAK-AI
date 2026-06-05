#ifndef UTILS_H
#define UTILS_H

// Struct untuk menampung data BST dari file data teks
typedef struct {
    int id;
    char nama [150];
    int sp;
} tempProfesi;

// Makro Warna ANSI
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Prototipe Fungsi Utility
void clearScreen();
void printLogo();
int loadDataToSystem (P_Node* , GraphPtr *);

#endif // UTILS_H