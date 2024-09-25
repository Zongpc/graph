/*
 * @Author: zongpc zongpc.me@outlook.com
 * @Date: 2024-08-29 10:55:45
 * @LastEditors: zongpc zongpc.me@outlook.com
 * @LastEditTime: 2024-09-18 19:58:01
 * @FilePath: \graph\adjListOp.h
 * @Description: 
 * 
 * Copyright (c) 2024 by zongpc.me@outlook.com, All Rights Reserved. 
 */
#ifndef __ADJLISTOP_H__
#define __ADJLISTOP_H__
#include "adjListGen.h"

void adjListDFS(struct Graph* graph, int startVertex) ;

void adjListBFS(struct Graph* graph, int startVertex, int vertexNum) ;

void adjListTopoSort(struct Graph* graph, int vertexNum, int dirFlag) ;

void adjListMSTPrim(struct Graph* graph,  int startVertex, int vertexNum, int MaxInt) ;

void adjListMSTPrimQ(struct Graph* graph,  int startVertex, int vertexNum, int MaxInt) ;

void adjListSSSP(struct Graph* graph,  int startVertex, int vertexNum, int MaxInt) ;

#endif
