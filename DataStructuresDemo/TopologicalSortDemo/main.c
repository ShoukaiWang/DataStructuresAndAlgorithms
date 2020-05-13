//
//  main.c
//  TopologicalSortDemo
//
//  Created by SK on 2020/5/13.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXEDGE 20
#define MAXVEX 14
#define INFINITYC 65535

typedef int Status;

typedef struct MGraph {
    int vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;

typedef struct EdgeNode {
    int adjvex; //邻接点域，存储该顶点对应的下标
    int weight;
    struct EdgeNode *next;
}EdgeNode;

typedef struct VertexNode {
    int in;
    int data;
    EdgeNode *firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct {
    AdjList adjList;
    int numVertexes, numEdges;
} graphAdjList, *GraphAdjList;


void CreateMGraph(MGraph *G) {
    int i, j;
    
    G->numEdges = MAXEDGE;
    G->numVertexes = MAXVEX;
    
    for (i = 0; i < G->numVertexes; i++) {
        G->vexs[i] = i;
    }
    
    for (i = 0; i < G->numVertexes; i++) {
        for (j = 0; j < G->numVertexes; j++) {
            G->arc[i][j] = 0;
        }
    }
    
    G->arc[0][4] = 1;
    G->arc[0][5] = 1;
    G->arc[0][11] = 1;
    G->arc[1][2] = 1;
    G->arc[1][4] = 1;
    G->arc[1][8] = 1;
    G->arc[2][5] = 1;
    G->arc[2][6] = 1;
    G->arc[2][9] = 1;
    G->arc[3][2] = 1;
    G->arc[3][13] = 1;
    G->arc[4][7] = 1;
    G->arc[5][8] = 1;
    G->arc[5][12] = 1;
    G->arc[6][5] = 1;
    G->arc[8][7] = 1;
    G->arc[9][10] = 1;
    G->arc[9][11] = 1;
    G->arc[10][13] = 1;
    G->arc[12][9] = 1;
    
}

void CreateALGraph(MGraph G, GraphAdjList *GL) {
    int i, j;
    EdgeNode *e;
    
    *GL = (GraphAdjList)malloc(sizeof(graphAdjList));
    (*GL)->numVertexes = G.numVertexes;
    (*GL)->numEdges = G.numEdges;
    
    for(i = 0;i < G.numVertexes; i++) {
        (*GL)->adjList[i].in = 0;
        (*GL)->adjList[i].data = G.vexs[i];
        (*GL)->adjList[i].firstedge = NULL;
    }
    
    for(i = 0; i<G.numVertexes; i++) {
        for(j = 0; j<G.numVertexes; j++) {
            if (G.arc[i][j] == 1) {
                e = (EdgeNode *)malloc(sizeof(EdgeNode));
                e->adjvex = j;
                e->next = (*GL)->adjList[i].firstedge;
                (*GL)->adjList[i].firstedge = e;
                (*GL)->adjList[j].in++;
            }
        }
    }
}

Status TopologicalSort(GraphAdjList GL) {
    int *stack = malloc(sizeof(int) * GL->numVertexes);
    int top = 0;
    for (int i = 0; i < GL->numVertexes; i++) {
        if (GL->adjList[i].in == 0) {
            stack[++top] = i;
        }
    }
    
    EdgeNode *e;
    int getTop, k;
    int count = 0;
    while (top != 0) {
        getTop = stack[top--];
        printf("%d -> ", GL->adjList[getTop].data);
        count++;
        
        for (e = GL->adjList[getTop].firstedge; e; e = e->next) {
            k = e->adjvex;
            if (--GL->adjList[k].in == 0) {
                stack[++top] = k;
            }
        }
    }
    
    if (count < GL->numVertexes) {
        return ERROR;
    }
    
    return OK;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("拓扑排序!\n");
    MGraph G;
    GraphAdjList GL;
    int result;
    CreateMGraph(&G);
    CreateALGraph(G, &GL);
    result = TopologicalSort(GL);
    printf("result: %d \n", result);
    return 0;
}