#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <stdio.h>
#include <stdlib.h>

// Struktur Elemen Kursus di dalam Heap (Menyimpan ID Kursus dan Nilai Skill Points)
typedef struct {
    int course_id;   // ID unik dari kursus
    int sp_value;    // Poin yang diperoleh (Kunci prioritas Max-Heap)
} HeapElement;

// Struktur data utama Max-Heap (Priority Queue) sesuai spesifikasi Task 3
typedef struct {
    HeapElement* data; // Array dinamis untuk menyimpan elemen kursus
    int capacity;      // Kapasitas maksimum alokasi memori heap
    int size;          // Jumlah elemen aktif yang ada saat ini
} MaxHeap;

// --- Prototipe Fungsi Utilitas Indeks ---
int parent(int idx);
int leftChild(int idx);
int rightChild(int idx);

// --- Prototipe Fungsi Utama Max-Heap ---
MaxHeap* createMaxHeap(int capacity);
void maxHeapify(MaxHeap* heap, int idx);
void insertHeap(MaxHeap* heap, int course_id, int sp_value);
HeapElement extractMax(MaxHeap* heap);
void freeMaxHeap(MaxHeap* heap);

// --- Prototipe Pengembangan Khusus Ruang Lingkup Max-Heap ---
int isEmptyHeap(MaxHeap* heap);            // Cek apakah heap kosong (O(1))
HeapElement peekMax(MaxHeap* heap);        // Lihat elemen tertinggi tanpa menghapus (O(1))
void printHeap(MaxHeap* heap);             // Cetak data array heap untuk debugging (O(n))

#endif // MAXHEAP_H