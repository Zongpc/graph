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

//#define ALIGNCACHE

// Create a node
struct node* createNode(int v, int w) {
  struct node* newNode;
#ifdef ALIGNCACHE
  if(posix_memalign((void**)&newNode, CACHELINESIZE, sizeof(node))){
      perror("Aligned allocation Node failed!\n");
      exit(EXIT_FAILURE);
  }
#else
  newNode = malloc(sizeof(struct node));
#endif
  newNode->vertex = v;
  newNode->weight = w;
  newNode->next = NULL;
  return newNode;
}

// Create a graph
struct Graph* createAGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

#ifdef ALIGNCACHE
  if(posix_memalign((void**)&graph->adjLists, CACHELINESIZE, vertices * sizeof(node *))){
      perror("Aligned allocation adjList ptr array failed!\n");
      exit(EXIT_FAILURE);
  }
  
  if(posix_memalign((void**)&graph->visited, CACHELINESIZE, vertices * sizeof(int))){
      perror("Aligned allocation visited array failed!\n");
      exit(EXIT_FAILURE);
  }
 
  if(posix_memalign((void**)&graph->inDegree, CACHELINESIZE, vertices * sizeof(int))){
      perror("Aligned allocation inDegree array failed!\n");
      exit(EXIT_FAILURE);
  }

  if(posix_memalign((void**)&graph->outDegree, CACHELINESIZE, vertices * sizeof(int))){
      perror("Aligned allocation outDegree array failed!\n");
      exit(EXIT_FAILURE);
  }
#else
  graph->adjLists = malloc(vertices * sizeof(struct node*));
  graph->visited = malloc(vertices * sizeof(int));
  graph->inDegree = malloc(vertices * sizeof(int));
  graph->outDegree = malloc(vertices * sizeof(int));
#endif

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
    graph->inDegree[i] = 0;
    graph->outDegree[i] = 0;
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
    graph->outDegree[s] = graph->outDegree[s] + 1;

    if (dirFlag == 0) {
        // Add edge from d to s
        newNode = createNode(s,w);
        newNode->next = graph->adjLists[d];
        graph->adjLists[d] = newNode;
        graph->inDegree[s] = graph->inDegree[s] + 1;
        graph->outDegree[d] = graph->outDegree[d] + 1;
    }
}

// Print the graph
void printGraph(struct Graph* graph) {
    int v;
    int tmpIndegree,tmpOutdegree;
    for (v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        tmpIndegree = graph->inDegree[v];
        tmpOutdegree = graph->outDegree[v];
        printf("\n vertex %d ,indegree %d, outdegree %d\n: ", v , tmpIndegree, tmpOutdegree);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Print the graph adjlist pointer
void printAdjListPtr(struct Graph* graph) {
    // debug int v;
    // debug for (v = 0; v < graph->numVertices; v++) {
    // debug     struct node* temp = graph->adjLists[v];
    // debug     printf("\n vertex %d ,adjList Pointer%lx, node Pointer%lx \n: ", v , &graph->adjLists[v] ,temp);
    // debug     while (temp) {
    // debug         printf("%lx -> ", temp);
    // debug         temp = temp->next;
    // debug     }
    // debug     printf("\n");
    // debug }
}


