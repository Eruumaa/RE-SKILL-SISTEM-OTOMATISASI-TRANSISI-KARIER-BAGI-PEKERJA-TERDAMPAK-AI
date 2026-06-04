#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NAME 100

// Node untuk adjacency list
typedef struct CourseNode *CourseNPtr;
typedef struct CourseNode
{
    int course_id;
    CourseNPtr next;
} CourseNode;

// Data setiap course
typedef struct Course *CoursePtr;
typedef struct Course
{
    int course_id;
    char course_name[MAX_NAME];
    int sp_value;
} Course;

// Struktur Graph (DAG)
typedef struct Graph *GraphPtr;
typedef struct Graph
{
    int num_vertices;
    CoursePtr courses;
    CourseNPtr *adjList;
    int *in_degree;
} Graph;

// Function Prototype
Graph *createGraph(int vertices);

void addCourse(
    GraphPtr graph,
    int index,
    int course_id,
    const char *course_name,
    int sp_value);

void addEdge(Graph *graph, int u, int v);
void removeCourse(Graph *graph, int courseIndex);
void displayGraph(Graph *graph);
void freeGraph(Graph *graph);

#endif
