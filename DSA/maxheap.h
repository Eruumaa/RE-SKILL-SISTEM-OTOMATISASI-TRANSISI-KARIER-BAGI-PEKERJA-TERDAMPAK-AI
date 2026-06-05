#ifndef MAXHEAP_H
#define MAXHEAP_H

// Struct Elemen Kursus di dalam Heap yang menyimpan ID kursus dan nilai skill point
typedef struct HeapElement *HeapelementPtr;
typedef struct HeapElement{
    int course_id; // ID unik dari kursus
    int sp_value;  // Poin yang diperoleh
} HeapElement;
// Alias pointer

// Struct data utama Max-Heap untuk Priority Queue
typedef struct MaxHeap *MaxheapPtr;
typedef struct MaxHeap {
    HeapelementPtr data; // Array dinamis untuk menyimpan elemen kursus
    int capacity;        // Kapasitas maksimum alokasi memori heap
    int size;            // Jumlah elemen aktif yang ada saat ini
} MaxHeap;

// Prototipe Fungsi Utilitas Indeks
int parent (int );
int leftChild (int );
int rightChild (int );

// Prototipe Fungsi Utama Max-Heap
MaxheapPtr createMaxHeap (int );
HeapElement extractMax (MaxheapPtr );
void maxHeapify (MaxheapPtr , int );
void insertHeap (MaxheapPtr , int , int );
void freeMaxHeap (MaxheapPtr );

// Prototipe Pengembangan Khusus Max-Heap
HeapElement peekMax (MaxheapPtr );     // Lihat elemen tertinggi tanpa menghapus dengan kompleksitas waktu (O(1))
int isEmptyHeap (MaxheapPtr );        // Cek apakah heap kosong dengan kompleksitas waktu (O(1))
void printHeap (MaxheapPtr );        // Cetak data array heap untuk debugging dengan kompleksitas waktu (O(n))

#endif