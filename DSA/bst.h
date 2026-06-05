#ifndef BST_H
#define BST_H

// Struktur struct ProfessionNode
typedef struct ProfessionNode *P_Node; // alias
typedef struct ProfessionNode {
    int id;          // Kunci untuk BST
    char name[100];  // Nama profesi
    int required_sp; // Syarat total Skill Points
    P_Node left;
    P_Node right;
} ProfessionNode;

// Prototipe Fungsi Selaras Menggunakan parameter id
P_Node createNode (int , char *, int );
P_Node insertProfession (P_Node , int , char *, int );
P_Node searchProfession (P_Node , int );
void freeBST (P_Node );
void printInOrder (P_Node );

#endif