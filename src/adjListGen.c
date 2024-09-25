/*
 * @Author: zongpc zongpc.me@outlook.com
 * @Date: 2024-08-28 11:53:07
 * @LastEditors: zongpc zongpc.me@outlook.com
 * @LastEditTime: 2024-08-31 17:22:06
 * @FilePath: \graph\adjLlistGen.c
 * @Description: 
 * 
 * Copyright (c) 2024 by zongpc.me@outlook.com, All Rights Reserved. 
 */
#include <stdio.h>
#include <stdlib.h>

#include "adjListGen.h"

// Create a node
struct node* createNode(int v, int w) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->weight = w;
  newNode->next = NULL;
  return newNode;
}

// Create a graph
struct Graph* createAGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));

  graph->visited = malloc(vertices * sizeof(int));

  graph->inDegree = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
    graph->inDegree[i] = 0;
  }

  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int s, int d , int w ,int dirFlag) {
    // Add edge from s to d
    struct node* newNode = createNode(d,w);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;
    graph->inDegree[d] = graph->inDegree[d] + 1;

    if (dirFlag == 0) {
        // Add edge from d to s
        newNode = createNode(s,w);
        newNode->next = graph->adjLists[d];
        graph->adjLists[d] = newNode;
        graph->inDegree[s] = graph->inDegree[s] + 1;
    }
}

// Print the graph
void printGraph(struct Graph* graph) {
    int v;
    int tmpIndegree;
    for (v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        tmpIndegree = graph->inDegree[v];
        printf("\n vertex %d ,indgree %d\n: ", v , tmpIndegree);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}


