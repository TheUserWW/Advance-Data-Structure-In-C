# 优先队列（最小堆）头文件文档

## 概述

本头文件提供了基于最小堆数据结构的C语言优先队列实现。该优先队列可以高效访问最小元素（前端）并优化了对最大元素（后端）的访问。

## 特性

- **最小堆实现**：始终提供O(1)时间访问最小元素
- **高效操作**：插入和提取操作时间复杂度为O(log n)
- **双端访问**：快速访问最小（前端）和最大（后端）元素
- **动态大小**：自动处理队列容量
- **类型安全**：当前支持整型数值

## 数据结构

```c
typedef struct {
    int *heap;          // 存储堆元素的数组(基于1的索引)
    int capacity;       // 最大元素容量
    int count;          // 当前元素数量
    int max_leaf;       // 最大叶子节点值的缓存(用于pq_back)
} PriorityQueue;
```

## API参考

### 创建与销毁

#### `pq_create`
```c
PriorityQueue* pq_create(int max_size);
```
创建具有指定容量的新优先队列。

**参数:**
- `max_size`: 队列可容纳的最大元素数量

**返回:**
- 指向新创建的PriorityQueue的指针
- 分配失败时返回NULL

#### `pq_free`
```c
void pq_free(PriorityQueue *pq);
```
释放优先队列关联的所有资源。

**参数:**
- `pq`: 要销毁的优先队列指针

### 容量操作

#### `pq_empty`
```c
bool pq_empty(PriorityQueue *pq);
```
检查优先队列是否为空。

**返回:**
- 队列为空返回true
- 否则返回false

#### `pq_full`
```c
bool pq_full(PriorityQueue *pq);
```
检查优先队列是否已满。

**返回:**
- 队列达到容量返回true
- 否则返回false

#### `pq_size`
```c
int pq_size(PriorityQueue *pq);
```
返回队列当前元素数量。

### 元素访问

#### `pq_front`
```c
int pq_front(PriorityQueue *pq);
```
访问最小元素(最小堆的顶部)。

**返回:**
- 最小元素的值
- 队列为空时返回INT_MAX

#### `pq_back`
```c
int pq_back(PriorityQueue *pq);
```
访问队列中的最大元素。

**返回:**
- 最大元素的值
- 队列为空时返回INT_MIN

### 修改器

#### `pq_push`
```c
void pq_push(PriorityQueue *pq, int value);
```
向优先队列插入新元素。

**参数:**
- `value`: 要插入的整数值

**注意:**
- 队列已满时会打印错误信息
- 插入后保持堆属性

#### `pq_pop`
```c
int pq_pop(PriorityQueue *pq);
```
移除并返回最小元素。

**返回:**
- 最小元素的值
- 队列为空时返回INT_MAX

## 使用示例

```c
#include "priority_queue.h"
#include <stdio.h>

int main() {
    // 创建容量为10的优先队列
    PriorityQueue *pq = pq_create(10);
    
    // 插入元素
    pq_push(pq, 5);
    pq_push(pq, 3);
    pq_push(pq, 8);
    pq_push(pq, 1);
    pq_push(pq, 4);
    
    // 访问元素
    printf("前端(最小): %d\n", pq_front(pq));  // 输出: 1
    printf("后端(最大): %d\n", pq_back(pq));     // 输出: 8
    
    // 处理所有元素
    while (!pq_empty(pq)) {
        printf("%d ", pq_pop(pq));
    }
    // 输出: 1 3 4 5 8
    
    // 清理
    pq_free(pq);
    return 0;
}
```

## 性能特征

| 操作        | 时间复杂度      | 说明                          |
|------------|----------------|-----------------------------|
| pq_create  | O(1)           | 单次分配                     |
| pq_free    | O(1)           | 单次释放                     |
| pq_push    | O(log n)       | 堆插入                      |
| pq_pop     | O(log n)       | 堆提取                      |
| pq_front   | O(1)           | 直接访问根节点               |
| pq_back    | O(1) 均摊      | 在操作过程中维护             |
| pq_empty   | O(1)           | 计数比较                    |
| pq_full    | O(1)           | 计数比较                    |

## 注意事项

1. 实现使用基于1的索引以便于父/子节点计算
2. 错误条件返回INT_MAX/INT_MIN并打印到stderr
3. 生产环境使用时考虑:
   - 添加错误代码替代打印
   - 使用void指针使其通用化
   - 添加调整容量功能
4. max_leaf优化在保持O(log n)插入时间的同时提供了O(1)访问最大元素的能力
