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
#ifndef __ADJLISTGRAPHREAD_H__
#define __ADJLISTGRAPHREAD_H__
#include "adjListGen.h"

#define MAX_TOKENS 4 

#define READ_BUFFER_SIZE (64 * 1024) // 64KB
#define INITIAL_LINE_BUFFER_SIZE 1024

int containsTab(const char *str);

int adjListGraphRead(char *filename, struct Graph* graph, int vertexNum);

void lineProcess(char *line, struct Graph* graph);

#endif