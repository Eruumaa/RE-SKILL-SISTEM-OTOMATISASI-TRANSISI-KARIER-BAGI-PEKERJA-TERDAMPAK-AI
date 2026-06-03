#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NAME 100

// Node untuk adjacency list
typedef struct CourseNode {
    int course_id;
    struct CourseNode* next;
} CourseNode;

// Data setiap course
typedef struct {
    int course_id;
    char course_name[MAX_NAME];
    int sp_value;
} Course;

// Struktur Graph (DAG)
typedef struct {
    int num_vertices;
    Course* courses;
    CourseNode** adjList;
    int* in_degree;
} Graph;

// Function Prototype
Graph* createGraph(int vertices);

void addCourse(
    Graph* graph,
    int index,
    int course_id,
    const char* course_name,
    int sp_value
);

void addEdge(Graph* graph, int u, int v);

void removeCourse(Graph* graph, int courseIndex);

void displayGraph(Graph* graph);

void freeGraph(Graph* graph);

#endif
