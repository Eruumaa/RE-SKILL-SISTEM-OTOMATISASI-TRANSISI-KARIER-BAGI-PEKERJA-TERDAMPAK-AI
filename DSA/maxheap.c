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

// Mengalokasikan memori dinamis untuk struktur Max-Heap berdasarkan kapasitas maksimum
MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (heap == NULL) {
        printf("[Error] Alokasi struktur Max-Heap gagal!\n");
        exit(1);
    }
    heap->capacity = capacity;
    heap->size = 0;
    heap->data = (HeapElement*)malloc(capacity * sizeof(HeapElement));
    if (heap->data == NULL) {
        printf("[Error] Alokasi data elemen heap gagal!\n");
        free(heap);
        exit(1);
    }
    return heap;
}
// Menjaga properti Max-Heap dari posisi akar (root) menuju ke bawah (O(log n))
void maxHeapify(MaxHeap* heap, int idx) {
    int largest = idx;
    int left = leftChild(idx);
    int right = rightChild(idx);

    if (left < heap->size && heap->data[left].sp_value > heap->data[largest].sp_value) {
        largest = left;
    }

    if (right < heap->size && heap->data[right].sp_value > heap->data[largest].sp_value) {
        largest = right;
    }

    if (largest != idx) {
        swapElements(&heap->data[idx], &heap->data[largest]);
        maxHeapify(heap, largest);
    }
}
