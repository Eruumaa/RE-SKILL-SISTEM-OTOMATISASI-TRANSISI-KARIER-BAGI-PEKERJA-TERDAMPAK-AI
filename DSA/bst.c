#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fungsi utilitas untuk membuat node baru
P_Node createNode (int id, char *name, int required_sp) {
    P_Node newNode = (P_Node)malloc(sizeof(ProfessionNode));
    if (newNode == NULL) {
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
P_Node insertProfession (P_Node root, int id, char *name, int required_sp) {
    // Jika root kosong, buat node baru sebagai root
    if (root == NULL) {
        return createNode(id, name, required_sp);
    }

    // Menggunakan parameter 'id' langsung agar pembagian pohon seimbang
    if (id < root->id) {
        root->left = insertProfession(root->left, id, name, required_sp);
    }
    else if (id > root->id) {
        root->right = insertProfession(root->right, id, name, required_sp);
    }

    return root;
}

//  Mencari node berdasarkan ID profesi
P_Node searchProfession (P_Node root, int search_id) {
    if (root == NULL || root->id == search_id) {
        return root;
    }

    if (search_id < root->id) {
        return searchProfession(root->left, search_id);
    }

    return searchProfession(root->right, search_id);
}

// Fungsi freeBST
void freeBST (P_Node root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

// Fungsi Utilitas Mencetak Seluruh Isi BST transversal In-order
void printInOrder (P_Node root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("| %-4d | %-65s | %-4d SP     |\n", root->id, root->name, root->required_sp);
        printInOrder(root->right);
    }
}