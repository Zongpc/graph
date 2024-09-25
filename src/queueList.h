/*
 * @Author: zongpc zongpc.me@outlook.com
 * @Date: 2024-08-30 12:01:12
 * @LastEditors: zongpc zongpc.me@outlook.com
 * @LastEditTime: 2024-08-30 12:25:16
 * @FilePath: \graph\queueList.h
 * @Description: 
 * 
 * Copyright (c) 2024 by zongpc.me@outlook.com, All Rights Reserved. 
 */
#ifndef __QUEUELIST_H__
#define __QUEUELIST_H__

#include<stdio.h>    
#include<stdlib.h>  
#include<stdbool.h> 
#include<assert.h> 


//----------queue data----------
// 定义队列中存储的数据类型为整数  
typedef int QDataType;  
  
// 定义队列节点的结构体  
typedef struct QueueNode {  
    QDataType val;         // 节点中存储的数据值  
    struct QueueNode* next; // 指向下一个节点的指针  
} QNode;  // QNode是队列节点的类型别名  
  
// 定义队列的结构体  
typedef struct Queue {  
    QNode* phead; // 指向队列头部的指针，若队列为空，则此指针为NULL  
    QNode* ptail; // 指向队列尾部的指针，若队列为空，则此指针为NULL  
    int size;     // 表示队列中当前元素的数量  
} Queue;  // Queue是队列的类型别名

//队列的初始化
void QueueInit(Queue* pq) ;

//队列的销毁
void QueueDestory(Queue* pq) ;

//入队列
void QueuePush(Queue* pq, QDataType x) ;

//出队列
void QueuePop(Queue* pq) ;

//获取队头数据
QDataType QueueFront(Queue* pq) ;

//获取队尾数据
QDataType QueueBack(Queue* pq) ;

//判断队列是否为空
bool QueueEmpty(Queue* pq) ;
//------------------------------

#endif