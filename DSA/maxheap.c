#include "maxheap.h"

// Fungsi utilitas matematika untuk mendapatkan indeks relasi pohon biner dalam array
int parent(int idx) { 
    return (idx - 1) / 2; 
}

int leftChild(int idx) { 
    return (2 * idx) + 1; 
}

int rightChild(int idx) { 
    return (2 * idx) + 2; 
}

// Fungsi internal pembantu untuk menukar posisi dua elemen di dalam heap
void swapElements(HeapElement* a, HeapElement* b) {
    HeapElement temp = *a;
    *a = *b;
    *b = temp;
}

