#include "maxheap.h"

// Fungsi utilitas matematika untuk mendapatkan indeks relasi pohon biner dalam array
int parent(int idx)
{
    return (idx - 1) / 2;
}

int leftChild(int idx)
{
    return (2 * idx) + 1;
}

int rightChild(int idx)
{
    return (2 * idx) + 2;
}

// Fungsi internal pembantu untuk menukar posisi dua elemen di dalam heap
void swapElements(HeapelementPtr a, HeapelementPtr *b)
{
    HeapElement temp = *a;
    *a = *b;
    *b = temp;
}

// Mengalokasikan memori dinamis untuk struktur Max-Heap berdasarkan kapasitas maksimum
MaxheapPtr createMaxHeap(int capacity)
{
    MaxheapPtr heap = (MaxheapPtr)malloc(sizeof(MaxHeap));
    if (heap == NULL)
    {
        printf("[Error] Alokasi struktur Max-Heap gagal!\n");
        exit(1);
    }
    heap->capacity = capacity;
    heap->size = 0;
    heap->data = (HeapelementPtr)malloc(capacity * sizeof(HeapElement));
    if (heap->data == NULL)
    {
        printf("[Error] Alokasi data elemen heap gagal!\n");
        free(heap);
        exit(1);
    }
    return heap;
}
// Menjaga properti Max-Heap dari posisi akar (root) menuju ke bawah (O(log n))
void maxHeapify(MaxheapPtr heap, int idx)
{
    int largest = idx;
    int left = leftChild(idx);
    int right = rightChild(idx);

    if (left < heap->size && heap->data[left].sp_value > heap->data[largest].sp_value)
    {
        largest = left;
    }

    if (right < heap->size && heap->data[right].sp_value > heap->data[largest].sp_value)
    {
        largest = right;
    }

    if (largest != idx)
    {
        swapElements(&heap->data[idx], &heap->data[largest]);
        maxHeapify(heap, largest);
    }
}

// Memasukkan elemen kursus baru yang lolos prasyarat Kahn's (In-Degree == 0) ke heap (O(log n))
void insertHeap(MaxheapPtr heap, int course_id, int sp_value)
{
    if (heap->size >= heap->capacity)
    {
        printf("[Peringatan] Max-Heap penuh!\nGagal melakukan insert untuk kursus %d.\n", course_id);
        return;
    }

    int i = heap->size;
    heap->data[i].course_id = course_id;
    heap->data[i].sp_value = sp_value;
    heap->size++;

    while (i != 0 && heap->data[parent(i)].sp_value < heap->data[i].sp_value)
    {
        swapElements(&heap->data[i], &heap->data[parent(i)]);
        i = parent(i);
    }
}

// Mengambil dan menghapus kursus dengan perolehan sp_value tertinggi dari Root (O(log n))
HeapElement extractMax(MaxheapPtr heap)
{
    if (heap->size <= 0)
    {
        HeapElement empty = {-1, -1};
        return empty;
    }

    if (heap->size == 1)
    {
        heap->size--;
        return heap->data[0];
    }

    HeapElement root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);

    return root;
}

// Membersihkan dan membebaskan alokasi memori dinamis heap demi mencegah memory leak
void freeMaxHeap(MaxheapPtr heap)
{
    if (heap != NULL)
    {
        free(heap->data);
        free(heap);
    }
}

// Memeriksa apakah struktur antrean Max-Heap dalam kondisi kosong (O(1))
int isEmptyHeap(MaxheapPtr heap)
{
    return (heap == NULL || heap->size == 0);
}

// Melihat elemen dengan prioritas nilai SP tertinggi di posisi root tanpa menghapusnya (O(1))
HeapElement peekMax(MaxheapPtr heap)
{
    if (isEmptyHeap(heap))
    {
        HeapElement empty = {-1, -1};
        return empty;
    }
    return heap->data[0];
}

// Mencetak representasi linear array dari isi heap saat ini untuk keperluan penelusuran (O(n))
void printHeap(MaxheapPtr heap)
{
    if (isEmptyHeap(heap))
    {
        printf("Max-Heap Kosong.\n");
        return;
    }
    printf("Status Heap Saat Ini (Size: %d): ", heap->size);
    for (int i = 0; i < heap->size; i++)
    {
        printf("[ID: %d | SP: %d] ", heap->data[i].course_id, heap->data[i].sp_value);
    }
    printf("\n");
}