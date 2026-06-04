#ifndef MAXHEAP_H
#define MAXHEAP_H

// Struktur Elemen Kursus di dalam Heap (Menyimpan ID Kursus dan Nilai Skill Points)
typedef HeapElement *HeapelementPtr;
typedef struct HeapElement
{
    int course_id; // ID unik dari kursus
    int sp_value;  // Poin yang diperoleh (Kunci prioritas Max-Heap)
} HeapElement;

// Struktur data utama Max-Heap (Priority Queue)
typedef struct MaxHeap *MaxheapPtr;
typedef struct MaxHeap
{
    HeapelementPtr data; // Array dinamis untuk menyimpan elemen kursus
    int capacity;        // Kapasitas maksimum alokasi memori heap
    int size;            // Jumlah elemen aktif yang ada saat ini
} MaxHeap;

// Prototipe Fungsi Utilitas Indeks
int parent(int idx);
int leftChild(int idx);
int rightChild(int idx);

// Prototipe Fungsi Utama Max-Heap
MaxheapPtr createMaxHeap(int capacity);
void maxHeapify(MaxheapPtr heap, int idx);
void insertHeap(MaxheapPtr heap, int course_id, int sp_value);
HeapElement extractMax(MaxheapPtr heap);
void freeMaxHeap(MaxheapPtr heap);

// Prototipe Pengembangan Khusus Ruang Lingkup Max-Heap
int isEmptyHeap(MaxheapPtr heap);        // Cek apakah heap kosong (O(1))
HeapelementPtr peekMax(MaxheapPtr heap); // Lihat elemen tertinggi tanpa menghapus (O(1))
void printHeap(MaxheapPtr heap);         // Cetak data array heap untuk debugging (O(n))

#endif // MAXHEAP_H