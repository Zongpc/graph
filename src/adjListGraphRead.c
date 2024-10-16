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

#define MAX_TOKENS 4 

#define READ_BUFFER_SIZE (64 * 1024) // 64KB
#define INITIAL_LINE_BUFFER_SIZE 1024

int containsTab(const char *str) {
    while (*str) {
        if (*str == '\t') {
            return 1; // 找到制表符
        }
        str++;
    }
    return 0; // 没有制表符
}

void lineProcess(char *line, struct Graph* graph){
    int tabflag = 0;
    int sourceID;
    int destID;
    int timeStamp;

    int j;

    if(containsTab(line) || tabflag ==1){
        tabflag == 1;
    }
    char *token;
    if(tabflag == 1) {
        token = strtok(line, "\t");
    } else {
        token = strtok(line, " ");
    }
    int i = 0;
    if (token[0] == '#') {
        return ;
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
    addEdge(graph, sourceID, destID, 1, UNDIRECT);
    j++;
}

int adjListGraphRead(char *filename, struct Graph* graph, int vertexNum) {
    FILE *file;

    // 打开文件
    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("cannot open file: %s\n", filename);
    //    return 1;
    }
    // 分配读取缓冲区
    char *read_buffer = malloc(READ_BUFFER_SIZE);
    if (!read_buffer) {
        perror("Failed to allocate read buffer");
        fclose(file);
        return EXIT_FAILURE;
    }

    // 初始化行缓冲区
    size_t line_buffer_size = INITIAL_LINE_BUFFER_SIZE;
    char *line_buffer = malloc(line_buffer_size);
    if (!line_buffer) {
        perror("Failed to allocate line buffer");
        free(read_buffer);
        fclose(file);
        return EXIT_FAILURE;
    }
    line_buffer[0] = '\0'; // 初始化为空字符串
    size_t line_length = 0;

    size_t bytes_read;
    while ((bytes_read = fread(read_buffer, 1, READ_BUFFER_SIZE, file)) > 0) {
        size_t start = 0;
        for (size_t i = 0; i < bytes_read; ++i) {
            // 处理 Windows 的换行符 \r\n
            if (read_buffer[i] == '\n') {
                size_t end = i;
                // 检查前一个字符是否为 \r
                if (i > 0 && read_buffer[i - 1] == '\r') {
                    end = i - 1;
                }

                size_t current_line_part_length = end - start;

                // 计算需要的总长度
                size_t new_total_length = line_length + current_line_part_length + 1; // +1 for null terminator

                // 检查并扩展行缓冲区
                if (new_total_length > line_buffer_size) {
                    while (new_total_length > line_buffer_size) {
                        line_buffer_size *= 2;
                    }
                    char *temp = realloc(line_buffer, line_buffer_size);
                    if (!temp) {
                        perror("Failed to realloc line buffer");
                        free(read_buffer);
                        free(line_buffer);
                        fclose(file);
                        return EXIT_FAILURE;
                    }
                    line_buffer = temp;
                }

                // 复制当前行部分到行缓冲区
                memcpy(line_buffer + line_length, read_buffer + start, current_line_part_length);
                line_length += current_line_part_length;
                line_buffer[line_length] = '\0'; // 添加终止符

                // 处理完整的行
                lineProcess(line_buffer, graph);

                // 重置行缓冲区
                line_length = 0;
                line_buffer[0] = '\0';
                start = i + 1;
            }
        }

        // 处理当前块中未完成的行
        if (start < bytes_read) {
            size_t remaining = bytes_read - start;

            // 计算需要的总长度
            size_t new_total_length = line_length + remaining + 1; // +1 for null terminator

            // 检查并扩展行缓冲区
            if (new_total_length > line_buffer_size) {
                while (new_total_length > line_buffer_size) {
                    line_buffer_size *= 2;
                }
                char *temp = realloc(line_buffer, line_buffer_size);
                if (!temp) {
                    perror("Failed to realloc line buffer");
                    free(read_buffer);
                    free(line_buffer);
                    fclose(file);
                    return EXIT_FAILURE;
                }
                line_buffer = temp;
            }

            // 复制未完成的行部分到行缓冲区
            memcpy(line_buffer + line_length, read_buffer + start, remaining);
            line_length += remaining;
            line_buffer[line_length] = '\0'; // 添加终止符
        }
    }
    // 处理文件末尾可能没有换行符的最后一行
    if (line_length > 0) {
        lineProcess(line_buffer, graph);
    }

    // 清理资源
    free(read_buffer);
    free(line_buffer);
    fclose(file);

    return EXIT_SUCCESS;
}


