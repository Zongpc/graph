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
#include <string.h>

// 比较函数，用于 qsort
int compare(const void *a, const void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);
    
    if (int_a < int_b) return -1;
    else if (int_a > int_b) return 1;
    else return 0;
}

// 计算基本统计量：最小值、最大值、平均值、中位数
void calculateStatistics(int *array, int size, int *min, int *max, double *average, double *median) {
    if (size <= 0) {
        fprintf(stderr, "数组大小必须大于零。\n");
        exit(EXIT_FAILURE);
    }

    // 初始化最小值和最大值
    *min = array[0];
    *max = array[0];
    long long sum = 0;

    // 遍历数组以计算最小值、最大值和总和
    for (int i = 0; i < size; i++) {
        if (array[i] < *min) {
            *min = array[i];
        }
        if (array[i] > *max) {
            *max = array[i];
        }
        sum += array[i];
    }

    // 计算平均值
    *average = (double)sum / size;

    // 计算中位数
    // 需要先对数组进行排序
    int *sorted = (int *)malloc(size * sizeof(int));
    if (sorted == NULL) {
        perror("内存分配失败");
        exit(EXIT_FAILURE);
    }
    memcpy(sorted, array, size * sizeof(int));
    qsort(sorted, size, sizeof(int), compare);

    if (size % 2 == 0) {
        *median = (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
    } else {
        *median = sorted[size / 2];
    }

    free(sorted);
}

// 计算频率分布
void calculateFrequency(int *array, int size, int min, int max, int *frequency) {
    for (int i = 0; i < size; i++) {
        frequency[array[i] - min]++;
    }
}



int adjListAna(int *data, int size) {

    // 计算基本统计量
    int min, max;
    double average, median;
    calculateStatistics(data, size, &min, &max, &average, &median);

    // 输出基本统计量
    printf("数组基本统计量:\n");
    printf("最小值 (Min): %d\n", min);
    printf("最大值 (Max): %d\n", max);
    printf("平均值 (Average): %.2f\n", average);
    printf("中位数 (Median): %.2f\n\n", median);

    // 计算频率分布
    int range = max - min + 1;
    int *frequency = (int *)calloc(range, sizeof(int));
    if (frequency == NULL) {
        perror("内存分配失败");
        return EXIT_FAILURE;
    }
    calculateFrequency(data, size, min, max, frequency);

    // 输出频率分布
    printf("数据频率分布:\n");
    for (int i = 0; i < range; i++) {
        if (frequency[i] > 0) {
            printf("值 %d: %d 次\n", min + i, frequency[i]);
        }
    }
    printf("\n");

    //// 可选：绘制简单的直方图
    //printf("数据直方图:\n");
    //for (int i = 0; i < range; i++) {
    //    if (frequency[i] > 0) {
    //        printf("%d: ", min + i);
    //        for (int j = 0; j < frequency[i]; j++) {
    //            printf("*");
    //        }
    //        printf(" (%d)\n", frequency[i]);
    //    }
    //}

    // 释放动态分配的内存
    free(frequency);

    return 0;
}