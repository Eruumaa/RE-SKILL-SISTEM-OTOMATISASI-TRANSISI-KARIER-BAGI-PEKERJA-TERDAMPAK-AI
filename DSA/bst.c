#include "BST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fungsi utilitas untuk membuat node baru
P_Node createNode(int id, char *name, int required_sp)
{
    P_Node newNode = (P_Node)malloc(sizeof(ProfessionNode));
    if (newNode == NULL)
    {
        printf("Alokasi memori gagal!\n");
        exit(1);
    }

    newNode->id = id; // Menggunakan ID yang dilewatkan dari parameter
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0'; // Memastikan null-terminated
    newNode->required_sp = required_sp;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Fungsi insertProfession
P_Node insertProfession(P_Node root, int id, char *name, int required_sp)
{
    // Jika root kosong, buat node baru sebagai root
    if (root == NULL)
    {
        return createNode(id, name, required_sp);
    }

    // Menggunakan parameter 'id' langsung agar pembagian pohon seimbang
    if (id < root->id)
    {
        root->left = insertProfession(root->left, id, name, required_sp);
    }
    else if (id > root->id)
    {
        root->right = insertProfession(root->right, id, name, required_sp);
    }

    return root;
}

//  Mencari node berdasarkan ID profesi
P_Node searchProfession(P_Node root, int search_id)
{
    if (root == NULL || root->id == search_id)
    {
        return root;
    }

    if (search_id < root->id)
    {
        return searchProfession(root->left, search_id);
    }

    return searchProfession(root->right, search_id);
}

// Mencari node berdasarkan NAMA profesi
P_Node searchProfessionByName(P_Node root, char *search_name)
{
    // Basis kasus: Jika pohon kosong, atau jika data tidak ditemukan
    if (root == NULL)
    {
        return NULL;
    }

    // Periksa apakah nama node saat ini cocok dengan yang dicari (Case-Sensitive)
    if (strcmp(root->name, search_name) == 0)
    {
        return root;
    }

    // Jika belum cocok, cari ke sub-pohon sebelah kiri
    P_Node foundLeft = searchProfessionByName(root->left, search_name);
    if (foundLeft != NULL)
    {
        return foundLeft; // Jika ditemukan di kiri, langsung kembalikan hasil
    }

    // Jika di kiri tidak ada, cari ke sub-pohon sebelah kanan
    return searchProfessionByName(root->right, search_name);
}

// Menu cari Profesi
void menuCariProfesi(P_Node root)
{
    char inputNama[100];

    printf("\nMasukkan nama profesi target: ");
    // Menggunakan scanf atau fgets untuk menerima input string ber-spasi
    char format[20];
    sprintf(format, "%%%ds", (int)sizeof(inputNama) - 1);
    scanf(" %[^\n]", inputNama);

    // Memanggil fungsi tambahan yang baru dibuat
    P_Node hasil = searchProfessionByName(root, inputNama);

    if (hasil != NULL)
    {
        printf("\n============================================");
        printf("\n Profesi Ditemukan!\n");
        printf("ID Profesi   : %d\n", hasil->id);
        printf("Nama Profesi : %s\n", hasil->name);
        printf("Syarat SP    : %d\n", hasil->required_sp);
        printf("============================================/n");
    }
    else
    {
        printf("===========================================================");
        printf("\n Maaf, profesi '%s' tidak ditemukan dalam sistem.\n", inputNama);
        printf("===========================================================\n");
    }
}

// Fungsi freeBST
void freeBST(P_Node root)
{
    if (root != NULL)
    {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

// Fungsi Otomatisasi Menyimpan Data Profesi
P_Node loadDefaultProfessions(P_Node root)
{
    // ID 103 (nilai tengah) diletakkan di paling atas agar menjadi Root utama!
    DummyData listProfesi[] = {

    };

    // Hitung otomatis jumlah data yang ada di dalam array
    int totalData = sizeof(listProfesi) / sizeof(listProfesi[0]);

    // Lakukan perulangan otomatis untuk memasukkan semua data ke BST
    for (int i = 0; i < totalData; i++)
    {
        root = insertProfession(root, listProfesi[i].id, listProfesi[i].name, listProfesi[i].required_sp);
    }

    return root;
}

// --- 6. Fungsi Utilitas Mencetak Seluruh Isi BST (In-order) ---
void printInOrder(P_Node root)
{
    if (root != NULL)
    {
        printInOrder(root->left);
        printf("==================================================\n");
        printf("ID: %d | Profesi: %-25s | Required SP: %d\n", root->id, root->name, root->required_sp);
        printf("==================================================\n");
        printInOrder(root->right);
    }
}