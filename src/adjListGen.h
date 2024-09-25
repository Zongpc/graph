/*
 * @Author: zongpc zongpc.me@outlook.com
 * @Date: 2024-08-29 10:16:48
 * @LastEditors: zongpc zongpc.me@outlook.com
 * @LastEditTime: 2024-08-31 10:44:35
 * @FilePath: \graph\adjListGen.h
 * @Description: 
 * 
 * Copyright (c) 2024 by zongpc.me@outlook.com, All Rights Reserved. 
 */
#ifndef __ADJLISTGEN_H__
#define __ADJLISTGEN_H__


#define DIRECT      1
#define UNDIRECT    0

//----------graph data--------
struct node{
  int vertex;
  int weight;
  struct node* next;
};

struct Graph{
  int numVertices;
  int* visited;
  int* inDegree;
  struct node** adjLists;
};
//----------------------------

//----------function----------
// Create a node
struct node* createNode(int v , int w);


// Create a graph
struct Graph* createAGraph(int vertices);


// Add edge
void addEdge(struct Graph* graph, int s, int d ,int w, int dirFlag);

// Print the graph
void printGraph(struct Graph* graph);
//------------------------

#endif
