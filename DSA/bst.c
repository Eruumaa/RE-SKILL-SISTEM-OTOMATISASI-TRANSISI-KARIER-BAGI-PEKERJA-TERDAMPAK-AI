#include "BST.h"

// --- 1. Fungsi utilitas untuk membuat node baru ---
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

// --- 2. Fungsi insertProfession ---
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

// --- 3. Fungsi searchProfession ---
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

// --- 4. Fungsi freeBST ---
void freeBST(P_Node root)
{
    if (root != NULL)
    {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

// --- 5. Fungsi Otomatisasi Menyimpan Data Profesi ---
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