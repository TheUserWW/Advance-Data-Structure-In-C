// priority_queue.h
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// 定义优先队列结构体
typedef struct {
    int *heap;          // 存储数据的堆数组
    int capacity;       // 队列容量
    int count;          // 当前元素数量
    int max_leaf;       // 当前堆中最大的叶子节点元素(用于快速获取back)
} PriorityQueue;

// 创建优先队列
PriorityQueue* pq_create(int max_size) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->heap = (int*)malloc(sizeof(int) * (max_size + 1)); // 从索引1开始存储
    pq->capacity = max_size;
    pq->count = 0;
    pq->max_leaf = INT_MIN;
    return pq;
}

// 释放优先队列
void pq_free(PriorityQueue *pq) {
    free(pq->heap);
    free(pq);
}

// 交换两个元素
static void pq_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 上浮操作
static void pq_swim(PriorityQueue *pq, int k) {
    while (k > 1 && pq->heap[k/2] > pq->heap[k]) {
        pq_swap(&pq->heap[k/2], &pq->heap[k]);
        k /= 2;
    }
}

// 下沉操作
static void pq_sink(PriorityQueue *pq, int k) {
    while (2*k <= pq->count) {
        int j = 2*k;
        if (j < pq->count && pq->heap[j] > pq->heap[j+1]) {
            j++;
        }
        if (pq->heap[k] <= pq->heap[j]) {
            break;
        }
        pq_swap(&pq->heap[k], &pq->heap[j]);
        k = j;
    }
}

// 检查队列是否为空
bool pq_empty(PriorityQueue *pq) {
    return pq->count == 0;
}

// 检查队列是否已满
bool pq_full(PriorityQueue *pq) {
    return pq->count == pq->capacity;
}

// 插入元素
void pq_push(PriorityQueue *pq, int value) {
    if (pq_full(pq)) {
        fprintf(stderr, "Priority queue is full!\n");
        return;
    }
    pq->heap[++pq->count] = value;
    
    // 更新最大叶子节点信息
    if (value > pq->max_leaf) {
        pq->max_leaf = value;
    }
    
    pq_swim(pq, pq->count);
}

// 获取前端元素(最小元素)
int pq_front(PriorityQueue *pq) {
    if (pq_empty(pq)) {
        fprintf(stderr, "Priority queue is empty!\n");
        return INT_MAX; // 返回最大值表示错误
    }
    return pq->heap[1];
}

// 获取后端元素(最大元素)
int pq_back(PriorityQueue *pq) {
    if (pq_empty(pq)) {
        fprintf(stderr, "Priority queue is empty!\n");
        return INT_MIN; // 返回最小值表示错误
    }
    
    // 如果只有一个元素，它就是最大和最小值
    if (pq->count == 1) {
        return pq->heap[1];
    }
    
    // 返回我们维护的最大叶子节点值
    return pq->max_leaf;
}

// 删除并返回前端元素
int pq_pop(PriorityQueue *pq) {
    if (pq_empty(pq)) {
        fprintf(stderr, "Priority queue is empty!\n");
        return INT_MAX; // 返回最大值表示错误
    }
    int min = pq->heap[1];
    pq_swap(&pq->heap[1], &pq->heap[pq->count--]);
    pq_sink(pq, 1);
    
    // 如果删除的元素是当前最大叶子节点，需要重新查找
    if (min == pq->max_leaf) {
        pq->max_leaf = INT_MIN;
        int first_leaf = (pq->count / 2) + 1;
        for (int i = first_leaf; i <= pq->count; i++) {
            if (pq->heap[i] > pq->max_leaf) {
                pq->max_leaf = pq->heap[i];
            }
        }
    }
    
    return min;
}

// 获取队列元素数量
int pq_size(PriorityQueue *pq) {
    return pq->count;
}

#endif // PRIORITY_QUEUE_H