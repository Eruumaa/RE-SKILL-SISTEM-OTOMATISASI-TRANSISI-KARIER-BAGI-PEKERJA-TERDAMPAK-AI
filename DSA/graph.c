#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fungsi membuat graf dengan kompleksitas O(V)
GraphPtr createGraph (int vertices) {
    GraphPtr graph = (GraphPtr)malloc(sizeof(Graph));

    // Menyimpan jumlah vertex
    graph->num_vertices = vertices; 

    // Alokasi memori
    graph->courses = (CoursePtr)malloc(vertices * sizeof(Course));
    graph->adjList = (CourseNPtr *)malloc(vertices * sizeof(CourseNPtr));
    graph->in_degree = (int *)calloc(vertices, sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

// Fungsi menambah course dalam graf dengan kompleksitas O(1)
void addCourse (GraphPtr graph, int index, int course_id, const char *course_name, int sp_value) {
    graph->courses[index].course_id = course_id;
    strcpy(graph->courses[index].course_name, course_name);
    graph->courses[index].sp_value = sp_value;
}

// Fungsi menambah edge dengan kompleksitas O(1)
void addEdge (GraphPtr graph, int u, int v) {
    CourseNPtr newNode = (CourseNPtr)malloc(sizeof(CourseNode));
    // Menyimpan vertex tujuan
    newNode->course_id = v;          
    // Menghubungkan ke node sebelumnya  
    newNode->next = graph->adjList[u]; 

    // Node baru menjadi head adjacency list
    graph->adjList[u] = newNode;

    // update in-degree dengan menambah jumlah in-degree vertex tujuan
    graph->in_degree[v]++;
}

// Fungsi menghapus course pada graf
void removeCourse (GraphPtr graph, int courseIndex) {
    CourseNPtr temp = graph->adjList[courseIndex];

    while (temp != NULL) {
        int neighbor = temp->course_id;

        if (graph->in_degree[neighbor] > 0) {
            graph->in_degree[neighbor]--;
        }

        temp = temp->next;
    }
}

// Fungsi menampilkan graf dengan kompleksitas O(V + E)
void displayGraph (Graph *graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        // Menampilkan nama course dan nilai SP
        printf("[ID: %2d] %s (%d SP)\n", i, graph->courses[i].course_name, graph->courses[i].sp_value);      

        CourseNode *temp = graph->adjList[i];

        if (temp == NULL) {
            printf("         -> (Puncak materi: Tidak menjadi prasyarat untuk kursus lain)\n");
        } else {
            printf("         -> Membuka kunci materi lanjutan:\n");
            
            // Print semua kursus lanjutan dengan list ke bawah
            while (temp != NULL)
            {
                printf("            - %s\n", graph->courses[temp->course_id].course_name);
                temp = temp->next;
            }
        }
        printf("\n");
    }
}

// Fungsi memfreekan graf dengan kompleksitas O(V + E)
void freeGraph (GraphPtr graph) {
    if (graph == NULL) return;
    for (int i = 0; i < graph->num_vertices; i++) {
        CourseNPtr current = graph->adjList[i];

        while (current != NULL) {
            CourseNPtr temp = current;
            current = current->next;
            free(temp);
        }
    }
// Membebaskan array course, adjacency list, array in-degree, dan Membebaskan graf utama
    free(graph->courses);
    free(graph->adjList);
    free(graph->in_degree);
    free(graph);
}