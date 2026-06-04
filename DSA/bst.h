#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur struct ProfessionNode
typedef struct ProfessionNode *P_Node; // alias
typedef struct ProfessionNode
{
    int id;          // Kunci unik (key) untuk BST
    char name[100];  // Nama profesi
    int required_sp; // Syarat total Skill Points
    P_Node left;
    P_Node right;
} ProfessionNode;

// Menyimpan data dummy
typedef struct
{
    int id;
    char name[100];
    int required_sp;
} DummyData;

// Prototipe Fungsi (Selaras Menggunakan parameter id)
P_Node createNode(int id, char *name, int required_sp);
P_Node insertProfession(P_Node root, int id, char *name, int required_sp);
P_Node searchProfession(P_Node root, int search_id);
void freeBST(P_Node root);
void printInOrder(P_Node root);

// Fungsi Pencarian Profesi Berdasarkan Nama
P_Node searchProfessionByName(P_Node root, char *search_name);

// Fungsi Otomatisasi Load Data
P_Node loadDefaultProfessions(P_Node root);

#endif // BST_H