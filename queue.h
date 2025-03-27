/**
 * @file queue.h
 * @brief 动态循环队列实现 Dynamic circular queue implementation
 */

 #ifndef QUEUE_H
 #define QUEUE_H
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 typedef struct {
     int *data;      // 存储元素的数组
     int front;      // 队头索引
     int rear;       // 队尾索引
     int capacity;   // 队列容量
     int count;      // 当前元素数量
 } Queue;
 
 // ==================== 基本操作 ====================
 
 /**
  * @brief 创建队列
  * @param initCapacity 初始容量（建议≥2）
  * @return 队列指针
  */
 Queue* queue_create(int initCapacity);
 
 /**
  * @brief 销毁队列
  * @param q 队列指针
  */
 void queue_destroy(Queue *q);
 
 /**
  * @brief 检查队列是否为空
  * @param q 队列指针
  * @return true为空
  */
 bool queue_empty(Queue *q);
 
 /**
  * @brief 获取队列元素数量
  * @param q 队列指针
  * @return 元素个数
  */
 int queue_size(Queue *q);
 
 // ==================== 核心操作 ====================
 
 /**
  * @brief 在队尾插入元素
  * @param q 队列指针
  * @param value 要插入的值
  * @return 成功返回true
  */
 bool queue_push(Queue *q, int value);
 
 /**
  * @brief 移除队首元素
  * @param q 队列指针
  * @return 成功返回true
  */
 bool queue_pop(Queue *q);
 
 /**
  * @brief 获取队首元素
  * @param q 队列指针
  * @return 队首元素（队列空返回-1）
  */
 int queue_front(Queue *q);
 
 /**
  * @brief 获取队尾元素
  * @param q 队列指针
  * @return 队尾元素（队列空返回-1）
  */
 int queue_back(Queue *q);
 
 // ==================== 实现部分 ====================
 #ifdef QUEUE_IMPLEMENTATION
 
 Queue* queue_create(int initCapacity) {
     if (initCapacity < 2) initCapacity = 2;
     
     Queue *q = (Queue*)malloc(sizeof(Queue));
     if (!q) return NULL;
 
     q->data = (int*)malloc(initCapacity * sizeof(int));
     if (!q->data) {
         free(q);
         return NULL;
     }
 
     q->front = 0;
     q->rear = -1;
     q->capacity = initCapacity;
     q->count = 0;
     return q;
 }
 
 void queue_destroy(Queue *q) {
     if (q) {
         free(q->data);
         free(q);
     }
 }
 
 bool queue_empty(Queue *q) {
     return !q || q->count == 0;
 }
 
 int queue_size(Queue *q) {
     return q ? q->count : 0;
 }
 
 static bool queue_expand(Queue *q) {
     int newCapacity = q->capacity * 2;
     int *newData = (int*)malloc(newCapacity * sizeof(int));
     if (!newData) return false;
 
     // 将数据拷贝到新数组（保持顺序）
     for (int i = 0, j = q->front; i < q->count; i++) {
         newData[i] = q->data[j];
         j = (j + 1) % q->capacity;
     }
 
     free(q->data);
     q->data = newData;
     q->front = 0;
     q->rear = q->count - 1;
     q->capacity = newCapacity;
     return true;
 }
 
 bool queue_push(Queue *q, int value) {
     if (!q) return false;
     
     if (q->count == q->capacity && !queue_expand(q)) {
         return false;
     }
 
     q->rear = (q->rear + 1) % q->capacity;
     q->data[q->rear] = value;
     q->count++;
     return true;
 }
 
 bool queue_pop(Queue *q) {
     if (queue_empty(q)) return false;
 
     q->front = (q->front + 1) % q->capacity;
     q->count--;
     return true;
 }
 
 int queue_front(Queue *q) {
     return queue_empty(q) ? -1 : q->data[q->front];
 }
 
 int queue_back(Queue *q) {
     return queue_empty(q) ? -1 : q->data[q->rear];
 }
 
 #endif // QUEUE_IMPLEMENTATION
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif // QUEUE_H