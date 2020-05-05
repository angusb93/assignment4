#include <stdio.h>
#include <stdbool.h>
#include "stdlib.h"
#include "assert.h"
#include "string.h"

typedef int Vertex;
typedef struct Edge {
    Vertex v;
    Vertex w;
    int d;
} Edge;

typedef struct Node {
    Vertex v;
    int d;
    struct Node *next;
} Node;

void printLL(struct Node* n)
{
    while (n != NULL) {
        printf(" %d ", n->v);
        n = n->next;
    }
}

bool inLL(Node *list_start, Vertex v)
{
    if(list_start == NULL){
        return false;
    }
    Node *it = list_start;
    while (it->next != NULL){
        if(it->v == v){
            return true;
        }
        it = it->next;
    }
    return false;
}



Node * insertLL(Node *firstNode, Vertex new_vert, int d)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    struct Node *last = firstNode;  /* used in step 5*/

    /* 2. put in the data  */
    new_node->v  = new_vert;
    new_node->d = d;

    /* 3. This new node is going to be the last node, so make next
          of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (firstNode == NULL)
    {
        firstNode = new_node;
        return firstNode;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
    return firstNode;
}



void deleteLL(struct Node* n)
{

}

typedef struct GraphRep {
    Node **edges;
    int nV;
    int nE;
} GraphRep;

typedef struct GraphRep *Graph;

Graph newGraph(int n) {
    int i;
    assert(n >= 0);
    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);
    g->nV = n; g->nE = 0;
    g->edges = malloc(g->nV * sizeof(Node *));
    assert(g->edges != NULL);
    for (i = 0; i < n; i++)
        g->edges[i] = NULL;
    return g;
}

bool validV(Graph g, Vertex v){
    return (g != NULL && v >= 0);
}

void insertEdge(Graph g, Edge e) {
    assert(g != NULL && validV(g,e.v) && validV(g,e.w));
    if (!inLL(g->edges[e.v], e.w)) {
        g->edges[e.v] = insertLL(g->edges[e.v], e.w, e.d);
        g->nE++;
    }
}

//void removeEdge(Graph g, Edge e) {
//    assert(g != NULL && validV(g,e.v) && validV(g,e.w));
//    if (inLL(g->edges[e.v], e.w)) {
//        g->edges[e.v] = deleteLL(g->edges[e.v], e.w);
//        g->edges[e.w] = deleteLL(g->edges[e.w], e.v);
//        g->nE--;
//    }
//}
//
bool adjacent(Graph g, Vertex x, Vertex y) {
    assert(g != NULL && validV(g,x));
    return inLL(g->edges[x], y);
}

void printGraph(Graph graph)
{
    int v;
    for (v = 0; v < graph->nV; v++)
    {
        Node *temp;
        temp = graph->edges[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf(" -> (Num:%d, dist:%d)", temp->v,temp->d);
            temp = temp->next;
        }
        printf("\n");
    }
}

Graph buildGraph(char *distance, char *busstops) {
    // find number of vertex's for size of graph
    char str[100];
    char size[100];

    FILE *stops = fopen(busstops, "r");
    if (stops){
        while( fgets(str, sizeof(str), stops)!=NULL );
    }
    else{
        printf("Could not find file\n");
        return 0;                                   // error checking
    }
    strncpy(size, str, 2);
    size[2] = '\0'; // null terminate destination
    int sizeInt = atoi(size) + 1; //needed size of graph

    Graph g = newGraph(sizeInt); //build empty graph
    Edge e;
    int v, w, d;
    FILE *file = fopen(distance, "r"); // open a file
    if (file) {
        while (fscanf(file, "%d-%d:%d", &v, &w, &d) == 3) {
            e.v = v;
            e.w = w;
            e.d = d;
            insertEdge(g, e); // insert edges to build graph
        }
    }else{
        printf("Could not find file\n");
        return 0;
    }
    return g;
}
int main() {
    Graph g = buildGraph("distance.txt","BusStops.txt");
    printGraph(g);

}
