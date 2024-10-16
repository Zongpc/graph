/*
 * @Author: zongpc zongpc.me@outlook.com
 * @Date: 2024-08-29 10:42:04
 * @LastEditors: zongpc zongpc.me@outlook.com
 * @LastEditTime: 2024-09-18 22:11:22
 * @FilePath: \graph\datasetGet.c
 * @Description: 
 * 
 * Copyright (c) 2024 by zongpc.me@outlook.com, All Rights Reserved. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "adjListGen.h"
#include "adjListOp.h"
#include "adjListGraphRead.h"
#include "adjListAna.h"

#include "../../gem5_study/include/gem5/m5ops.h"

#define MAX_TOKENS 4 


int main (int argc, char *argv[]) {
    FILE *file;
    char buffer[256];
    int vertexNum; 
    int sourceID;
    int destID;
    int maxSrcId = 0;
    int maxDstId = 0;
    int timeStamp;
    int overflowFlag = 0;
    int paramDIR ;

    int j;


    //check integrity of input argv 
    if (argc < 3) {
        printf("Please enter the dataset path, the max number of the vertices and DIRECTION param of the graph(1:DIR,0:UNDIR), like: ./datasetGet ../../dataset/xxx.txt 1024 1\n");
    //    return 1;
    }

    vertexNum = atoi(argv[2]);
    printf("vertexNum:%d \n",vertexNum);

    int tmpDIR = atoi(argv[3]);

    if(tmpDIR == 1) {
        paramDIR = DIRECT;
    } else if(tmpDIR == 0){
        paramDIR = UNDIRECT;
    } else {
        printf("Input Error! DIRECTION param of the graph(1:DIR,0:UNDIR)\n");
        return 1;
    }

    struct Graph* graph = createAGraph(vertexNum);
    char* filename = argv[1];

    clock_t read_start, read_end;
    double cpu_read_time_used;
    read_start = clock();
    //adjListGraphRead(filename, graph, vertexNum);

    // 打开文件
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("cannot open file: %s\n", argv[1]);
        return 1;
    }

    // 逐行读取文件内容，并打印到控制台
    printf("start read file\n");
    int tabflag = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char *ptr = buffer;
        if(containsTab(ptr) || tabflag ==1){
            tabflag == 1;
        }
        char *token;
        if(tabflag == 1) {
            token = strtok(buffer, "\t");
        } else {
            token = strtok(buffer, " ");
        }
        int i = 0;
        if (token[0] == '#') {
            continue;
        } else {
            while (token != NULL && i < MAX_TOKENS) {
                //printf("%s\n", token);
                switch (i) {
                    case 0:
                        sourceID = atoi(token); 
                        break;
                    case 1:
                        destID = atoi(token); 
                        break;
                    case 2:
                        timeStamp = atoi(token); 
                        break;
                    default:
                        break;} 
                i++;
                token = strtok(NULL, "\t");
            }
            //printf("sourceID:%d   ,destID:%d \n", sourceID, destID);
        }
        if (sourceID > maxSrcId){
            maxSrcId = sourceID;
        }
        if (destID > maxDstId){
            maxDstId = destID;
            //printf("\n destID:%d, maxDstID:%d\n",destID, maxDstId);
        }
        if (maxDstId >= vertexNum || maxSrcId >= vertexNum){
            overflowFlag = 1;
        } else {
            addEdge(graph, sourceID, destID, 1, paramDIR);
            j++;
        }
    }
   // 关闭文件
    fclose(file);

    printf("\n*maxSrcID: %d, maxDstId: %d.", maxSrcId, maxDstId);
    if(overflowFlag){
        printf("\n*Sorry, vertexNum enter is too small!\n");
        return 1;
    }
    
    read_end = clock();
    cpu_read_time_used = ((double) (read_end - read_start)) / CLOCKS_PER_SEC;
    printf("\n*Read time taken: %f seconds\n", cpu_read_time_used);

    adjListAna(graph->outDegree, vertexNum);
    //printGraph(graph);
    //printAdjListPtr(graph);

    //----------gen an test example graph----------
    //int main() {
        struct Graph* graphT = createAGraph(6);
        addEdge(graphT, 0, 1 , 1,DIRECT);
        addEdge(graphT, 0, 4 , 1,DIRECT);
        addEdge(graphT, 0, 2 , 4,DIRECT);
        addEdge(graphT, 0, 3 , 20,DIRECT);
        addEdge(graphT, 4, 3 , 10,DIRECT);
        addEdge(graphT, 2, 3 , 8,DIRECT);
        addEdge(graphT, 3, 5 , 1,DIRECT);
    
        printGraph(graphT);
    
    //    return 0;
    //}
    //---------------------------------------------

    clock_t start, end;
    double cpu_time_used;

    //------------------hot cache------------------
    //start = clock();
    //adjListBFS(graph, vertexNum);
    //end = clock();
    //cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //printf("\n*Time taken: %f seconds\n", cpu_time_used);

    //for(int i=0; i<vertexNum; i++) {
    //    graph->visited[i] = 0;
    //}
    //------------------hot cache------------------

#ifdef USEM5
    m5_checkpoint(0,0);
    m5_reset_stats(0,0);
#endif

    start = clock();
#ifdef BFS
    adjListBFS(graph, vertexNum);
#elif PRIM 
    adjListMSTPrimQ(graph, 1, vertexNum, 100) ;
#elif SSSP
    adjListSSSP(graph, 1, vertexNum, 100) ;
#endif
    end = clock();

#ifdef USEM5
    m5_dump_stats(0,0);
#endif

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\n*Time taken: %f seconds\n", cpu_time_used);



    //adjListMSTPrimQ(graphT, 0, 6, 20) ;
    //adjListMSTPrimQ(graph, 8, vertexNum, 100) ;

    //adjListSSSP(graphT, 0, 6, 20) ;

    //adjListMSTPrimQ(graph, 0, vertexNum, 5000) ;

    
    return 0;
}

