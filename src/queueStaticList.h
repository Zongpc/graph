/*
 * @Author: zongpc zongpc.me@outlook.com
 * @Date: 2024-08-30 12:01:12
 * @LastEditors: zongpc zongpc.me@outlook.com
 * @LastEditTime: 2024-09-18 20:34:26
 * @FilePath: \graph\queueStaticList.h
 * @Description: 
 * 
 * Copyright (c) 2024 by zongpc.me@outlook.com, All Rights Reserved. 
 */
#ifndef __QUEUESTATICLIST_H__
#define __QUEUESTATICLIST_H__

#include<stdio.h>    
#include<stdlib.h>  
#include<stdint.h>  
#include<stdbool.h> 
#include<assert.h> 


//----------queue data----------
// 定义队列中存储的数据类型为整数  
typedef uint64_t QSDataType;  
  
//// 定义队列节点的结构体  
//typedef struct QueueNode {  
//    QDataType val;         // 节点中存储的数据值  
//    struct QueueNode* next; // 指向下一个节点的指针  
//} QNode;  // QNode是队列节点的类型别名  
  
// 定义队列的结构体  
typedef struct QueueStatic {  
    //dynamic QNode* phead; // 指向队列头部的指针，若队列为空，则此指针为NULL  
    //dynamic QNode* ptail; // 指向队列尾部的指针，若队列为空，则此指针为NULL  
    int size;     // 表示队列中当前元素的数量  
    uint64_t* qlist;  // static list --debug
    int phead;  // static list --debug
    int ptail;  // static list --debug
} QueueStatic;  // Queue是队列的类型别名

//队列的初始化
void QueueStaticInit(QueueStatic* pq , int max_size) ;

//队列的销毁
void QueueStaticDestory(QueueStatic* pq) ;

//入队列
void QueueStaticPush(QueueStatic* pq, QSDataType x) ;

//出队列
void QueueStaticPop(QueueStatic* pq) ;

//获取队头数据
QSDataType QueueStaticFront(QueueStatic* pq) ;

//获取队尾数据
QSDataType QueueStaticBack(QueueStatic* pq) ;

//判断队列是否为空
bool QueueStaticEmpty(QueueStatic* pq) ;
//------------------------------

#endif