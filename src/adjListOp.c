/*
 * @Author: zongpc zongpc.me@outlook.com
 * @Date: 2024-08-29 10:55:45
 * @LastEditors: zongpc zongpc.me@outlook.com
 * @LastEditTime: 2024-09-18 22:16:32
 * @FilePath: \graph\adjListOp.c
 * @Description: 
 * 
 * Copyright (c) 2024 by zongpc.me@outlook.com, All Rights Reserved. 
 */
#include <stdio.h>
#include <time.h>
#include "adjListGen.h"
#include "queueList.h"
#include "queueStaticList.h"

void takeNap(int count) {
    for (int i = 0; i < count; i++) {
        __asm__ volatile ("nop");
    }
}

void adjListDFS(struct Graph* graph, int startVertex) {
    struct node* adjList = graph->adjLists[startVertex];
    struct node* temp = adjList;

    graph->visited[startVertex] = 1;
    printf("Visited %d \n", startVertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            adjListDFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void adjListBFS(struct Graph* graph, int vertexNum) {
    QueueStatic workQ;
    QueueStaticInit(&workQ, vertexNum);

    int adjVertex;
    int currentVertex;
    unsigned int totalVertexCnt = 0;
    unsigned int treeVertexCnt = 0;
    unsigned int treeVertexCntMax = 0;
    unsigned int treeVertexSrc;
    unsigned int QueryNap = 0;
    struct node* tmpNode; 
    
    for(int i=0; i<vertexNum; i++) {
        treeVertexCnt = 0; 
        if (graph->visited[i] == 0) {
            graph->visited[i] = 1;

            QueueStaticPush(&workQ, i);
//            QueueStaticPush(&workQ, startVertx);

            while (!QueueStaticEmpty(&workQ)) {
                //takeNap(10);
                currentVertex = QueueStaticFront(&workQ);
                QueueStaticPop(&workQ);
                //printf("Visited %d\n", currentVertex);

                tmpNode = graph->adjLists[currentVertex];

                while (tmpNode) {
                    adjVertex = tmpNode->vertex;
                    tmpNode = tmpNode->next;
                    if (graph->visited[adjVertex] == 0) {
                        graph->visited[adjVertex] = 1;
                        QueueStaticPush(&workQ, adjVertex);
                        totalVertexCnt = totalVertexCnt + 1;
                        treeVertexCnt = treeVertexCnt + 1;
                    }
                    //QueryNap = QueryNap + takeNap(10);
                    //takeNap(100);
                }
            }
            if (graph->outDegree[i] != 0) {
                if(treeVertexCnt > treeVertexCntMax){
                    treeVertexCntMax = treeVertexCnt;
                    treeVertexSrc =i;
                }
            }
        }
    }
    printf("\n %d vertices are visisted!\n",totalVertexCnt);
    printf("\n %d vertices on the biggest tree start from %d\n",treeVertexCntMax,treeVertexSrc);
//    printf("\n %d Qurey Naps are taken!\n",QueryNap);
}

void adjListTopoSort(struct Graph* graph,  int vertexNum, int dirFlag) {
    int *afterSort;
    QueueStatic workQ;

    afterSort = malloc(vertexNum * sizeof(QSDataType));

    QueueStaticInit(&workQ, vertexNum);

    for(int i = 0 ; i < vertexNum ; i++) {
        if (dirFlag == 1) {
            if (graph->inDegree[i] == 0) {
                QueueStaticPush(&workQ, i);
            }
        } else {
            if (graph->inDegree[i] <= 1) {
                QueueStaticPush(&workQ, i);
            }
        }
    }

    int j = 0;
    while (!QueueStaticEmpty(&workQ)) {
        int tmpVertex = QueueStaticFront(&workQ);
        int tmpIndegree;
        QueueStaticPop(&workQ);
        afterSort[j] = tmpVertex;
        j++;
        struct node* tmpNode = graph->adjLists[tmpVertex]; 
        while (tmpNode) {
            tmpVertex = tmpNode->vertex;
            tmpNode = tmpNode->next;
            graph->inDegree[tmpVertex] --; 
            tmpIndegree = graph->inDegree[tmpVertex]; 
            if (tmpIndegree <= 1-dirFlag) {
                QueueStaticPush(&workQ,tmpVertex);
            }
        }
    }
    if (j == vertexNum) {
        printf("\n Path:");
        printf("\n %d vertices are sorted!",j);
        //for(int k=0 ; k<vertexNum; k++) {
        //    printf("%d -> ", afterSort[k]);
        //}
    } else {
        printf("\n Warning! There is a loop! \n");
        for(int l=0 ; l<vertexNum; l++) {
            if(graph->inDegree[l] > 1-dirFlag) {
                printf("vertex-%d is in a loop ;", l);
            }
        }
    }
}

void adjListMSTPrim(struct Graph* graph,  int startVertex, int vertexNum, int MaxInt) {
    int refVertex;
    int *MSTNodes;
    int *MSTDist;
    int minWeight = MaxInt;
    int i,j,k;
    MSTNodes = malloc(vertexNum * sizeof(int));
    MSTDist = malloc(vertexNum * sizeof(int));
    for (i = 0 ; i < vertexNum; i++) {
        MSTNodes[i] = -1;
        MSTDist[i] = MaxInt;
        graph -> visited[i] = 0;
        
    }
    MSTDist[startVertex] = 0;
    for (i = 0 ; i < vertexNum ; i++) {
        refVertex = -1;
        minWeight = MaxInt;
        for (j = 0 ; j < vertexNum ; j++) {
            if ((!graph->visited[j]) &&  MSTDist[j] < minWeight) {
                refVertex = j;
                minWeight = MSTDist[j];
            }
        }
        if (refVertex == -1) break;
        graph->visited[refVertex] = 1;
        struct node* tmpNode = graph->adjLists[refVertex];
        while (tmpNode) {
            int adjVertex = tmpNode -> vertex;
            int adjWeight = tmpNode -> weight;
            tmpNode = tmpNode -> next;
            if ((!graph->visited[adjVertex]) &&  adjWeight < MSTDist[adjVertex]) {
                MSTDist[adjVertex] = adjWeight;
                MSTNodes[adjVertex] = refVertex;
            }
        }
    }
    //printf("\n Minimum Spanning Tree(MST): ");
	int sumWeight = 0;
    QueueStatic freeQ;
    QueueStaticInit(&freeQ, vertexNum);
	for (i = 0; i < vertexNum; i++) {
		if (MSTNodes[i] != -1) {
			//printf("<%d,%d>  ", i,  MSTNodes[i]);
		    sumWeight += MSTDist[i];
		}else if (i != startVertex) {
            QueueStaticPush(&freeQ, i);
        }
	}
    printf("\n Sum of weights on the tree: %d\n" , sumWeight);
    /*
    if (!QueueStaticEmpty(&freeQ)) {
        printf("\n The vertices not on the tree: {");
        while (!QueueStaticEmpty(&freeQ)) {
            int freeVertex = QueueStaticFront(&freeQ);
            QueueStaticPop(&freeQ);
            printf(" %d " , freeVertex);
        }
        printf("} \n");
    }
    */
}
        
void adjListMSTPrimQ(struct Graph* graph,  int startVertex, int vertexNum, int MaxInt) {
    int *MSTNodes;
    int *MSTDist;
    QueueStatic workQ;
    QueueStaticInit(&workQ, vertexNum);
    int minWeight = MaxInt;
    int i,j,k;
    MSTNodes = malloc(vertexNum * sizeof(int));
    MSTDist = malloc(vertexNum * sizeof(int));
    for (i = 0 ; i < vertexNum; i++) {
        MSTNodes[i] = -1;
        MSTDist[i] = MaxInt;
        graph -> visited[i] = 0;
        
    }
    MSTDist[startVertex] = 0;
    QueueStaticPush(&workQ,startVertex);
    while(!QueueStaticEmpty(&workQ)) {
        int refVertex = QueueStaticFront(&workQ);
        graph->visited[refVertex] = 1;
        QueueStaticPop(&workQ);
        struct node* tmpNode = graph->adjLists[refVertex];
        while (tmpNode) {
            int adjVertex = tmpNode -> vertex;
            int adjWeight = tmpNode -> weight;
            tmpNode = tmpNode -> next; 
            //if ((!graph->visited[adjVertex]) && tmpNode -> weight < MSTDist[adjVertex]) {
            if (adjWeight < MSTDist[adjVertex]) {
                MSTDist[adjVertex] = adjWeight;
                MSTNodes[adjVertex] = refVertex; 
                if (!graph->visited[adjVertex]) {
                    QueueStaticPush(&workQ,adjVertex);
                }
            }
        }
    }
    //printf("\n Minimum Spanning Tree(MST): ");
	int sumWeight = 0;
    QueueStatic freeQ;
    QueueStaticInit(&freeQ, vertexNum);
	for (j = 0; j < vertexNum; j++) {
		if (MSTNodes[j] != -1) {
			//printf("<%d,%d>  ", j,  MSTNodes[j]);
		    sumWeight += MSTDist[j];
		}else if (j != startVertex) {
            QueueStaticPush(&freeQ, j);
        }
	}
    printf("\n Sum of weights on the tree: %d" , sumWeight);
    /*
    if (!QueueStaticEmpty(&freeQ)) {
        printf("\n The vertices not on the tree: {");
        //while (!QueueStaticEmpty(&freeQ)) {
        //    int freeVertex = QueueStaticFront(&freeQ);
        //    QueueStaticPop(&freeQ);
        //    printf(" %d " , freeVertex);
        //}
        printf("} \n");
    }
    */
}

void adjListSSSP(struct Graph* graph,  int startVertex, int vertexNum, int MaxInt) {
    int *SSSPNodes;
    int *SSSPDist;
    QueueStatic workQ;
    QueueStaticInit(&workQ, vertexNum);
    int minWeight = MaxInt;
    int i,j,k;
    SSSPNodes = malloc(vertexNum * sizeof(int));
    SSSPDist = malloc(vertexNum * sizeof(int));
    for (i = 0 ; i < vertexNum; i++) {
        SSSPNodes[i] = -1;
        SSSPDist[i] = MaxInt;
        graph -> visited[i] = 0;
        
    }
    SSSPDist[startVertex] = 0;
    QueueStaticPush(&workQ,startVertex);
    while(!QueueStaticEmpty(&workQ)) {
        int refVertex = QueueStaticFront(&workQ);
        graph->visited[refVertex] = 1;
        QueueStaticPop(&workQ);
        struct node* tmpNode = graph->adjLists[refVertex];
        while (tmpNode) {
            int adjVertex = tmpNode -> vertex;
            int adjWeight = tmpNode -> weight;
            tmpNode = tmpNode -> next; 
            int tmpDist = adjWeight + SSSPDist[refVertex];
            if (tmpDist < SSSPDist[adjVertex]) {
                SSSPDist[adjVertex] = tmpDist;
                SSSPNodes[adjVertex] = refVertex; 
                if (!graph->visited[adjVertex]) {
                    QueueStaticPush(&workQ,adjVertex);
                }
            }
        }
    }
    //printf("\n Single Source Shortest Path(SSSP): ");
	int sumWeight = 0;
    QueueStatic freeQ;
    QueueStaticInit(&freeQ, vertexNum);
	for (j = 0; j < vertexNum; j++) {
		if (SSSPNodes[j] != -1) {
			//printf("<%d,%d>  ", j,  SSSPNodes[j]);
		    sumWeight += SSSPDist[j];
		}else if (j != startVertex) {
            QueueStaticPush(&freeQ, j);
        }
	}
    printf("\n Sum of weights on the tree: %d\n" , sumWeight);
    /*
    if (!QueueStaticEmpty(&freeQ)) {
        printf("\n The vertices not on the tree: {");
        while (!QueueStaticEmpty(&freeQ)) {
            int freeVertex = QueueStaticFront(&freeQ);
            QueueStaticPop(&freeQ);
            printf(" %d " , freeVertex);
        }
        printf("} \n");
    }
    */
}
