// priority_queue.h
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Priority Queue structure (Min-Heap implementation)
// 优先队列结构（最小堆实现）
typedef struct {
    int *heap;          // Heap array starting from index 1 (堆数组，从索引1开始)
    int capacity;       // Current allocated capacity (当前分配的容量)
    int count;          // Current number of elements (当前元素数量)
} PriorityQueue;

// Create an empty priority queue with initial capacity 0
// 创建一个空的优先队列，初始容量为0
PriorityQueue* pq_create() {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->heap = NULL;
    pq->capacity = 0;
    pq->count = 0;
    return pq;
}

// Free the memory used by the priority queue
// 释放优先队列使用的内存
void pq_free(PriorityQueue *pq) {
    free(pq->heap);
    free(pq);
}

// Swap two elements
// 交换两个元素
static void pq_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Swim (heapify up) operation to maintain heap property
// 上浮操作（堆化向上）以维护堆性质
static void pq_swim(PriorityQueue *pq, int k) {
    while (k > 1 && pq->heap[k/2] > pq->heap[k]) {
        pq_swap(&pq->heap[k/2], &pq->heap[k]);
        k /= 2;
    }
}

// Sink (heapify down) operation to maintain heap property
// 下沉操作（堆化向下）以维护堆性质
static void pq_sink(PriorityQueue *pq, int k) {
    while (2*k <= pq->count) {
        int j = 2*k;
        // Choose the smaller child (选择较小的子节点)
        if (j < pq->count && pq->heap[j] > pq->heap[j+1]) {
            j++;
        }
        // Stop if heap property is satisfied (如果堆性质已满足则停止)
        if (pq->heap[k] <= pq->heap[j]) {
            break;
        }
        pq_swap(&pq->heap[k], &pq->heap[j]);
        k = j;
    }
}

// Check if the priority queue is empty
// 检查优先队列是否为空
bool pq_empty(PriorityQueue *pq) {
    return pq->count == 0;
}

// Insert an element into the priority queue
// 向优先队列中插入一个元素
void pq_push(PriorityQueue *pq, int value) {
    // Check if resizing is needed (检查是否需要扩容)
    if (pq->count == pq->capacity) {
        int new_capacity = pq->capacity == 0 ? 1 : pq->capacity * 2;
        int *new_heap = (int*)realloc(pq->heap, (new_capacity + 1) * sizeof(int));
        if (!new_heap) {
            fprintf(stderr, "Memory allocation failed!\n");
            return;
        }
        pq->heap = new_heap;
        pq->capacity = new_capacity;
    }
    // Add the new element and perform swim operation
    // 添加新元素并执行上浮操作
    pq->heap[++pq->count] = value;
    pq_swim(pq, pq->count);
}

// Get the front element (minimum value)
// 获取前端元素（最小值）
int pq_front(PriorityQueue *pq) {
    if (pq_empty(pq)) {
        fprintf(stderr, "Priority queue is empty!\n");
        return INT_MAX;
    }
    return pq->heap[1];
}

// Get the back element (maximum value in a min-heap)
// 获取后端元素（最小堆中的最大值）
int pq_back(PriorityQueue *pq) {
    if (pq_empty(pq)) {
        fprintf(stderr, "Priority queue is empty!\n");
        return INT_MIN;
    }
    if (pq->count == 1) {
        return pq->heap[1];
    }
    // The maximum value must be in the leaf nodes
    // 最大值一定在叶子节点中
    int first_leaf = (pq->count / 2) + 1;
    int max_val = INT_MIN;
    for (int i = first_leaf; i <= pq->count; i++) {
        if (pq->heap[i] > max_val) {
            max_val = pq->heap[i];
        }
    }
    return max_val;
}

// Remove and return the front element (minimum value)
// 弹出并返回前端元素（最小值）
int pq_pop(PriorityQueue *pq) {
    if (pq_empty(pq)) {
        fprintf(stderr, "Priority queue is empty!\n");
        return INT_MAX;
    }
    int min = pq->heap[1];
    // Move the last element to the root and sink it
    // 将最后一个元素移到根节点并执行下沉操作
    pq_swap(&pq->heap[1], &pq->heap[pq->count--]);
    pq_sink(pq, 1);

    // Check if shrinking is needed (检查是否需要缩容)
    if (pq->capacity > 0 && pq->count <= pq->capacity / 4) {
        int new_capacity = pq->capacity / 2;
        int *new_heap = (int*)realloc(pq->heap, (new_capacity + 1) * sizeof(int));
        if (new_heap || new_capacity == 0) {
            pq->heap = new_heap;
            pq->capacity = new_capacity;
        }
    }
    return min;
}

// Get the number of elements in the priority queue
// 获取优先队列中的元素数量
int pq_size(PriorityQueue *pq) {
    return pq->count;
}

#endif // PRIORITY_QUEUE_H
