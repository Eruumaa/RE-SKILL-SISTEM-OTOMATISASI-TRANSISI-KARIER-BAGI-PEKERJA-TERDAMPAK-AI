# System Context & Constraints

Project Name: Re-Skill (Career Transition Automation System)
Language: C (Standard C99 atau lebih baru)
Environment: CLI / Terminal
Role/Task: Implementasi Struktur Data dan Algoritma inti (BST, DAG, Max-Heap).
Rules:
Fokus pada struktur data dasar yang optimal. Tidak menggunakan Machine Learning.
Tulis kode yang modular (gunakan header files dan satu file fungsi gabungan dari ketiga algoritma inti).

Pastikan manajemen memori yang baik (gunakan malloc dan free dengan benar).
Berikan komentar (inline documentation) yang menjelaskan Big-O complexity pada fungsi utama.

## Task 1: Implementasi Binary Search Tree (BST) untuk Data Profesi

- Buatkan implementasi Binary Search Tree (BST) dalam bahasa C untuk menyimpan profil profesi.

### Struktur struct: Buat struct ProfessionNode yang memiliki

- id (integer) sebagai kunci unik (key).
- name (string/char array) nama profesi.
- required_sp (integer) syarat total Skill Points minimal.
- Pointer ke left dan right.
- Fungsi insertProfession: Buat fungsi untuk memasukkan data profesi baru ke dalam BST berdasarkan id.
- Fungsi searchProfession: Buat fungsi yang mengembalikan pointer ke node profesi jika ditemukan berdasarkan id, atau NULL jika tidak. Fungsi ini harus berjalan dengan kompleksitas O(log n) rata-rata.
- Fungsi freeBST: Buat fungsi untuk membersihkan seluruh memori BST saat program selesai.

## Task 2: Implementasi Directed Acyclic Graph (DAG) untuk Prasyarat Kursus

- Buatkan implementasi Directed Acyclic Graph (DAG) menggunakan Adjacency List dalam bahasa C untuk memodelkan hierarki prasyarat kursus.

### Struktur struct

- Buat CourseNode untuk Linked List dari daftar ketetanggaan (adjacency).
- Buat Graph yang menyimpan array dari pointer ke kepala linked list (vertex), jumlah vertex (num_vertices), dan sebuah array in_degree untuk melacak In-Degree setiap vertex.
- Setiap vertex merepresentasikan sebuah kursus dan harus menyimpan data: course_id (integer), course_name (string), dan sp_value (integer, mewakili poin yang didapat setelah menyelesaikan kursus).
- Fungsi createGraph: Fungsi inisialisasi Graph dengan jumlah vertex tertentu.
- Fungsi addEdge: Fungsi untuk menambahkan sisi (edge) berarah dari kursus u (prasyarat) ke kursus v (lanjutan). Penting: Pastikan fungsi ini juga meningkatkan nilai in_degree dari vertex v sebesar 1.
- Fungsi removeCourse (Simulasi): Buat fungsi untuk menyimulasikan pemutusan edge ketika sebuah kursus diambil. Fungsi ini akan mencari semua adjacent vertices (tetangga) dari kursus yang diambil dan mengurangi nilai in_degree mereka masing-masing sebesar 1.

## Task 3: Implementasi Max-Heap (Priority Queue) untuk Mesin Optimasi

- Buatkan implementasi Max-Heap (Priority Queue) dalam bahasa C yang akan digunakan sebagai mesin optimasi Greedy Algorithm.

### Struktur struct

- Buat struct MaxHeap yang berisi array dari elemen kursus (berisi course_id dan sp_value), ukuran maksimal (kapasitas), dan ukuran saat ini (size). Prioritas (Max-Heap) ditentukan oleh nilai sp_value (Skill Points).
  Fungsi Dasar Heap:
- Buat fungsi utilitas: parent, leftChild, dan rightChild untuk mendapatkan indeks.
- Buat fungsi heapify (untuk menjaga properti max-heap dari root ke bawah).
  Fungsi insertHeap: Fungsi untuk memasukkan kursus (yang memiliki in_degree == 0) ke dalam heap. Kompleksitas harus O(log n).
- Fungsi extractMax: Fungsi untuk mengambil dan menghapus elemen dengan sp_value tertinggi dari heap. Ini akan digunakan oleh algoritma Greedy. Kompleksitas harus O(log n).

## Task 4: Struktur Transaksional, Inisialisasi, & Orkestrasi (Kahn's & Greedy)

- Buatkan struktur data pendukung untuk transaksi dan fungsi utama yang menghubungkan BST, DAG, dan Max-Heap sesuai alur Kahn's Algorithm dan optimasi Greedy.

### Struktur LearningPath

- Buat struktur (misal: array of struct dinamis atau linked list) untuk menyimpan urutan course_id yang dipilih oleh sistem.

#### Fungsi loadDummyData

- Buat fungsi untuk mengisi dummy data:
- Minimal 3 node ke BST (contoh: Data Analyst SP: 100, Prompt Engineer SP: 80,).
- Nilai Skill Point(SP) hanya bisa ditentukan oleh pengembang sistem
- Minimal 5 vertex ke Graph beserta edges-nya.
- Fungsi Inti calculateReskillingPath: Buat kerangka fungsi yang menerima current_sp (poin bawaan user) dan target_profession_id.

#### Alurnya

- Cari profesi di BST, hitung skill_gap (required_sp - current_sp).
- Looping seluruh vertex di Graph: jika in_degree == 0, insertHeap kursus tersebut ke Max-Heap.
- Loop while (skill_gap > 0 && heap tidak kosong):
- Panggil extractMax (ini pendekatan Greedy).
- Kurangi skill_gap dengan sp_value dari kursus yang diambil.
- Masukkan kursus ke LearningPath.
- Panggil fungsi removeCourse (Task 2) untuk meng-update in_degree tetangganya.
- Cek tetangga yang terdampak: jika in_degree tetangga menjadi 0, insertHeap tetangga tersebut ke Max-Heap.
