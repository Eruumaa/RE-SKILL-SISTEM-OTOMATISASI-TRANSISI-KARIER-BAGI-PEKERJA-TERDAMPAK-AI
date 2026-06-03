#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// O(V)
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));

    graph->num_vertices = vertices;

    graph->courses = (Course*)malloc(vertices * sizeof(Course));

    graph->adjList = (CourseNode**)malloc(
        vertices * sizeof(CourseNode*)
    );

    graph->in_degree = (int*)calloc(
        vertices,
        sizeof(int)
    );

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
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
    graph->courses[index].course_id = course_id;
    strcpy(graph->courses[index].course_name, course_name);
    graph->courses[index].sp_value = sp_value;
}

// O(1)
void addEdge(Graph* graph, int u, int v) {

    CourseNode* newNode =
        (CourseNode*)malloc(sizeof(CourseNode));

    newNode->course_id = v;
    newNode->next = graph->adjList[u];

    graph->adjList[u] = newNode;

    // update in-degree
    graph->in_degree[v]++;
}

// O(out_degree(v))
void removeCourse(Graph* graph, int courseIndex) {

    CourseNode* temp =
        graph->adjList[courseIndex];

    while (temp != NULL) {

        int neighbor = temp->course_id;

        if (graph->in_degree[neighbor] > 0) {
            graph->in_degree[neighbor]--;
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
               graph->courses[i].sp_value);

        CourseNode* temp = graph->adjList[i];

        while (temp != NULL) {

            printf("%s ",
                   graph->courses[temp->course_id].course_name);

            temp = temp->next;
        }

        printf("\n");
    }
}

// O(V + E)
void freeGraph(Graph* graph) {

    for (int i = 0; i < graph->num_vertices; i++) {

        CourseNode* current = graph->adjList[i];

        while (current != NULL) {

            CourseNode* temp = current;
            current = current->next;

            free(temp);
        }
    }

    free(graph->courses);
    free(graph->adjList);
    free(graph->in_degree);
    free(graph);
}
