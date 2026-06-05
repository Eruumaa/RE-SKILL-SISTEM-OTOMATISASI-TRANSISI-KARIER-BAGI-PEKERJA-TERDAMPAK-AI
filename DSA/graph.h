#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NAME 150

// Node untuk adjacency list
typedef struct CourseNode *CourseNPtr;
typedef struct CourseNode {
    int course_id;
    CourseNPtr next;
} CourseNode;

// Data setiap course
typedef struct Course *CoursePtr;
typedef struct Course {
    int course_id;
    char course_name[MAX_NAME];
    int sp_value;
} Course;

// Struct Graph (DAG)
typedef struct Graph *GraphPtr;
typedef struct Graph {
    int num_vertices;
    CoursePtr courses;
    CourseNPtr *adjList;
    int *in_degree;
} Graph;

// Function Prototype untuk membuat graf
Graph *createGraph (int );

// Fungsi menambah course dalam graf
void addCourse (GraphPtr , int , int , const char *, int );
void addEdge (Graph *, int , int );
void removeCourse (Graph *, int );
void displayGraph (Graph *);
void freeGraph (Graph *);

#endif