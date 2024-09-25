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
#include "adjListGen.h"
#include "adjListOp.h"

#define MAX_TOKENS 4 

int main (int argc, char *argv[]) {
    FILE *file;
    char buffer[512];
    int vertexNum; 
    int sourceID;
    int destID;
    int timeStamp;

    int j;


    //check integrity of input argv 
    if (argc < 2) {
        printf("Please enter the dataset path and the max number of the vertices, like: ./datasetGet ../../dataset/xxx.txt 1024 \n");
    //    return 1;
    }

    vertexNum = atoi(argv[2]);
    printf("vertexNum:%d \n",vertexNum);

    struct Graph* graph = createAGraph(vertexNum);

    // 打开文件
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("cannot open file: %s\n", argv[1]);
    //    return 1;
    }

    // 逐行读取文件内容，并打印到控制台
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char *token = strtok(buffer, "\t");
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
        addEdge(graph, sourceID, destID, i, UNDIRECT);
        j++;
    }
    
    

    // 关闭文件
    //fclose(file);

    
    //printGraph(graph);

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

    //adjListTopoSort(graphT, 10, 1);

    adjListBFS(graph, 3, vertexNum);
    
    adjListMSTPrimQ(graphT, 0, 6, 20) ;

    adjListSSSP(graphT, 0, 6, 20) ;

    //adjListMSTPrimQ(graph, 0, vertexNum, 5000) ;

    
    return 0;
}

