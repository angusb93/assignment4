#include <stdio.h>
#include <stdbool.h>
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include <limits.h>

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
    int visited;
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
    new_node->visited = 0;

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

struct Stack {
    int top;
    unsigned capacity;
    int* array;
}Stack;

struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

void push(struct Stack* stack, Vertex item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    //printf("%d pushed to stack\n", item);
}

Vertex pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
int peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
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
    g->nV = n;
    g->nE = 0;
    g->edges = malloc(g->nV * sizeof(Node *));
    assert(g->edges != NULL);
    for (i = 0; i < n; i++) {
        g->edges[i] = NULL;
    }
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
            printf(" -> (Num:%d, dist:%d, visited:%d)", temp->v,temp->d,temp->visited);
            temp = temp->next;
        }
        printf("\n");
    }
}

Graph buildGraph(char *distance, char *busstops, bool transpose) {
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
            if(transpose == false) {
                e.v = v;
                e.w = w;
                e.d = d;
                insertEdge(g, e); // insert edges to build graph
            } else{
                e.v = w;
                e.w = v;
                e.d = d;
                insertEdge(g, e); // insert edges to build graph
            }
        }
    }else{
        printf("Could not find file\n");
        return 0;
    }
    return g;
}


void DFS(Graph graph, Vertex v) {
    Node *adjList = graph->edges[v];
    Node *temp = adjList;

    graph->edges[v]->visited = 1;
    printf("Visited %d\n", v);
    while(temp) {
        Vertex connectedVertex = temp->v;
        if(!graph->edges[connectedVertex]){
            break;
        }
        if(graph->edges[connectedVertex]->visited == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void fillOrder(Graph graph, Vertex v, struct Stack* stack) {
    Node *adjList = graph->edges[v];
    Node *temp = adjList;

    graph->edges[v]->visited = 1;
    //printf("Visited %d\n", v);
    while(temp) {
        Vertex connectedVertex = temp->v;
//        if(!graph->edges[connectedVertex]){
//            break;
//        }
        if(graph->edges[connectedVertex]->visited == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
    push(stack, v);
}

int StronglyConnectivity(const char *distance, const char *busStops){

    Graph g = buildGraph(distance,busStops, false);
    Graph g_t = buildGraph(distance,busStops, true);
    Vertex v = 0;

    // Step 2: Do DFS traversal starting from first vertex.
    DFS(g, v);

    // If DFS traversal doesn’t visit all vertices, then return false.

    int x;
    for (x = 0; x < g->nV; x++)
    {
        Node *temp;
        temp = g->edges[x];
        if(!g->edges[x]->visited){
            return 0;
        }
        while (temp)
        {
            if(temp->visited == 0){
                return 0;
            }
            temp = temp->next;
        }
        //printf("\n");
    }

    // Step 5: Do DFS for reversed graph starting from first vertex.
    DFS(g_t, v);


    // If all vertices are not visited in second DFS, then
    // return false
    x=0;
    for (x = 0; x < g->nV; x++)
    {
        Node *temp;
        temp = g_t->edges[x];
        if(!g_t->edges[x]->visited){
            return 0;
        }
        while (temp)
        {
            if(!temp->visited){
                return 0;
            }
            temp = temp->next;
        }
    }
    return 1;

}


void maximalStronlyComponents(const char *distance, const char *busStops){
    Graph g = buildGraph(distance,busStops, false);
    Graph g_t = buildGraph(distance,busStops, true);
    Vertex v = 0;
    struct Stack* stack = createStack(100);

    for (int i = 0; i < g->nV ; ++i) {
        fillOrder(g, v, stack);
    }
    int cnt = 0;
    while(stack->top != -1){
        Vertex v = stack->top;
        pop(stack);

        if (g_t->edges[v]->visited == false){
            //DFS(g_t, v);
            //printf("\n");
            printf("Strongly connected component %d: bus stop %d of this strongly connected component\n",cnt,v);
        }
        cnt++;

    }

}

void reachableStops(const char *sourceStop, const char *busStops, const char
*BusNames, const char *BusRoutes, const char *Distance){

}



int main() {
    Graph g = buildGraph("distance.txt","BusStops.txt", false);
    printGraph(g);
    Vertex v = 30;
    int res = StronglyConnectivity("distance.txt","BusStops.txt");
    if (res==0)
        printf("Graph is not strongly connected\n");
    else
        printf("graph IS strongly connected\n");
    maximalStronlyComponents("distance.txt","BusStops.txt");

}
