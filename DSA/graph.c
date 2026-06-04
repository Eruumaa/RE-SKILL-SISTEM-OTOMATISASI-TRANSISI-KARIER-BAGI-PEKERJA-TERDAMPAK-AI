#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// O(V)
Graph* createGraph(int vertices) {                   // Membuat graph dengan jumlah vertex tertentu
    Graph* graph = (Graph*)malloc(sizeof(Graph));    // Alokasi memori untuk struktur graph

    graph->num_vertices = vertices;                  // Menyimpan jumlah vertex

    graph->courses = (Course*)malloc(vertices * sizeof(Course));    // Alokasi array course

    graph->adjList = (CourseNode**)malloc(
        vertices * sizeof(CourseNode*)       // Alokasi adjacency list
    );

    graph->in_degree = (int*)calloc(
        vertices,
        sizeof(int)          // Alokasi dan inisialisasi in-degree = 0
    );

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;       // Setiap adjacency list diawali NULL

    }

    return graph;
}

// O(1)
void addCourse(
    Graph* graph,
    int index,
    int course_id,
    const char* course_name,
    int sp_value
) {
    graph->courses[index].course_id = course_id;            // Menyimpan ID mata kuliah
    strcpy(graph->courses[index].course_name, course_name); // Menyalin nama mata kuliah
    graph->courses[index].sp_value = sp_value;              // Menyimpan nilai SP/SKS        
}

// O(1)
void addEdge(Graph* graph, int u, int v) {

    CourseNode* newNode =
        (CourseNode*)malloc(sizeof(CourseNode));

    newNode->course_id = v;                  // Menyimpan vertex tujuan
    newNode->next = graph->adjList[u];       // Menghubungkan ke node sebelumnya

    graph->adjList[u] = newNode;             // Node baru menjadi head adjacency list

    // update in-degree
    graph->in_degree[v]++;             // Menambah jumlah in-degree vertex tujuan
}

// O(out_degree(v))
void removeCourse(Graph* graph, int courseIndex) {

    CourseNode* temp =
        graph->adjList[courseIndex];          // Mengambil daftar tetangga vertex

    while (temp != NULL) {

        int neighbor = temp->course_id;           // Menyimpan vertex tetangga

        if (graph->in_degree[neighbor] > 0) {
            graph->in_degree[neighbor]--;       // Mengurangi in-degree tetangga
        }

        temp = temp->next;
    }
}

// O(V + E)
void displayGraph(Graph* graph) {

    printf("\n=== COURSE DAG ===\n");

    for (int i = 0; i < graph->num_vertices; i++) {

        printf("%s (SP:%d) -> ",
               graph->courses[i].course_name,
               graph->courses[i].sp_value);      // Menampilkan nama course dan nilai SP

        CourseNode* temp = graph->adjList[i];    // Mengambil adjacency list vertex i

        while (temp != NULL) {

            printf("%s ",
                   graph->courses[temp->course_id].course_name);     // Menampilkan course yang terhubung

            temp = temp->next;
        }

        printf("\n");
    }
}

// O(V + E)
void freeGraph(Graph* graph) {

    for (int i = 0; i < graph->num_vertices; i++) {

        CourseNode* current = graph->adjList[i];     // Mengambil head list

        while (current != NULL) {

            CourseNode* temp = current;          // Menyimpan node sementara
            current = current->next;             // Pindah ke node berikutnya


            free(temp);
        }
    }

    free(graph->courses);       // Membebaskan array course
    free(graph->adjList);       // Membebaskan adjacency list
    free(graph->in_degree);     // Membebaskan array in-degree
    free(graph);                 // Membebaskan graph utama
}

