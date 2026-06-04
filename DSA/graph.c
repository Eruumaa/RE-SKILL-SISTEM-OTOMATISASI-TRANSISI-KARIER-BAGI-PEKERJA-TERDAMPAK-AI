#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// O(V)
GraphPtr createGraph(int vertices)
{
    GraphPtr graph = (GraphPtr)malloc(sizeof(Graph));

    graph->num_vertices = vertices; // Menyimpan jumlah vertex

    // Alokasi memori
    graph->courses = (CoursePtr)malloc(vertices * sizeof(Course));
    graph->adjList = (CourseNPtr *)malloc(vertices * sizeof(CourseNPtr));
    graph->in_degree = (int *)calloc(vertices, sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjList[i] = NULL;
    }

    return graph;
}

// O(1)
void addCourse(
    GraphPtr graph,
    int index,
    int course_id,
    const char *course_name,
    int sp_value)
{
    graph->courses[index].course_id = course_id;
    strcpy(graph->courses[index].course_name, course_name);
    graph->courses[index].sp_value = sp_value;
}

// O(1)
void addEdge(GraphPtr graph, int u, int v)
{

    CourseNPtr newNode = (CourseNPtr *)malloc(sizeof(CourseNode));

    newNode->course_id = v;            // Menyimpan vertex tujuan
    newNode->next = graph->adjList[u]; // Menghubungkan ke node sebelumnya

    graph->adjList[u] = newNode; // Node baru menjadi head adjacency list

    // update in-degree
    graph->in_degree[v]++; // Menambah jumlah in-degree vertex tujuan
}

// O(out_degree(v))
void removeCourse(GraphPtr graph, int courseIndex)
{

    CourseNPtr temp = graph->adjList[courseIndex];

    while (temp != NULL)
    {
        int neighbor = temp->course_id;

        if (graph->in_degree[neighbor] > 0)
        {
            graph->in_degree[neighbor]--;
        }

        temp = temp->next;
    }
}

// O(V + E)
void displayGraph(Graph *graph)
{

    printf("\n=== COURSE DAG ===\n");

    for (int i = 0; i < graph->num_vertices; i++)
    {

        printf("%s (SP:%d) -> ",
               graph->courses[i].course_name,
               graph->courses[i].sp_value);      // Menampilkan nama course dan nilai SP

        CourseNode *temp = graph->adjList[i];

        while (temp != NULL)
        {

            printf("%s ",
                   graph->courses[temp->course_id].course_name);     // Menampilkan course yang terhubung

            temp = temp->next;
        }

        printf("\n");
    }
}

// O(V + E)
void freeGraph(GraphPtr graph)
{

    for (int i = 0; i < graph->num_vertices; i++)
    {

        CourseNPtr current = graph->adjList[i];

        while (current != NULL)
        {

            CourseNPtr temp = current;
            current = current->next;

            free(temp);
        }
    }

    free(graph->courses);       // Membebaskan array course
    free(graph->adjList);       // Membebaskan adjacency list
    free(graph->in_degree);     // Membebaskan array in-degree
    free(graph);                 // Membebaskan graph utama
}

