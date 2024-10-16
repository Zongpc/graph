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
#ifndef __ADJLISTANA_H__
#define __ADJLISTANA_H__

int adjListAna(int *data, int size);
void calculateStatistics(int *array, int size, int *min, int *max, double *average, double *median);
void calculateFrequency(int *array, int size, int min, int max, int *frequency);
int compare(const void *a, const void *b);

#endif