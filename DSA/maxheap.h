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
