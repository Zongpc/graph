/*
 * @Author: zongpc zongpc.me@outlook.com
 * @Date: 2024-08-30 12:01:12
 * @LastEditors: zongpc zongpc.me@outlook.com
 * @LastEditTime: 2024-08-30 17:21:33
 * @FilePath: \graph\queueList.c
 * @Description: 
 * 
 * Copyright (c) 2024 by zongpc.me@outlook.com, All Rights Reserved. 
 */
#ifndef __DATATYPE_H__
#define __DATATYPE_H__

#include<stdio.h>    
#include<stdlib.h>  
#include<stdbool.h> 
//#include<assert.h> 
#include "queueList.h"

// 队列的初始化函数  
void QueueInit(Queue* pq) {  
//    assert(pq); // 断言确保传入的队列指针不为空，这是一种常见的错误检查机制  
    pq->phead = NULL; // 初始化队列的头部指针为NULL，表示队列开始时是空的  
    pq->ptail = NULL; // 初始化队列的尾部指针为NULL  
    pq->size = 0;     // 初始化队列的大小为0，表示队列中没有元素  
}

// 队列的销毁  
void QueueDestroy(Queue* pq) {  
//    assert(pq); // 确保pq不是NULL  
  
    QNode* cur = pq->phead; // 从队列头部开始遍历  
    while (cur) {  
        QNode* next = cur->next; // 保存下一个节点的指针  
        free(cur); // 释放当前节点的内存  
        cur = next; // 移动到下一个节点  
    }  
    pq->phead = pq->ptail = NULL; // 将队列的头部和尾部指针设置为NULL  
    pq->size = 0; // 重置队列大小为0  
}

// 入队列函数  
void QueuePush(Queue* pq, QDataType x) {    
    // 断言检查pq指针是否为空，如果为空则程序终止，确保pq是有效的指针  
//    assert(pq);    
      
    // 动态分配内存以创建一个新的队列节点  
    QNode* newNode = (QNode*)malloc(sizeof(QNode));    
      
    // 检查内存分配是否成功  
    if (newNode == NULL) {    
        // 如果内存分配失败，打印错误信息  
        perror("malloc fail");    
        return;  // 并提前退出函数  
    }    
    // 将新节点的值设置为传入的x  
    newNode->val = x;    
    // 将新节点的next指针设置为NULL，因为它是新添加的尾部节点  
    newNode->next = NULL;    
    
    // 检查队列是否为空  
    if (pq->phead == NULL) {    
        // 如果队列为空，则将队列的头部和尾部指针都设置为新节点  
        pq->phead = pq->ptail = newNode;    
    } else {    
        // 如果队列不为空，则将新节点添加到队列的尾部  
        pq->ptail->next = newNode;    
        pq->ptail = newNode; // 更新尾部指针为新节点  
    }    
    
    // 队列大小加1  
    pq->size++;    
}


// 出队列函数  
void QueuePop(Queue* pq) {  
    // 断言检查pq指针是否为空，确保pq是有效的指针  
//	assert(pq);  
  
	// 温柔地检查队列是否为空  
	if (pq->phead == NULL) {  
		return; // 如果队列为空，则直接返回，不进行任何操作  
	}  
  
	// 暴力检查，断言队列头部指针不为空，如果为空则程序终止,两种检查任选一种即可
	// assert(pq->phead);  
  
	// 检查队列中是否只有一个节点  
	if (pq->phead->next == NULL) {  
		free(pq->phead); // 释放队列头部节点的内存  
		pq->phead = pq->ptail = NULL; // 将队列的头部和尾部指针都设置为NULL  
	}  
	// 队列中有两个及以上节点  
	else {  
		QNode* next = pq->phead->next; // 保存下一个节点的指针  
		free(pq->phead); // 释放队列头部节点的内存  
		pq->phead = next; // 将队列的头部指针指向下一个节点  
	}  
  
	pq->size--; // 队列大小减1  
}


//获取队头数据
QDataType QueueFront(Queue* pq) {
//	assert(pq);
//	assert(pq->phead);
	return pq->phead->val;
}



// 获取队尾数据函数  
QDataType QueueBack(Queue* pq) {  
    // 使用assert宏进行断言，确保传入的队列指针pq不为NULL  
    // 如果pq为NULL，则程序会在这里终止，并报告错误  
//	assert(pq);  
      
    // 再次使用assert宏进行断言，这次确保队列的尾部指针ptail不为NULL  
    // 这意味着队列中至少应该有一个元素，因为ptail指向队列的最后一个元素  
    // 如果ptail为NULL，说明队列为空，此时获取队尾数据没有意义，程序会终止并报告错误  
//	assert(pq->ptail);  
      
    // 返回队尾元素的数据值  
    // pq->ptail指向队尾元素，pq->ptail->val就是队尾元素的数据值  
	return pq->ptail->val;  
}


// 判断队列是否为空函数  
bool QueueEmpty(Queue* pq) {  
//	assert(pq);  
      
    // 判断队列大小是否为0，如果是，则返回true，表示队列为空  
    // 否则返回false，表示队列不为空  
	return pq->size == 0;  
}


//------------------------------

#endif